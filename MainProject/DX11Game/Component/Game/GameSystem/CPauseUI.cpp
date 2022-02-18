/**
*
* @file		CPauseUI.cpp
* @brief	ポーズUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/GameSystem/CPauseUI.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Scene/CGameManager.h>
#include <System/CInput.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>
#include <Component/Game/GameSystem/CGameBackUI.h>
#include <Component/Game/GameSystem/CGameFinUI.h>

/** マクロ定義 */
namespace
{
	const Vector3 TEX_SIZE = Vector3(1280.0f, 720.0f, 1.0f);
	const Vector3 TEX_POS1 = Vector3(200.0f, 250.0f, 0.0f);
	const Vector3 TEX_POS2 = Vector3(-200.0f, 250.0f, 0.0f);
}

/**
* @brief	コンストラクタ
*/
CPauseUI::CPauseUI()
	: m_bBackGame(true)
{

}


/**
* @brief	デストラクタ
*/
CPauseUI::~CPauseUI()
{

}


/**
* @brief	生成時
*/
void CPauseUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Sprite");

	// 名前設定
	obj->SetName("PauseUI");

	// コンポーネントID
	SetID(Script);

	// スプライト追加
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Pause);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;

	// ゲームに戻るUI生成
	const auto& backObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS2).lock();
	const auto& backCom = backObj->AddComponent<CGameBackUI>();
	backCom.lock()->SetSelect(true);
	m_spSelectObj[0] = backObj;

	// ゲーム終了UI生成
	const auto& finObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS1).lock();
	const auto& finCom = finObj->AddComponent<CGameFinUI>();
	finCom.lock()->SetSelect(false);
	m_spSelectObj[1] = finObj;
}


/**
* @brief	破棄時
*/
void CPauseUI::OnDestroy()
{
	CScriptBase::OnDestroy();
	m_spSelectObj[0].lock()->Destroy();
	m_spSelectObj[0].reset();
	m_spSelectObj[1].lock()->Destroy();
	m_spSelectObj[1].reset();
}


/**
* @brief	更新処理
*/
void CPauseUI::Update()
{
	m_spSelectObj[0].lock()->Update();
	m_spSelectObj[1].lock()->Update();
}


/**
* @brief	選択
* @param	bSelect		true/選択1 , false/選択2
*/
void CPauseUI::Select(bool bSelect)
{
	if (bSelect)
	{
		m_spSelectObj[0].lock()->GetComponent<CGameBackUI>().lock()->SetSelect(true);
		m_spSelectObj[1].lock()->GetComponent<CGameFinUI>().lock()->SetSelect(false);
	}
	else
	{
		m_spSelectObj[0].lock()->GetComponent<CGameBackUI>().lock()->SetSelect(false);
		m_spSelectObj[1].lock()->GetComponent<CGameFinUI>().lock()->SetSelect(true);
	}
}