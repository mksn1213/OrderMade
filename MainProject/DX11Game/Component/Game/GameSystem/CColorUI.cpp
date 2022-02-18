/**
*
* @file		CColorUI.cpp
* @brief	カラーUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/GameSystem/CColorUI.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const Vector3 TEX_SIZE = Vector3(100.0f, 100.0f, 1.0f);
}

/**
* @brief	コンストラクタ
*/
CColorUI::CColorUI()
{

}


/**
* @brief	デストラクタ
*/
CColorUI::~CColorUI()
{

}


/**
* @brief	生成時
*/
void CColorUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("ColorUI");
	// コンポーネントID
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Color);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CColorUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CColorUI::Update()
{

}