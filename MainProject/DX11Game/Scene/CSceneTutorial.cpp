/**
*
* @file		CSceneTutorial.cpp
* @brief	チュートリアルシーンクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/10	実装開始
*
*/

/** インクルード部 */
#include <Scene/CSceneTutorial.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Factory/CStageFactory.h>
#include <Scene/CSceneManager.h>
#include <System/Camera/CCameraManager.h>
#include <Component/Tutorial/CTutorialManager.h>
#include <System/Sound/CSound.h>

// コンポーネント
#include <Component/Game/Field/CField.h>
#include <Component/Game/GameSystem/CScoreUI.h>
#include <Component/Game/GameSystem/CTimerUI.h>
#include <Component/Tutorial/CTutorialUserGuideUI.h>
#include <Component/Tutorial/CTutorialShipGate.h>
#include <Component/Game/GameSystem/CColorUI.h>

/** マクロ定義 */
namespace
{
	// カメラ座標
	const XMFLOAT3 CAMERA_POS			= XMFLOAT3(0.0f, 130.0f, -90.0f);
	// カメラ注視点
	const XMFLOAT3 CAMERA_TARGET_POS	= XMFLOAT3(0.0f, 0.0f, 10.0f);
	// 操作ガイド座標
	const Vector3 GUIDE_POS				= Vector3(0.0f, -310.0f, 0.0f);
	// カラーUI座標
	const Vector3 COLOR_POS				= Vector3(550.0f, 200.0f, 0.0f);
	// ゲート座標
	const Vector3 GATE_POS				= Vector3(0.0f, 0.0f, 40.0f);
}

/**
* @brief	コンストラクタ
*/
CSceneTutorial::CSceneTutorial()
	: m_nStageNo(0)
{
	// シーンタイプセット
	SetSceneType(SceneTutorial);
}


/**
* @brief	デストラクタ
*/
CSceneTutorial::~CSceneTutorial()
{

}


/**
* @brief	初期化処理
*/
void CSceneTutorial::Init()
{
	// カメラ座標セット
	CAMERA->Get(0)->SetParameter(CAMERA_POS, CAMERA_TARGET_POS, Vector3::up());
	CAMERA->Get(0)->Chase(false);

	// チュートリアル管理生成
	TUTORIAL_MANAGER->CreateInstance();
	TUTORIAL_MANAGER->SetStageNo(m_nStageNo);

	// フィールド生成
	const auto& field = GAMEOBJECT_MANAGER->Instantiation<CGameObject>();
	field.lock()->AddComponent<CField>();

	// ステージ生成
	CStageFactory::Init(m_eSceneType, m_nStageNo);

	// スコアUI生成
	const auto& scoreObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(SCREEN_WIDTH / 2 - 120.0f, SCREEN_HEIGHT / 2 - 70.0f, 0.0f)).lock();
	const auto& scoreCom = scoreObj->AddComponent<CScoreUI>().lock();

	// タイマーUI生成
	const auto& timerObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(-SCREEN_WIDTH / 2 + 120.0f, SCREEN_HEIGHT / 2 - 70.0f, 0.0f)).lock();
	const auto& timerCom = timerObj->AddComponent<CTimerUI>().lock();

	// 操作ガイド生成
	const auto& guideObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(GUIDE_POS).lock();
	guideObj->AddComponent<CTutorialUserGuideUI>();

	// カラーUI生成
	const auto& colorObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(COLOR_POS).lock();
	colorObj->AddComponent<CColorUI>();

	// チュートリアル用出荷ゲート生成
	const auto& gateObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(GATE_POS).lock();
	gateObj->AddComponent<CTutorialShipGate>();

	// BGM再生
	SOUND_MANAGER->Play(BGM_GAME);
}


/**
* @brief	終了処理
*/
void CSceneTutorial::Uninit()
{
	// BGM停止
	SOUND_MANAGER->Stop(BGM_GAME);

	// ステージ生成終了
	CStageFactory::Uninit();

	// チュートリアル管理削除
	TUTORIAL_MANAGER->DestroyInstance();
}


/**
* @brief	更新処理
*/
void CSceneTutorial::Update()
{
	// チュートリアル管理更新
	TUTORIAL_MANAGER->Update();
}


/**
* @brief	描画処理
*/
void CSceneTutorial::Draw()
{
	// チュートリアル管理描画
	TUTORIAL_MANAGER->Draw();
}