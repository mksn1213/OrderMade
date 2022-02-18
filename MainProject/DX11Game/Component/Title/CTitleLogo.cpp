/**
*
* @file		CTitleLogo.cpp
* @brief	タイトルロゴクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/11	実装開始
*
*/

/** インクルード部 */
#include <Component/Title/CTitleLogo.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/**
* @brief	コンストラクタ
*/
CTitleLogo::CTitleLogo()
{

}


/**
* @brief	デストラクタ
*/
CTitleLogo::~CTitleLogo()
{

}


/**
* @brief	生成時
*/
void CTitleLogo::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("TitleLogo");
	// コンポーネントID設定
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::TitleLogo);
	sprite->SetDrawSize(Vector3(600.0f, 300.0f, 1.0f));
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CTitleLogo::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CTitleLogo::Update()
{

}