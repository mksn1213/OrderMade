/**
*
* @file		CFertilizer.cpp
* @brief	肥料クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/16  実装開始
* @date		2021/12/20	コンポーネントに変更
* @date		2021/12/28	アイコンUI追加
*
*/

/** インクルード部 */
#include <Component/Game/Soil/CFertilizer.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <System/Renderer/CMeshRenderer.h>
#include <Component/Game/Player/CPlayerTarget.h>

/**
* @brief	コンストラクタ
*/
CFertilizer::CFertilizer()
{

}


/**
* @brief	デストラクタ
*/
CFertilizer::~CFertilizer()
{

}


/**
* @brief	生成時
*/
void CFertilizer::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("SupportItem");

	// 名前設定
	obj->SetName("Fertilizer");

	// コンポーネントID設定
	SetID(Script);

	// モデルのセット
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::FertilizerC);

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(8.0f, 10.0f, 10.0f));
	collider->m_pMainScript = this;

	// アイコンUI作成
	const auto& uiObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	uiObj->AddComponent<CIconUI>().lock();
	m_spRenderer = uiObj->GetComponent<CMeshRenderer>();

	// 親子関係を作る
	CTransform::SetParentChildRelation(m_spGameObject, uiObj, EDirection::Up, 20.0f);
}


/**
* @brief	破棄時
*/
void CFertilizer::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CFertilizer::Update()
{

}


/**
* @brief	当たった際の処理
* @param	collider		当たり相手のコライダー
*/
void CFertilizer::OnCollision(std::weak_ptr<CCollider> collider)
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
bool CFertilizer::ExistsProcess(std::weak_ptr<CCollider> collider)
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
* @brief	色情報のセット
* @param	color	色タイプ
*/
void CFertilizer::SetColor(CColor::EColor color)
{
	// 色のセット
	m_eColor.colorType = color;

	// モデルの切り替え
	const auto& renderer = m_spGameObject.lock()->GetComponent<CModelRenderer>().lock();
	switch (m_eColor.colorType)
	{
	case CColor::EColor::Cyan:
		renderer->SetModel(EModelType::FertilizerC);
		m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerC);			
		m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Cyan);
		break;
	case CColor::EColor::Magenta:
		renderer->SetModel(EModelType::FertilizerM);
		m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerM);
		m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Magenta);
		break;
	case CColor::EColor::Yellow:
		renderer->SetModel(EModelType::FertilizerY);
		m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerY);
		m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Yellow);
		break;
	default:
		break;
	}	
}