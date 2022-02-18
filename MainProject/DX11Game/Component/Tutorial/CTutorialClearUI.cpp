/**
*
* @file		CTutorialClearUI.cpp
* @brief	チュートリアルクリアUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	実装開始
*
*/

/** インクルード部 */
#include <Component/Tutorial/CTutorialClearUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneTutorial.h>
#include <Component/Tutorial/CTutorialManager.h>
#include <System/GameObject/CGameObjectManager.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>
#include <Component/Tutorial/CTutorialFinUI.h>

/** マクロ定義 */
namespace
{
	const Vector3	TEX_POS   = Vector3(900.0f, 0.0f, 0.0f);
	const Vector3	TEX_SIZE  = Vector3(300.0f, 300.0f, 1.0f);
	const int		FIN_FRAME = 120;
}

/**
* @brief	コンストラクタ
*/
CTutorialClearUI::CTutorialClearUI()
	: m_nFrame(0)
	, m_bIsCreate(false)
{

}


/**
* @brief	デストラクタ
*/
CTutorialClearUI::~CTutorialClearUI()
{

}


/**
* @brief	生成時
*/
void CTutorialClearUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("TutorialClearUI");
	// コンポーネントID設定
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetDrawSize(TEX_SIZE);
	sprite->SetTexture(ETexture::TutorialOK);
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CTutorialClearUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CTutorialClearUI::Update()
{
	if (m_nFrame > FIN_FRAME)
	{
		auto stageNo = TUTORIAL_MANAGER->GetStageNo();
		if (stageNo != 3)
		{
			auto scene = SCENE_MANAGER->SetNextScene<CSceneTutorial>();
			scene->SetStageNo(stageNo + 1);
			m_nFrame = 0;
		}
		else
		{
			if (!m_bIsCreate)
			{
				const auto& obj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS).lock();
				obj->AddComponent<CTutorialFinUI>();
				m_bIsCreate = true;
			}
		}
	}
	m_nFrame++;
}