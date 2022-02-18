/**
*
* @file		CScoreUI.h
* @brief	スコアクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/25	実装開始
* @date		2021/12/22	コンポーネントに変更
* @date		2021/12/30	CScoreからCScoreUIに変更
*
*/

/** インクルード部 */
#include <Component/Game/GameSystem/CScoreUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CGameManager.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const float NUMBER_SPACE	= 30.0f;	// 描画間隔
	const int	NUMBER_FRAME_X	= 10;		// 横フレーム数
	const int	NUMBER_FRAME_Y	= 1;		// 縦フレーム数
	const int	PERFORM_TIME	= 30;		// 演出時間
}

/**
* @brief	コンストラクタ
*/
CScoreUI::CScoreUI()
	: m_uOldScore(0)
	, m_nFrame(0)
	, m_bPerform(false)
{

}


/**
* @brief	デストラクタ
*/
CScoreUI::~CScoreUI()
{

}


/**
* @brief	生成時
*/
void CScoreUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Sprite");

	// 名前設定
	obj->SetName("ScoreUI");

	// コンポーネントID設定
	SetID(Script);

	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Game_Score);
	sprite->SetDrawSize(Vector3(200.0f, 100.0f, 1.0f));
	m_spSprite = sprite;

	// スコアスプライト追加
	unsigned drawScore = 0;
	for (int i = 0; i < 4; ++i)
	{
		auto renderer = obj->AddComponent<CSpriteRenderer>().lock();
		renderer->SetTexture(ETexture::Game_Number);
		renderer->SetDrawSize(Vector3(30.0f, 45.0f, 1.0f));
		renderer->SetColor(Vector3::zero());
		renderer->SetTexSize(Vector3(1.0f / NUMBER_FRAME_X, 1.0f / NUMBER_FRAME_Y, 0.0f));
		renderer->SetLocalPos(Vector3(-NUMBER_SPACE * 1.5f + i * NUMBER_SPACE, 0.0f, 0.0f));
		unsigned n = drawScore % 10;
		drawScore /= 10;
		int u = n % NUMBER_FRAME_X;
		int v = n / NUMBER_FRAME_X;
		renderer->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));		
		m_spRenderer[i] = renderer;
	}

	// シーンタイプ保存
	m_eSceneType = SCENE_MANAGER->GetScene()->GetSceneType();
}


/**
* @brief	破棄時
*/
void CScoreUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CScoreUI::Update()
{
	// チュートリアルシーンだった場合終了
	if (m_eSceneType == ESceneType::SceneTutorial)	return;

	// スコア取得
	unsigned drawScore = GAME_MANAGER->GetScore();

	// スコアが変動した場合
	if (drawScore != m_uOldScore)	m_bPerform = true;

	// テクスチャ座標更新
	for (int i = 3; i >= 0; --i)
	{
		unsigned n = drawScore % 10;
		drawScore /= 10;
		int u = n % NUMBER_FRAME_X;
		int v = n / NUMBER_FRAME_X;
		m_spRenderer[i].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	}

	// 演出関連
	if (m_bPerform)
	{
		if (m_nFrame < PERFORM_TIME)
		{
			// 色変更 + サイズ変更
			for (int i = 0; i < 4; ++i)
			{
				m_spRenderer[i].lock()->SetColor(Vector3::up() * 0.7f);
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

	// 前のスコア保存
	m_uOldScore = GAME_MANAGER->GetScore();
}
