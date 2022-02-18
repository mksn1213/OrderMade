/**
*
* @file		CFade.cpp
* @brief	フェードクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/01/14	実装開始
*
*/

/** インクルード部 */
#include <System/CFade.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const float INCREASE = 0.01f;
}

/**
* @brief	コンストラクタ
*/
CFade::CFade()
	: m_eFadeState(EFade::FADE_IN)
	, m_fParam(1.0f)
{

}


/**
* @brief	デストラクタ
*/
CFade::~CFade()
{

}


/**
* @brief	生成時
*/
void CFade::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Sprite");

	// 名前設定
	obj->SetName("Fade");

	// コンポーネントID
	SetID(Script);

	// スプライト追加
	const auto& renderer = obj->AddComponent<CSpriteRenderer>().lock();
	renderer->SetTexture(ETexture::Fade);
	renderer->SetEffectTexture(ETexture::Dissolve);
	renderer->SetDrawSize(Vector3(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f));
	m_spRenderer = renderer;

	// シェーダーセット
	m_spGameObject.lock()->SetShader(Simple2DVS, DissolvePS);
}


/**
* @brief	破棄時
*/
void CFade::OnDestroy()
{
}


/**
* @brief	更新処理
*/
void CFade::Update()
{
	if (m_eFadeState == EFade::FADE_NONE)	return;
	
	// フェードイン処理
	if (m_eFadeState == EFade::FADE_IN)
	{
		m_fParam -= INCREASE;
		if (m_fParam < 0.0f)
		{
			m_fParam = 0.0f;
			// フェード終了
			m_eFadeState = EFade::FADE_NONE;
		}
	}
	// フェードアウト処理
	else
	{
		m_fParam += INCREASE;
		if (m_fParam > 1.0f)
		{
			m_fParam = 1.0f;
			// シーン切り替え
			SCENE_MANAGER->SetSceneChange();
			// フェードイン開始
			m_eFadeState = EFade::FADE_IN;
		}
	}
}


/**
* @brief	フェードアウト開始
*/
void CFade::StartFadeOut()
{
	m_eFadeState = EFade::FADE_OUT;
}