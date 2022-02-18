/**
*
* @file		CSelectGate.cpp
* @brief	セレクトゲートクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	実装開始
*
*/

/** インクルード部 */
#include <Component/Select/CSelectGate.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneTitle.h>
#include <Scene/CSceneGame.h>
#include <Scene/CSceneTutorial.h>
#include <System/GameObject/CGameObjectManager.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/CPlayerTarget.h>
#include <Component/Select/CSelectGateUI.h>

/**
* @brief	コンストラクタ
*/
CSelectGate::CSelectGate()
	: m_eType(GateTitle)
{

}


/**
* @brief	コンストラクタ
*/
CSelectGate::~CSelectGate()
{

}


/**
* @brief	生成時
*/
void CSelectGate::OnCreate()
{
	const auto& obj = m_spGameObject.lock();
	
	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Stationary");

	// 名前の設定
	obj->SetName("SelectGate");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ShipGate);

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(40.0f, 40.0f, 10.0f), Vector3(0.0f, 20.0f, 0.0f));
	collider->m_pMainScript = this;
}


/**
* @brief	破棄時
*/
void CSelectGate::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新
*/
void CSelectGate::Update()
{

}


/**
* @brief	当たり判定
* @param	collider	相手のコライダー
*/
void CSelectGate::OnCollision(std::weak_ptr<CCollider> collider)
{
	// ターゲットに選択されている場合描画を変える
	if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)
	{
		// ターゲットが既に存在していた場合終了
		const auto& target = collider.lock()->m_spGameObject.lock()->GetComponent<CPlayerTarget>().lock();
		if (target->IsTarget())	return;
		// ターゲットの決定
		target->TargetON();
		// シェーダー変更
		const auto& obj = m_spGameObject.lock();
		obj->SetShader(EVertexShaderKind::AssimpVS, EPixelShaderKind::AssimpTargetPS);
	}
}


/**
* @brief	行う処理があるかどうか ⇒ あれば処理を実行する
* @details	相手がアイテムを持っている場合の処理
* @param	collider		相手のコライダー
* @return	bool			処理の有無
*/
bool CSelectGate::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// フェード中だったら終了
	const auto& scene = SCENE_MANAGER;
	if (scene->GetFadeState() != CFade::EFade::FADE_NONE)	return false;

	// ゲートタイプによって分岐
	switch (m_eType)
	{
	case CSelectGate::GateTitle:	scene->SetNextScene<CSceneTitle>();		break;
	case CSelectGate::GateTutorial:	scene->SetNextScene<CSceneTutorial>();	break;
	case CSelectGate::GateGame1:	scene->SetNextScene<CSceneGame>();		break;
	default:
		break;
	}
	return false;
}


/**
* @brief	ゲートタイプセット
* @param	type	ゲートタイプ
*/
void CSelectGate::SetGateType(EGateType type)
{
	m_eType = type;

	// UI生成
	const auto& obj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	obj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3::up() * 50.0f);
	const auto& com = obj->AddComponent<CSelectGateUI>().lock();
	com->SetTexture(m_eType);
}