/**
*
* @file		CSceneGame.cpp
* @brief	ゲームシーンクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	実装開始
*
*/

/** インクルード部 */
#include <Scene/CSceneGame.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Scene/CSceneManager.h>
#include <System/Factory/CStageFactory.h>
#include <Scene/CGameManager.h>
#include <Scene/CSceneResult.h>
#include <System/Camera/CCameraManager.h>
#include <System/Sound/CSound.h>
#include <System/CInput.h>

// コンポーネント
#include <Component/Game/Field/CField.h>
#include <Component/Game/GameSystem/CScoreUI.h>
#include <Component/Game/GameSystem/CTimerUI.h>
#include <Component/Game/GameSystem/CColorUI.h>
#include <Component/Game/GameSystem/CPauseButton.h>

namespace
{
	// カメラ座標
	const XMFLOAT3 CAMERA_POS = XMFLOAT3(0.0f, 130.0f, -90.0f);
	// カメラ注視点
	const XMFLOAT3 CAMERA_TARGET_POS	= XMFLOAT3(0.0f, 0.0f, 10.0f);
	// リザルトシーンに移行するまでの時間
	const int SCENE_CHNAGE_INTERVAL = 180;
	// カラーUI座標
	const Vector3 COLOR_POS = Vector3(550.0f, 200.0f, 0.0f);
	// ポーズUI座標
	const Vector3 PAUSE_POS = Vector3(500.0f, -300.0f, 0.0f);
}

/**
* @brief	コンストラクタ
*/
CSceneGame::CSceneGame()
	: m_nFrame(0)
{
	// シーンタイプセット
	SetSceneType(SceneGame);
}


/**
* @brief	デストラクタ
*/
CSceneGame::~CSceneGame()
{

}


/**
* @brief	初期化処理
*/
void CSceneGame::Init()
{
	// カメラ座標セット
	CAMERA->Get(0)->SetParameter(CAMERA_POS, CAMERA_TARGET_POS, Vector3::up());
	CAMERA->Get(0)->Chase(false);

	// ゲーム管理生成
	GAME_MANAGER->CreateInstance();

	// フィールド生成
	const auto& field = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(0.0f, 0.0f, 0.0f));
	field.lock()->AddComponent<CField>();

	// ステージ生成
	CStageFactory::Init(m_eSceneType);

	// スコアUIオブジェクト生成
	const auto& scoreObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(SCREEN_WIDTH / 2 - 120.0f, SCREEN_HEIGHT / 2 - 70.0f, 0.0f));
	scoreObj.lock()->AddComponent<CScoreUI>();

	// タイマーUIオブジェクト生成
	const auto& timerObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(-SCREEN_WIDTH / 2 + 120.0f, SCREEN_HEIGHT / 2 - 70.0f, 0.0f));
	timerObj.lock()->AddComponent<CTimerUI>();

	// カラーUI生成
	const auto& colorObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(COLOR_POS).lock();
	colorObj->AddComponent<CColorUI>();

	// ポーズボタンUI生成
	const auto& pauseObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(PAUSE_POS).lock();
	pauseObj->AddComponent<CPauseButton>();
}


/**
* @brief	終了処理
*/
void CSceneGame::Uninit()
{
	// BGMストップ
	SOUND_MANAGER->Stop(BGM_GAME);

	// ステージ生成終了
	CStageFactory::Uninit();

	// ゲーム管理削除
	GAME_MANAGER->DestroyInstance();
}


/**
* @brief	更新処理
*/
void CSceneGame::Update()
{
	// ゲーム管理更新
	GAME_MANAGER->Update();

	// ゲーム終了後シーン遷移
	if (GAME_MANAGER->IsGameFin())
	{
		if (m_nFrame > SCENE_CHNAGE_INTERVAL)
		{
			const auto& scene = SCENE_MANAGER;
			// フェード中だったら終了
			if (scene->GetFadeState() != CFade::EFade::FADE_NONE)	return;
			// 次のシーンセット
			auto nextScene = scene->SetNextScene<CSceneResult>();
			nextScene->SetScore(GAME_MANAGER->GetScore());
			m_nFrame = 0;
		}
		m_nFrame++;
	}
}


/**
* @brief	描画処理
*/
void CSceneGame::Draw()
{
	// ゲーム管理描画
	GAME_MANAGER->Draw();
}
