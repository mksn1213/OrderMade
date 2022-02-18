/**
*
* @file		CGameManager.cpp
* @brief	ゲーム管理クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/12	実装開始
*
*/

/** インクルード部 */
#include <Scene/CGameManager.h>
#include <Component/Game/Order/COrderManager.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Component/Game/GameSystem/CPauseUI.h>
#include <Scene/CSceneManager.h>
#include <System/Systems/CTransformSystem.h>
#include <System/Systems/CSpriteRendererSystem.h>
#include <System/Systems/CScriptSystem.h>
#include <System/Sound/CSound.h>
#include <Component/Game/GameSystem/CTimeUpUI.h>
#include <System/Renderer/CSpriteRenderer.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneSelect.h>
#include <System/CInput.h>

/** マクロ定義 */
namespace
{
	const int		TIME			= 60 * 120;						// ゲーム時間
	const int		COUNTDOWN_TIME	= 60 * 3;						// カウントダウン時間
	const Vector3	TEX_SIZE		= Vector3(50.0f, 100.0f, 1.0f);	// テクスチャサイズ
	const int		NUMBER_FRAME_X	= 10;							// 横フレーム数
	const int		NUMBER_FRAME_Y	= 1;							// 縦フレーム数
}

/**
* @brief	コンストラクタ
*/
CGameManager::CGameManager()
{

}


/**
* @brief	デストラクタ
*/
CGameManager::~CGameManager()
{

}


/**
* @brief	初期化処理
*/
HRESULT CGameManager::Init()
{
	// 制限時間セット
	m_pTimer = new CTimer(TIME);

	// 注文管理生成
	ORDER_MANAGER->CreateInstance();

	// 変数初期化
	m_nScore	= 0;
	m_bIsPause	= false;
	m_bGameFin	= false;
	m_bGameStart = false;
	m_nFrame	= COUNTDOWN_TIME;
	m_bSelect = true;

	// カウントダウン
	const auto& obj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& renderer = obj->AddComponent<CSpriteRenderer>().lock();
	renderer->SetDrawSize(TEX_SIZE);
	renderer->SetTexture(ETexture::Game_Number);
	unsigned drawSec = COUNTDOWN_TIME / 60 % 60;
	unsigned n = drawSec % 10;
	drawSec /= 10;
	int u = n % NUMBER_FRAME_X;
	int v = n / NUMBER_FRAME_X;
	renderer->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	renderer->SetTexSize(Vector3(1.0f / NUMBER_FRAME_X, 1.0f / NUMBER_FRAME_Y, 0.0f));
	m_spSprite = renderer;

	// 終了UI生成
	const auto& obj2 = std::make_shared<CGameObject>();
	obj2->m_self = obj2;
	obj2->Init();
	obj2->AddComponent<CTimeUpUI>();
	obj2->SetActive(false);
	m_spFinUIObj = obj2;

	// 別で更新するため、最初にコンポーネントを保持しておく
	m_spFinUIScript = obj2->GetComponent<CTimeUpUI>();

	// SEボリュームセット
	SOUND_MANAGER->SetVolume(SE_PAUSE, 5.0f);

	return S_OK;
}


/**
* @brief	終了処理
*/
void CGameManager::Uninit()
{
	// 終了UI破棄
	m_spFinUIObj.reset();

	// 注文管理削除
	ORDER_MANAGER->DestroyInstance();

	// タイマー削除
	if (m_pTimer != nullptr)
	{
		delete m_pTimer;
		m_pTimer = nullptr;
	}
}


/**
* @brief	更新処理
*/
void CGameManager::Update()
{
	if (!m_bGameStart)
	{
		// フェード中でない場合更新
		if (SCENE_MANAGER->GetFadeState() == CFade::EFade::FADE_NONE)
		{
			if (m_nFrame % 60 == 0)
			{
				if (m_nFrame <= 0)
				{
					// BGM再生
					SOUND_MANAGER->Play(BGM_GAME);
					m_spSprite.lock()->m_spGameObject.lock()->SetActive(false);
					m_bGameStart = true;
					return;
				}
				SOUND_MANAGER->Play(SE_CLICK);
			}
			m_nFrame--;
			unsigned n = m_nFrame / 60 % 60 % 10;
			int u = n % NUMBER_FRAME_X;
			int v = n / NUMBER_FRAME_X;
			float a = u / (float)NUMBER_FRAME_X;
			m_spSprite.lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X + 0.1f, v / (float)NUMBER_FRAME_Y, 0.0f));
		}
		return;
	}

	// ゲームが終了している場合、終了UI更新して終了
	if (m_bGameFin)
	{
		m_spFinUIScript.lock()->Update();
		return;
	}

	// ボタンプッシュでポーズのON/OFF
	if (CInput::GetKeyTrigger(VK_P))
	{
		if (!m_spPauseUIObj.lock())
		{
			// ポーズUI生成
			const auto& pauseObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
			pauseObj->AddComponent<CPauseUI>();
			m_spPauseUIObj = pauseObj;
			// ポーズON
			m_bIsPause = true;
			// システムの更新OFF
			SCENE_MANAGER->SystemStop(true);
		}
	}

	// ポーズ中は更新しない
	if (!m_bIsPause)
	{
		// 制限時間更新
		if (!m_pTimer->Update())
		{
			// 更新できなければゲーム終了
			m_bGameFin = true;
			// 終了UIオブジェクトをアクティブ状態に
			m_spFinUIObj->SetActive(true);
			// システムの更新OFF
			SCENE_MANAGER->SystemStop(true);
			return;
		}

		// 注文更新
		ORDER_MANAGER->Update();
	}
	else
	{
		// ポーズ中はコンポーネントシステムを止めるのでここで更新をかける
		if (m_spPauseUIObj.lock())
		{
			m_spPauseUIObj.lock()->Update();
		}

		if (CInput::GetKeyTrigger(VK_A))
		{
			m_spPauseUIObj.lock()->GetComponent<CPauseUI>().lock()->Select(true);
			m_bSelect = true;
		}
		else if (CInput::GetKeyTrigger(VK_D))
		{
			m_spPauseUIObj.lock()->GetComponent<CPauseUI>().lock()->Select(false);
			m_bSelect = false;
		}

		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			if (m_bSelect)
			{
				// SE再生
				SOUND_MANAGER->Play(SE_PAUSE);

				// ポーズ中の場合
				if (m_bIsPause)
				{
					m_spPauseUIObj.lock()->Destroy();
					m_spPauseUIObj.reset();
					// ポーズOFF
					m_bIsPause = false;
					// システムの更新ON
					SCENE_MANAGER->SystemStop(false);
				}
			}
			else
			{
				// SE再生
				SOUND_MANAGER->Play(SE_PAUSE);

				// セレクトシーン
				SCENE_MANAGER->SetNextScene<CSceneSelect>();
			}
		}
	}
}


/**
* @brief	描画処理
*/
void CGameManager::Draw()
{
	// 注文管理描画
	ORDER_MANAGER->Draw();
}
