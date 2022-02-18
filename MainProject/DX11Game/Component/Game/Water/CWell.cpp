/**
*
* @file		CWell.cpp
* @brief	井戸クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Water/CWell.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CPutAction.h>
#include <Component/Game/Water/Action/CPutWaterAction.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Water/CBucket.h>
#include <Component/Game/Player/CPlayerTarget.h>
#include <Component/Game/Water/CWater.h>

/**
* @brief	コンストラクタ
*/
CWell::CWell()
	: m_bIsAction(false)
	, m_bOldIsAction(false)
{

}


/**
* @brief	デストラクタ
*/
CWell::~CWell()
{

}


/**
* @brief	生成時
*/
void CWell::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Stationary");

	// 名前設定
	obj->SetName("Well");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Well);

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(22.0f, 20.0f, 20.0f));
	collider->m_pMainScript = this;
	
	// 水メッシュの生成
	const auto& waterObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	waterObj->AddComponent<CWater>();
	waterObj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3::up()*10.0f);
	waterObj->m_spTransform.lock()->SetScale(Vector3(12.0f, 1.0f, 12.0f));
}


/**
* @brief	破棄時
*/
void CWell::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CWell::Update()
{
	if (m_bOldIsAction && !m_bIsAction)
	{
		m_spGameObject.lock()->RemoveComponent<CAction>();
		m_bOldIsAction = m_bIsAction;
	}

	if (m_bIsAction)
	{
		m_bOldIsAction = m_bIsAction;
	}
}


/**
* @brief	当たり判定
* @param	collider		相手のコライダー
*/
void CWell::OnCollision(std::weak_ptr<CCollider> collider)
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
* @
*/
bool CWell::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// アクション中だった場合終了
	if (m_bIsAction)	return false;

	// 相手オブジェクトによって処理が変わる
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----プレイヤーターゲット
	{
		const auto& childList = m_spTransform.lock()->GetChildList();

		// 子オブジェクトがある場合
		if (childList.size() > 0)
		{
			// プレイヤー取得
			const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();

			// 親子関係の解除
			m_spTransform.lock()->ReleaseRelationship(childList.begin()->lock());

			// 親子関係を作る
			CTransform::SetParentChildRelation(playerObj, childList.begin()->lock(), EDirection::Front, 15.0f);

			// アイテムセット
			const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>().lock();
			playerCom->SetItem(childList.begin()->lock());

			// プレイヤーにアクション追加
			playerObj.lock()->AddComponent<CTakeAction>();
			return true;
		}
	}
		return false;
	default:	break;
	}

	return false;
}


/**
* @brief	行う処理があるかどうか ⇒ あれば処理を実行する
* @details	相手がアイテムを持っている場合の処理
* @param	collider		相手のコライダー
* @param	item			アイテムのゲームオブジェクト
* @return	bool			処理の有無
*/
bool CWell::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	// アクション中だった場合終了
	if (m_bIsAction)	return false;

	// 持っているアイテムによって処理を変える
	switch (itemObj.lock()->GetObjectID())
	{
	case EObjectType::Bucket:		//-----バケツ
		// バケツに水が入っていた場合終了
		if (itemObj.lock()->GetComponent<CBucket>().lock()->GetWaterFlag())	return false;

		// 子オブジェクトがなければ実行
		if (m_spTransform.lock()->GetChildList().size() == 0)
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
			CTransform::SetParentChildRelation(m_spGameObject, itemObj, EDirection::Up, 20.0f, EDirection::Left, 3.6f);

			// 水を入れるアクションを追加
			const auto& wellAction = m_spGameObject.lock()->AddComponent<CPutWaterAction>();
			wellAction.lock()->SetTarget(m_spGameObject, itemObj);

			// アクションON
			SetActionFlag(true);
			return true;
		}
		return false;
	default:break;
	}

	return false;
}
