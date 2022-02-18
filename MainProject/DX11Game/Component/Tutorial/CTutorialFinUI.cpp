/**
*
* @file		CTutorialFinUI.cpp
* @brief	チュートリアル終了UIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	実装開始
*
*/

/** インクルード部 */
#include <Component/Tutorial/CTutorialFinUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneSelect.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/CInput.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>
#include <Component/Title/CButton.h>

/** マクロ定義 */
namespace
{
	const Vector3	TEX_SIZE	= Vector3(500.0f, 600.0f, 1.0f);
	const float		MOVE_SPEED	= 12.0f;
	const Vector3	TEX_POS		= Vector3(0.0f, -300.0f, 0.0f);
}

/**
* @brief	コンストラクタ
*/
CTutorialFinUI::CTutorialFinUI()
	: m_nFrame(0)
	, m_bIsCreate(false)
{

}


/**
* @brief	デストラクタ
*/
CTutorialFinUI::~CTutorialFinUI()
{

}


/**
* @brief	生成時
*/
void CTutorialFinUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Sprite");
	// 名前設定
	obj->SetName("TutorialFinUI");
	// コンポーネントID設定
	SetID(Script);
	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetDrawSize(TEX_SIZE);
	sprite->SetTexture(ETexture::TutorialFin);
	m_spSprite = sprite;
}


/**
* @brief	破棄時
*/
void CTutorialFinUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CTutorialFinUI::Update()
{
	auto pos = m_spTransform.lock()->GetPosition();
	pos->x -= MOVE_SPEED;
	if (pos->x <= 0.0f)
	{
		pos->x = 0.0f;
		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			SCENE_MANAGER->SetNextScene<CSceneSelect>();
		}
		if (!m_bIsCreate)
		{
			const auto& obj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS).lock();
			obj->AddComponent<CButton>();
			m_bIsCreate = true;
		}
	}
	m_spTransform.lock()->SetPosition(pos);
}