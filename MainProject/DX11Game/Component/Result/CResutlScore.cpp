/**
*
* @file		CResultScore.cpp
* @brief	リザルトスコアクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	実装開始
*
*/

/** インクルード部 */
#include <Component/Result/CResultScore.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const float NUMBER_SPACE = 60.0f;	// 描画間隔
	const int	NUMBER_FRAME_X = 10;	// 横フレーム数
	const int	NUMBER_FRAME_Y = 1;		// 縦フレーム数
}

/**
* @brief	コンストラクタ
*/
CResultScore::CResultScore()
{

}


/**
* @brief	デストラクタ
*/
CResultScore::~CResultScore()
{

}


/**
* @brief	生成時
*/
void CResultScore::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("ResultScore");
	// コンポーネントID設定
	SetID(Script);
}


/**
* @brief	破棄時
*/
void CResultScore::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CResultScore::Update()
{

}


/**
* @brief	スコアセット
* @param	nScore	スコア
*/
void CResultScore::SetScore(int nScore)
{
	const auto& obj = m_spGameObject.lock();

	// スプライト追加
	for (int i = 3; i >= 0; --i)
	{
		auto renderer = obj->AddComponent<CSpriteRenderer>().lock();
		renderer->SetTexture(ETexture::Game_Number);
		renderer->SetDrawSize(Vector3(60.0f, 90.0f, 1.0f));
		renderer->SetColor(Vector3::zero());
		renderer->SetTexSize(Vector3(1.0f / NUMBER_FRAME_X, 1.0f / NUMBER_FRAME_Y, 0.0f));
		renderer->SetLocalPos(Vector3(-NUMBER_SPACE * 1.5f + i * NUMBER_SPACE, 0.0f, 0.0f));
		unsigned n = nScore % 10;
		nScore /= 10;
		int u = n % NUMBER_FRAME_X;
		int v = n / NUMBER_FRAME_X;
		renderer->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
		m_spRenderer[i] = renderer;
	}
}