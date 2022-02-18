/**
*
* @file		CPotteryWheel.cpp
* @brief	轆轤台クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Potted/CPotteryWheel.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/Action/CPutAction.h>
#include <Component/Game/Potted/Action/CTrimShapeAction.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Potted/CClay.h>
#include <Component/Game/Player/CPlayerTarget.h>

/** マクロ定義 */
namespace
{
	const float ROTATE_SPEED = 10.0f;
}

/**
* @brief	コンストラクタ
*/
CPotteryWheel::CPotteryWheel()
	: m_bIsAction(false)
	, m_bOldIsAction(false)
{

}


/**
* @brief	デストラクタ
*/
CPotteryWheel::~CPotteryWheel()
{

}


/**
* @brief	生成時
*/
void CPotteryWheel::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Stationary");

	// 名前設定
	obj->SetName("PotteryWheel");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::PotteryWheel);

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(25.0f, 20.0f, 25.0f),Vector3::up() * 10.0f);
	collider->m_pMainScript = this;

	// 回転オブジェクト
	m_spWheel = GAMEOBJECT_MANAGER->Instantiation<CGameObject>();
	const auto& com = m_spWheel.lock()->AddComponent<CModelRenderer>().lock();
	com->SetModel(EModelType::Wheel);
	// 親子関係を作る
	CTransform::SetParentChildRelation(m_spGameObject, m_spWheel, EDirection::Up, 10.0f);
}


/**
* @brief	破棄時
*/
void CPotteryWheel::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CPotteryWheel::Update()
{
	if (m_bOldIsAction && !m_bIsAction)
	{
		m_spGameObject.lock()->RemoveComponent<CAction>();
		m_bOldIsAction = m_bIsAction;
	}

	if (m_bIsAction)
	{
		// 回転処理
		const auto& wheelTrans = m_spWheel.lock()->m_spTransform.lock();
		auto rotate = wheelTrans->GetRotation();
		rotate->y += ROTATE_SPEED;
		wheelTrans->SetRotation(rotate);
		m_bOldIsAction = m_bIsAction;
	}
}


/**
* @brief	当たり判定
* @param	collider		相手のコライダー
*/
void CPotteryWheel::OnCollision(std::weak_ptr<CCollider> collider)
{
	// ターゲットに選択されている場合描画を変える
	if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)
	{
		// ターゲットが既に存在していた場合終了
		const auto& taget = collider.lock()->m_spGameObject.lock()->GetComponent<CPlayerTarget>().lock();
		if (taget->IsTarget())	return;
		// ターゲットの決定
		taget->TargetON();
		const auto& obj = m_spGameObject.lock();
		// シェーダー変更
		obj->SetShader(EVertexShaderKind::AssimpVS, EPixelShaderKind::AssimpTargetPS);
	}
}


/**
* @brief	行う処理があるかどうか ⇒ あれば処理を実行する
* @details	相手がアイテムを持っていなかった場合の処理
* @param	collider		相手のコライダー
* @return	bool			アクションの有無
*/
bool CPotteryWheel::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// アクション中だった場合終了
	if (m_bIsAction)	return false;

	// 相手オブジェクトによって処理が変わる
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----プレイヤーターゲット
	{
		const auto& childList = m_spWheel.lock()->m_spTransform.lock()->GetChildList();

		// 回転台以外の子オブジェクトが存在するとき
		if (childList.size() > 0)
		{
			// プレイヤー取得
			const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();

			// 親子関係の解除
			const auto& clayObj = childList.begin()->lock();
			m_spWheel.lock()->m_spTransform.lock()->ReleaseRelationship(clayObj);

			//親子関係を作る
			CTransform::SetParentChildRelation(playerObj, clayObj, EDirection::Front, 15.0f);

			// アイテムセット
			const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>().lock();
			playerCom->SetItem(clayObj);

			// プレイヤーにアクション追加
			playerObj.lock()->AddComponent<CTakeAction>();
			return true;
		}
	}
	return false;
	default:break;
	}

	return false;
}


/**
* @brief	行う処理があるかどうか ⇒ あれば処理を実行する
* @details	相手がアイテムを持っている場合の処理
* @param	collider		相手のコライダー
* @param	item			アイテムのゲームオブジェクト
* @return	bool			アクションの有無
*/
bool CPotteryWheel::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	// アクション中だった場合終了
	if (m_bIsAction)	return false;

	// 持っているアイテムによって処理を変える
	switch (itemObj.lock()->GetObjectID())
	{
	case EObjectType::Clay:		//-----粘土
		// 粘土が加工済みだった場合終了
		if (itemObj.lock()->GetComponent<CClay>().lock()->GetProcessedFlag())	return false;

		// 回転オブジェクトの子オブジェクトがなければ実行
		if (m_spWheel.lock()->m_spTransform.lock()->GetChildList().size() == 0)
		{
			// プレイヤーにアクション追加
			const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
			const auto& playerAction = playerObj.lock()->AddComponent<CPutAction>();
			playerAction.lock()->SetTarget(playerObj, itemObj);

			// アイテムのリリース
			playerObj.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();

			// 親子関係を解除
			playerObj.lock()->m_spTransform.lock()->ReleaseRelationship(itemObj);

			// 親子関係を作る
			CTransform::SetParentChildRelation(m_spWheel, itemObj, EDirection::Up, 1.0f);

			// 形を整えるアクションを追加
			const auto& trimAction = m_spGameObject.lock()->AddComponent<CTrimShapeAction>();
			trimAction.lock()->SetTarget(m_spGameObject, itemObj);

			// アクションON
			SetActionFlag(true);
			return true;
		}
		return false;
	default:	break;
	}
	return false;
}
