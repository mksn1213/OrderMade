/**
*
* @file		CTutorialOperateUI.cpp
* @brief	チュートリアル説明UIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	実装開始
*
*/

/** インクルード部 */
#include <Component/Tutorial/CTutorialOperateUI.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const Vector3	TEX_SIZE1 = Vector3(300.0f, 300.0f, 0.0f);
	const Vector3	TEX_SIZE2 = Vector3(300.0f, 380.0f, 0.0f);
	const Vector3	TEX_SIZE3 = Vector3(300.0f, 200.0f, 0.0f);
	const Vector3	TEX_SIZE4 = Vector3(300.0f, 380.0f, 0.0f);
}

/**
* @brief	コンストラクタ
*/
CTutorialOperateUI::CTutorialOperateUI()
{

}


/**
* @brief	デストラクタ
*/
CTutorialOperateUI::~CTutorialOperateUI()
{

}


/**
* @brief	生成時
*/
void CTutorialOperateUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("TutorialOperateUI");
	// コンポーネントID設定
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CTutorialOperateUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CTutorialOperateUI::Update()
{

}


/**
* @brief	テクスチャセット
* @param	nStageNo	ステージ番号
*/
void CTutorialOperateUI::SetTexture(int nStageNo)
{
	const auto& sprite = m_spSprite.lock();
	switch (nStageNo)
	{
	case 0:	sprite->SetTexture(ETexture::TutorialGuide1);
			sprite->SetDrawSize(TEX_SIZE1);					break;
	case 1:	sprite->SetTexture(ETexture::TutorialGuide2);	
			sprite->SetDrawSize(TEX_SIZE2);					break;
	case 2:	sprite->SetTexture(ETexture::TutorialGuide3);	
			sprite->SetDrawSize(TEX_SIZE3);					break;
	case 3:	sprite->SetTexture(ETexture::TutorialGuide4);	
			sprite->SetDrawSize(TEX_SIZE4);					break;
	default:												break;
	}
}