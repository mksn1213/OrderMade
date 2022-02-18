/**
*
* @file		CSelectUserGuideUI.cpp
* @brief	操作ガイドUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	実装開始
*
*/

/** インクルード部 */
#include <Component/Select/CSelectUserGuideUI.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const Vector3 TEX_SIZE = Vector3(1280, 100.0f, 1.0f);
}

/**
* @brief	コンストラクタ
*/
CSelectUserGuideUI::CSelectUserGuideUI()
{

}


/**
* @brief	デストラクタ
*/
CSelectUserGuideUI::~CSelectUserGuideUI()
{

}


/**
* @brief	生成時
*/
void CSelectUserGuideUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("UserGuideUI");
	// コンポーネントID設定
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::SelectUserGuide);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CSelectUserGuideUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CSelectUserGuideUI::Update()
{

}