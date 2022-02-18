/**
*
* @file		CScriptBase.cpp
* @brief	スクリプトベースクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <System/Systems/CScriptSystem.h>
#include <Scene/CSceneManager.h>

/** 静的メンバ */
const EComponentType CScriptBase::comID = EComponentType::Script;

/**
* @brief	コンストラクタ
*/
CScriptBase::CScriptBase()
{

}


/**
* @brief	デストラクタ
*/
CScriptBase::~CScriptBase()
{

}


/**
* @brief	生成時
*/
void CScriptBase::OnCreate()
{
	// トランスフォーム取得
	m_spTransform = m_spGameObject.lock()->GetComponent<CTransform>();
	// システムリストに格納
	CScriptSystem* pSystem = SCENE_MANAGER->GetSystem<CScriptSystem>(EComponentType::Script);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	破棄時
*/
void CScriptBase::OnDestroy()
{
	// システムから除外
	CScriptSystem* pSystem = SCENE_MANAGER->GetSystem<CScriptSystem>(EComponentType::Script);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}