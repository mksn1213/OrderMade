/**
*
* @file		COptionUI.cpp
* @brief	オプションUIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	実装開始
*
*/

/** インクルード部 */
#include <Component/Title/COptionUI.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/**
* @brief	コンストラクタ
*/
COptionUI::COptionUI()
{

}


/**
* @brief	デストラクタ
*/
COptionUI::~COptionUI()
{

}


/**
* @brief	生成時
*/
void COptionUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	//タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("OptionUI");
	// コンポーネントID設定
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Option);
	sprite->SetDrawSize(Vector3(300.0f, 150.0f, 1.0f));
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void COptionUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新
*/
void COptionUI::Update()
{

}


