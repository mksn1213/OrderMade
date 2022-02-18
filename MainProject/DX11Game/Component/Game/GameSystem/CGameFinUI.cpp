/**
*
* @file		CGameFinUI.cpp
* @brief	ゲーム終了UIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/GameSystem/CGameFinUI.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const Vector3	TEX_SIZE = Vector3(300.0f, 150.0f, 1.0f);
	const float		INCREASE = 0.05f;
}

/**
* @brief	コンストラクタ
*/
CGameFinUI::CGameFinUI()
	: m_bIsSelect(false)
	, m_fAlpha(0.0f)
	, m_bIsUp(true)
{

}


/**
* @brief	デストラクタ
*/
CGameFinUI::~CGameFinUI()
{

}


/**
* @brief	生成時
*/
void CGameFinUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("GameFinUI");
	// コンポーネントID
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::GameFin);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CGameFinUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CGameFinUI::Update()
{
	if (m_bIsSelect)
	{
		if (m_bIsUp)
		{
			m_fAlpha += INCREASE;
			if (m_fAlpha >= 1.0f)	m_bIsUp = false;
		}
		else
		{
			m_fAlpha -= INCREASE;
			if (m_fAlpha <= 0.0f)	m_bIsUp = true;
		}
	}
	else
	{
		m_fAlpha = 1.0f;
	}
	m_spSprite.lock()->SetAlpha(m_fAlpha);
}