/**
*
* @file		CButton.cpp
* @brief	ボタンクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	実装開始
*
*/

/** インクルード部 */
#include <Component/Title/CButton.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const Vector3	TEX_SIZE = Vector3(300.0f, 150.0f, 1.0f);
	const float		INCREASE = 0.02f;
}

/**
* @brief	コンストラクタ
*/
CButton::CButton()
	: m_fAlpha(0.0f)
	, m_bIsUp(true)
{

}


/**
* @brief	デストラクタ
*/
CButton::~CButton()
{

}


/**
* @brief	生成時
*/
void CButton::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	//タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("Button");
	// コンポーネントID設定
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Button);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CButton::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新
*/
void CButton::Update()
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
	m_spSprite.lock()->SetAlpha(m_fAlpha);
}