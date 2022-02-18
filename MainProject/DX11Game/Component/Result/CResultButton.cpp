/**
*
* @file		CResultButton.cpp
* @brief	リザルトボタンクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	実装開始
*
*/

/** インクルード部 */
#include <Component/Result/CResultButton.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/**
* @brief	コンストラクタ
*/
CResultButton::CResultButton()
{

}


/**
* @brief	デストラクタ
*/
CResultButton::~CResultButton()
{

}



/**
* @brief	生成時
*/
void CResultButton::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Sprite");

	// 名前設定
	obj->SetName("ResultButton");

	// コンポーネントID
	SetID(Script);

	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Button);
	sprite->SetDrawSize(Vector3(300.0f, 200.0f, 1.0f));
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CResultButton::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CResultButton::Update()
{

}
