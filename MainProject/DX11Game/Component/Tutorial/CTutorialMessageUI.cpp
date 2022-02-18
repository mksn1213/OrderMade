/**
*
* @file		CTutorialMessageUI.cpp
* @brief	チュートリアルメッセージUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	実装開始
*
*/

/** インクルード部 */
#include <Component/Tutorial/CTutorialMessageUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const Vector3	TEX_SIZE	= Vector3(500.0f, 200.0f, 1.0f);
	const float		MOVE_SPEED	= 12.0f;
	const int		STAY_TIME	= 60;
}

/**
* @brief	コンストラクタ
*/
CTutorialMessageUI::CTutorialMessageUI()
	: m_nFrame(0)
{

}


/**
* @brief	デストラクタ
*/
CTutorialMessageUI::~CTutorialMessageUI()
{

}


/**
* @brief	生成時
*/
void CTutorialMessageUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("TutorialMessageUI");
	// コンポーネントID設定
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CTutorialMessageUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CTutorialMessageUI::Update()
{
	// フェード中でない場合
	if (SCENE_MANAGER->GetFadeState() == CFade::EFade::FADE_NONE)
	{
		auto pos = m_spTransform.lock()->GetPosition();
		pos->x -= MOVE_SPEED;
		if (pos->x <= 0.0f)
		{
			if (m_nFrame < STAY_TIME)
			{
				pos->x = 0.0f;
			}
			m_nFrame++;
		}
		m_spTransform.lock()->SetPosition(pos);
	}
}


/**
* @brief	テクスチャセット
* @param	nStageNo	ステージ番号
*/
void CTutorialMessageUI::SetTexture(int nStageNo)
{
	switch (nStageNo)
	{
	case 0:	m_spSprite.lock()->SetTexture(ETexture::TutorialMessage1);	break;
	case 1:	m_spSprite.lock()->SetTexture(ETexture::TutorialMessage2);	break;
	case 2:	m_spSprite.lock()->SetTexture(ETexture::TutorialMessage3);	break;
	case 3:	m_spSprite.lock()->SetTexture(ETexture::TutorialMessage4);	break;
	default:															break;
	}
}