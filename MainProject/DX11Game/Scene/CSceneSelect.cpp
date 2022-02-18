/**
*
* @file		CSceneSelect.cpp
* @brief	セレクトシーンクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
*
*/

/** インクルード部 */
#include <Scene/CSceneSelect.h>
#include <Scene/CSceneGame.h>
#include <System/Factory/CStageFactory.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Scene/CSceneManager.h>
#include <System/Camera/CCameraManager.h>
#include <System/Sound/CSound.h>
#include <System/CInput.h>
#include <System/Renderer/CSpriteRenderer.h>

// コンポーネント
#include <Component/Game/Field/CField.h>
#include <Component/Select/CSelectGate.h>
#include <Component/Select/CSelectUserGuideUI.h>

/** マクロ定義 */
namespace
{
	// カメラ座標
	const XMFLOAT3	CAMERA_POS			= XMFLOAT3(0.0f, 70.0f, -70.0f);
	// カメラ注視点
	const XMFLOAT3	CAMERA_TARGET_POS	= XMFLOAT3(0.0f, 30.0f, 0.0f);
	// ゲート座標
	const Vector3	TITLE_GATE_POS		= Vector3(-90.0f, 0.0f, 40.0f);
	const Vector3	TUTORIAL_GATE_POS	= Vector3(0.0f, 0.0f, 40.0f);
	const Vector3	GAME1_GATE_POS		= Vector3(90.0f, 0.0f, 40.0f);
	// 操作ガイド座標
	const Vector3	GUIDE_POS			= Vector3(0.0f, -310.0f, 0.0f);
}

/**
* @brief	コンストラクタ
*/
CSceneSelect::CSceneSelect()
{
	// シーンタイプセット
	SetSceneType(SceneSelect);
}


/**
* @brief	デストラクタ
*/
CSceneSelect::~CSceneSelect()
{

}


/**
* @brief	初期化処理
*/
void CSceneSelect::Init()
{
	// カメラ座標セット
	CAMERA->Get(0)->SetParameter(CAMERA_POS, CAMERA_TARGET_POS, Vector3::up());
	CAMERA->Get(0)->Chase(true);

	// フィールド生成
	const auto& field = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	field->AddComponent<CField>();

	// ステージ生成
	CStageFactory::Init(m_eSceneType);

	// ゲート生成
	const auto& titleGate = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	titleGate->m_spTransform.lock()->SetPosition(TITLE_GATE_POS);
	const auto& titleGateCom = titleGate->AddComponent<CSelectGate>().lock();
	titleGateCom->SetGateType(CSelectGate::GateTitle);

	const auto& tutorialGate = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	tutorialGate->m_spTransform.lock()->SetPosition(TUTORIAL_GATE_POS);
	const auto& tutorialGateCom = tutorialGate->AddComponent<CSelectGate>().lock();
	tutorialGateCom->SetGateType(CSelectGate::GateTutorial);

	const auto& gameGate = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	gameGate->m_spTransform.lock()->SetPosition(GAME1_GATE_POS);
	const auto& gameGateCom = gameGate->AddComponent<CSelectGate>().lock();
	gameGateCom->SetGateType(CSelectGate::GateGame1);

	// 操作ガイド
	const auto& guideObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	guideObj->m_spTransform.lock()->SetPosition(GUIDE_POS);
	guideObj->AddComponent<CSelectUserGuideUI>();

	// サウンド再生
	SOUND_MANAGER->Play(BGM_SELECT);
}


/**
* @brief	終了処理
*/
void CSceneSelect::Uninit()
{
	SOUND_MANAGER->Stop(BGM_SELECT);
}


/**
* @brief	更新処理
*/
void CSceneSelect::Update()
{
}


/**
* @brief	描画処理
*/
void CSceneSelect::Draw()
{
}
