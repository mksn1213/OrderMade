/**
*
* @file		CFlower.cpp
* @brief	花クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/09	実装開始
* @date		2021/12/19	コンポーネントに変更
* @date		2021/12/28	アイコンUI追加
*
*/

/** インクルード部 */
#include <Component/Game/Plant/CFlower.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Utility/Search.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <Component/Game/Player/CPlayerTarget.h>

/**
* @brief	コンストラクタ
*/
CFlower::CFlower()
{

}


/**
* @brief	デストラクタ
*/
CFlower::~CFlower()
{

}


/**
* @brief	生成時
*/
void CFlower::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Item");

	// 名前設定
	obj->SetName("Flower");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Flower_W);

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(5.0f, 10.0f, 10.0f), Vector3::up() * 10.0f);
	collider->m_pMainScript = this;

	// アイコンUI作成
	const auto& uiObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& uiCom = uiObj->AddComponent<CIconUI>().lock();
	uiCom->SetIconTexture(ETexture::Icon_Flower);

	// 親子関係を作る
	CTransform::SetParentChildRelation(m_spGameObject, uiObj, EDirection::Up, 20.0f);
}


/**
* @brief	破棄時
*/
void CFlower::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CFlower::Update()
{

}


/**
* @brief	当たった際の処理
* @param	collider		当たり相手のコライダー
*/
void CFlower::OnCollision(std::weak_ptr<CCollider> collider)
{
	// ターゲットに選択されている場合描画を変える
	if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)
	{
		// ターゲットが既に存在していた場合終了
		const auto& taget = collider.lock()->m_spGameObject.lock()->GetComponent<CPlayerTarget>().lock();
		if (taget->IsTarget())	return;
		const auto& obj = m_spGameObject.lock();
		// 親が存在していた場合終了
		if (obj->m_spTransform.lock()->GetParent().lock())	return;
		// ターゲットの決定
		taget->TargetON();
		// シェーダー変更
		obj->SetShader(EVertexShaderKind::AssimpVS, EPixelShaderKind::AssimpTargetPS);
	}
}


/**
* @brief	行う処理があるかどうか ⇒ あれば処理を実行する
* @param	collider		相手のコライダー
* @return	bool			アクション有無
*/
bool CFlower::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// 相手オブジェクトによって処理が変わる
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----プレイヤーターゲット
	{
		// プレイヤー取得
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();

		// 親子関係を作る
		m_spTransform.lock()->GetParent().reset();
		CTransform::SetParentChildRelation(playerObj, m_spGameObject, EDirection::Front, 15.0f);

		// アイテムセット
		const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>();
		playerCom.lock()->SetItem(m_spGameObject);

		// プレイヤーにアクション追加
		playerObj.lock()->AddComponent<CTakeAction>();
		return true;
	}
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
bool CFlower::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	// 持っているアイテムによって処理を変える
	switch (itemObj.lock()->GetObjectID())
	{
	case EObjectType::Potted:		//-----鉢植え
	{
		// 既に鉢植えにアイテムオブジェクトが入っていた場合終了
		const auto& childList = itemObj.lock()->m_spTransform.lock()->GetChildList();
		const auto& childObj = SearchExistsList(childList, "Item").lock();
		if (childObj)	return false;
		
		// 子オブジェクトを取り替える
		m_spGameObject.lock()->m_spTransform.lock()->ReplaceChildAll(itemObj);

		// 親子関係を作る
		CTransform::SetParentChildRelation(itemObj, m_spGameObject, EDirection::Up, 0.0f);

		// プレイヤーにアクション追加
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		playerObj.lock()->AddComponent<CTakeAction>();
		return true;
	}
	default:	break;
	}

	return false;
}


/**
* @brief	色情報のセット
* @param	color		色情報
*/
void CFlower::SetColor(CColor color)
{
	// 色のセット
	m_eColor = color;

	// モデルの切り替え
	const auto& renderer = m_spGameObject.lock()->GetComponent<CModelRenderer>().lock();
	switch (m_eColor.colorType)
	{
	case CColor::EColor::White:		renderer->SetModel(EModelType::Flower_W);	break;
	case CColor::EColor::Cyan:		renderer->SetModel(EModelType::Flower_C);	break;
	case CColor::EColor::Magenta:	renderer->SetModel(EModelType::Flower_M);	break;
	case CColor::EColor::Yellow:	renderer->SetModel(EModelType::Flower_Y);	break;
	case CColor::EColor::Red:		renderer->SetModel(EModelType::Flower_R);	break;
	case CColor::EColor::Green:		renderer->SetModel(EModelType::Flower_G);	break;
	case CColor::EColor::Blue:		renderer->SetModel(EModelType::Flower_B);	break;
	default:																	break;
	}
}