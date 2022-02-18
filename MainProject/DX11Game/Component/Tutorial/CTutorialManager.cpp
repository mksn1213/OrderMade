/**
*
* @file		CTutorialManager.cpp
* @brief	チュートリアル管理クラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	実装開始
*
*/

/** インクルード部 */
#include <Component/Tutorial/CTutorialManager.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneTutorial.h>
#include <System/GameObject/CGameObjectManager.h>

// コンポーネント
#include <Component/Tutorial/CTutorialMessageUI.h>
#include <Component/Tutorial/CTutorialOperateUI.h>
#include <Component/Tutorial/CTutorialClearUI.h>

/** マクロ定義*/
namespace
{
	const Vector3 TEX_POS1 = Vector3(900.0f, 0.0f, 0.0f);
	const Vector3 TEX_POS2 = Vector3(450.0f, -50.0f, 0.0f);
}

/**
* @brief	コンストラクタ
*/
CTutorialManager::CTutorialManager()
{

}


/**
* @brief	デストラクタ
*/
CTutorialManager::~CTutorialManager()
{

}


/**
* @brief	初期化処理
*/
HRESULT CTutorialManager::Init()
{
	// 変数初期化
	m_bIsFin = false;
	m_bIsCreate = false;

	// チュートリアル説明UI
	const auto& operateObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS2).lock();
	m_spOperateCom = operateObj->AddComponent<CTutorialOperateUI>();

	// チュートリアルメッセージUI
	const auto& messageObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS1).lock();
	m_spMessageCom = messageObj->AddComponent<CTutorialMessageUI>();

	return S_OK;
}


/**
* @brief	終了処理
*/
void CTutorialManager::Uninit()
{

}


/**
* @brief	更新処理
*/
void CTutorialManager::Update()
{
	// チュートリアル終了フラグが立った場合
	if (m_bIsFin)
	{
		if (!m_bIsCreate)
		{
			// クリアUI生成
			const auto& obj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
			obj->AddComponent<CTutorialClearUI>();
			m_bIsCreate = true;
		}
	}
}


/**
* @brief	描画処理
*/
void CTutorialManager::Draw()
{

}


/**
* @brief	ステージ番号セット
* @param	nStageNo	ステージ番号
*/
void CTutorialManager::SetStageNo(int nStageNo)
{
	m_nStageNo = nStageNo;
	m_spMessageCom.lock()->SetTexture(m_nStageNo);
	m_spOperateCom.lock()->SetTexture(m_nStageNo);
}