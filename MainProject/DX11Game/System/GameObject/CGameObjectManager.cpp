/**
*
* @file		CGameObjectManager.cpp
* @brief	ゲームオブジェクト管理クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	実装開始
* @date		2021/11/30	オブジェクト管理からゲームオブジェクト管理に変更
* @date		2022/01/23	シングルトン継承
*
*/

/** インクルード部 */
#include <System/GameObject/CGameObjectManager.h>
#include <System/CDebugProc.h>
#include <System/Graphics/CGraphics.h>
#include <System/Texture/TextureFactory.h>
#include <System/Graphics/ShaderList.h>
#include <System/Renderer/CSpriteRenderer.h>

/**
* @brief	コンストラクタ
*/
CGameObjectManager::CGameObjectManager()
{
	
}


/**
* @brief	デストラクタ
*/
CGameObjectManager::~CGameObjectManager()
{

}


/**
* @brief	生成時
*/
HRESULT CGameObjectManager::Init()
{
	m_spGameObjectList.clear();
	return S_OK;
}


/**
* @brief	終了処理
*/
void CGameObjectManager::Uninit()
{
	// オブジェクト全て削除
	for (auto it = m_spGameObjectList.begin(); it != m_spGameObjectList.end();)
	{
		(*it)->RemoveComponentAll();
		it = m_spGameObjectList.erase(it);
	}
	m_spGameObjectList.clear();

	// コライダーリストクリア
	CCollider::ClearList();
}