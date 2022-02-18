/**
*
* @file		CResultScreen.cpp
* @brief	リザルト画面クラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	実装開始
*
*/

/** インクルード部 */
#include <Component/Result/CResultScreen.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/**
* @brief	コンストラクタ
*/
CResultScreen::CResultScreen()
{

}


/**
* @brief	デストラクタ
*/
CResultScreen::~CResultScreen()
{

}


/**
* @brief	生成時
*/
void CResultScreen::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Sprite");

	// 名前設定
	obj->SetName("ResultScreen");

	// コンポーネントID
	SetID(Script);

	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::ResultScene);
	sprite->SetDrawSize(Vector3(1280.0f, 720.0f, 1.0f));
}


/**
* @brief	破棄時
*/
void CResultScreen::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CResultScreen::Update()
{

}
