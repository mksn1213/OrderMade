/**
*
* @file		CTimerUI.cpp
* @brief	タイマーUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/01/04	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/GameSystem/CTimerUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CGameManager.h>
#include <cmath>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const float NUMBER_SPACE	= 30.0f;	// 描画間隔
	const int	NUMBER_FRAME_X	= 10;		// 横フレーム数
	const int	NUMBER_FRAME_Y	= 1;		// 縦フレーム数
	const int	PERFORM_TIME = 30;			// 演出時間
	const int	TIME_REMAINING = 10;		// 残り時間
}

/**
* @brief	コンストラクタ
*/
CTimerUI::CTimerUI()
	: m_nFrame(0)
	, m_bPerform(false)
{

}


/**
* @brief	デストラクタ
*/
CTimerUI::~CTimerUI()
{
}


/**
* @brief	生成時
*/
void CTimerUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Sprite");

	// 名前設定
	obj->SetName("TimerUI");

	// コンポーネントID設定
	SetID(Script);

	// スプライトセット
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Game_Timer);
	sprite->SetDrawSize(Vector3(200.0f, 100.0f, 1.0f));
	m_spSprite = sprite;

	// 時間スプライト追加
	const auto& dot = obj->AddComponent<CSpriteRenderer>().lock();
	dot->SetTexture(ETexture::Game_Dot);
	dot->SetDrawSize(Vector3(30.0f, 45.0f, 1.0f));
	dot->SetColor(Vector3::zero());
	for (int i = 0; i < 4; ++i)
	{
		auto renderer = obj->AddComponent<CSpriteRenderer>().lock();
		renderer->SetTexture(ETexture::Game_Number);
		renderer->SetDrawSize(Vector3(30.0f, 45.0f, 1.0f));
		renderer->SetColor(Vector3::zero());
		renderer->SetTexSize(Vector3(1.0f / NUMBER_FRAME_X, 1.0f / NUMBER_FRAME_Y, 0.0f));
		m_spRenderer[i] = renderer;
	}
	m_spRenderer[0].lock()->SetLocalPos(Vector3(-NUMBER_SPACE * 2, 0.0f, 0.0f));
	m_spRenderer[1].lock()->SetLocalPos(Vector3(-NUMBER_SPACE, 0.0f, 0.0f));
	m_spRenderer[2].lock()->SetLocalPos(Vector3( NUMBER_SPACE, 0.0f, 0.0f));
	m_spRenderer[3].lock()->SetLocalPos(Vector3( NUMBER_SPACE * 2, 0.0f, 0.0f));
	
	int time;
	m_eSceneType = SCENE_MANAGER->GetScene()->GetSceneType();
	if (m_eSceneType == ESceneType::SceneTutorial)	time = 120 * 60;
	else time = GAME_MANAGER->GetTime();
	
	//-----分
	unsigned drawMinute = time / (60 * 60);
	unsigned n = drawMinute % 10;
	drawMinute /= 10;
	int u = n % NUMBER_FRAME_X;
	int v = n / NUMBER_FRAME_X;
	m_spRenderer[1].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	n = drawMinute % 10;
	drawMinute /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[0].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));

	//-----秒
	unsigned drawSec = time / 60 % 60;
	n = drawSec % 10;
	drawSec /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[3].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	n = drawSec % 10;
	drawSec /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[2].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
}


/**
* @brief	破棄時
*/
void CTimerUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CTimerUI::Update()
{
	// チュートリアルシーンだった場合終了
	if (m_eSceneType == ESceneType::SceneTutorial)	return;

	// テクスチャ座標更新
	int time = GAME_MANAGER->GetTime();
	// 指定した残り時間から演出開始
	if (time / 60 <= TIME_REMAINING && time / 60.0f == time / 60)	m_bPerform = true;

	//-----分
	unsigned drawMinute = time / (60 * 60);
	unsigned n = drawMinute % 10;
	drawMinute /= 10;
	int u = n % NUMBER_FRAME_X;
	int v = n / NUMBER_FRAME_X;
	m_spRenderer[1].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	n = drawMinute % 10;
	drawMinute /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[0].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));

	//-----秒
	unsigned drawSec = time / 60 % 60;
	n = drawSec % 10;
	drawSec /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[3].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	n = drawSec % 10;
	drawSec /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[2].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));

	// 演出関連
	if (m_bPerform)
	{
		if (m_nFrame < PERFORM_TIME)
		{
			// 色変更 + サイズ変更
			for (int i = 0; i < 4; ++i)
			{
				m_spRenderer[i].lock()->SetColor(Vector3::right() * 0.7f);
				if (m_nFrame < PERFORM_TIME / 2)
				{
					auto size = m_spRenderer[i].lock()->GetDrawSize();
					size *= 1.02f;
					m_spRenderer[i].lock()->SetDrawSize(size);
				}
				else
				{
					auto size = m_spRenderer[i].lock()->GetDrawSize();
					size *= 0.98f;
					m_spRenderer[i].lock()->SetDrawSize(size);
				}
			}
			m_nFrame++;
		}
		// 演出終了
		else
		{
			// 色変更
			for (int i = 0; i < 4; ++i)
			{
				m_spRenderer[i].lock()->SetColor(Vector3::zero());
			}
			m_bPerform = false;
			m_nFrame = 0;
		}
	}
}