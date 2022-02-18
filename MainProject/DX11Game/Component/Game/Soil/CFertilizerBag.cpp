/**
*
* @file		CFertilizerBag.cpp
* @brief	肥料袋クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/16	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Soil/CFertilizerBag.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/CPlayerTarget.h>

// オブジェクト生成用
#include <System/Factory/CStageFactory.h>

/**
* @brief	コンストラクタ
*/
CFertilizerBag::CFertilizerBag()
{

}


/**
* @brief	デストラクタ
*/
CFertilizerBag::~CFertilizerBag()
{

}


/**
* @brief	生成時
*/
void CFertilizerBag::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Stationary");

	// 名前設定
	obj->SetName("FertilizerBag");

	// コンポーネントID設定
	SetID(Script);

	// モデルのセット
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::FertilizerBagC);

	// コンポーネント追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(20.0f, 10.0f, 30.0f),Vector3::up() * 5.0f);
	collider->m_pMainScript = this;
}


/**
* @brief	破棄時
*/
void CFertilizerBag::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CFertilizerBag::Update()
{

}


/**
* @brief	当たり判定
* @param	collider		相手のコライダー
*/
void CFertilizerBag::OnCollision(std::weak_ptr<CCollider> collider)
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
bool CFertilizerBag::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// 相手オブジェクトによって処理が変わる
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----プレイヤーターゲット
	{
		// 肥料オブジェクトを生成
		const auto& fertilizerObj = Create();

		// 親子関係を作る
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		CTransform::SetParentChildRelation(playerObj, fertilizerObj, EDirection::Front, 15.0f);

		// アイテムセット
		const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>().lock();
		playerCom->SetItem(fertilizerObj);

		// プレイヤーにアクション追加
		playerObj.lock()->AddComponent<CTakeAction>();
		return true;
	}
	default:	break;
	}

	return false;
}


/**
* @brief	色情報のセット
* @param	color	色タイプ
*/
void CFertilizerBag::SetColor(CColor::EColor color)
{
	// 色のセット
	m_eColor.colorType = color;

	// モデルの切り替え
	const auto& renderer = m_spGameObject.lock()->GetComponent<CModelRenderer>().lock();
	switch (m_eColor.colorType)
	{
	case CColor::EColor::Cyan:		renderer->SetModel(EModelType::FertilizerBagC);
									m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerBagC);			break;
	case CColor::EColor::Magenta:	renderer->SetModel(EModelType::FertilizerBagM);
									m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerBagM);			break;
	case CColor::EColor::Yellow:	renderer->SetModel(EModelType::FertilizerBagY);
									m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerBagY);			break;
	default:																									break;
	}
}


/**
* @brief	自身の色のオブジェクトを生成
* @return	std::weak_ptr<CGameObject> 生成したオブジェクト
*/
std::weak_ptr<CGameObject> CFertilizerBag::Create()
{
	std::weak_ptr<CGameObject> obj;
	switch (m_eColor.colorType)
	{
	case CColor::EColor::Cyan:		obj = CStageFactory::CreateGameObject(EObjectType::FertilizerC);	break;
	case CColor::EColor::Magenta:	obj = CStageFactory::CreateGameObject(EObjectType::FertilizerM);	break;
	case CColor::EColor::Yellow:	obj = CStageFactory::CreateGameObject(EObjectType::FertilizerY);	break;
	default:break;
	}
	return obj;
}