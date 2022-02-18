/**
*
* @file		CTimeUpUI.cpp
* @brief	タイムアップUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/01/13	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/GameSystem/CTimeUpUI.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const float INCREASE_ALPHA = 0.01f;		// アルファ値の増加量
}

/**
* @brief	コンストラクタ
*/
CTimeUpUI::CTimeUpUI()
	: m_fAlpha(0.0f)
{

}


/**
* @brief	デストラクタ
*/
CTimeUpUI::~CTimeUpUI()
{

}


/**
* @brief	生成時
*/
void CTimeUpUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Sprite");

	// 名前設定
	obj->SetName("TimeUpUI");

	// コンポーネントID
	SetID(Script);

	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::TimeUp);
	sprite->SetDrawSize(Vector3(400.0f, 200.0f, 1.0f));
	sprite->SetAlpha(0.0f);
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CTimeUpUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CTimeUpUI::Update()
{
	// 徐々に不透明に
	m_fAlpha += INCREASE_ALPHA;
	if (m_fAlpha >= 1.0f)	m_fAlpha = 1.0f;
	m_spSprite.lock()->SetAlpha(m_fAlpha);
}