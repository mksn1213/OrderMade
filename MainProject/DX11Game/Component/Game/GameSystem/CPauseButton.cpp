/**
*
* @file		CPauseButton.cpp
* @brief	ポーズボタンクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/GameSystem/CPauseButton.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const Vector3 TEX_SIZE = Vector3(300.0f, 150.0f, 1.0f);
}

/**
* @brief	コンストラクタ
*/
CPauseButton::CPauseButton()
{

}


/**
* @brief	デストラクタ
*/
CPauseButton::~CPauseButton()
{

}


/**
* @brief	生成時
*/
void CPauseButton::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("PauseButton");
	// コンポーネントID設定
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::PauseButton);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CPauseButton::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CPauseButton::Update()
{

}