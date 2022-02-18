/**
*
* @file		CScriptSystem.cpp
* @brief	スクリプトシステムクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CScriptSystem.h>
#include <System/Component/CScriptBase.h>
#include <System/GameObject/CGameObject.h>
#include <algorithm>

/**
* @brief	コンストラクタ
*/
CScriptSystem::CScriptSystem()
{

}


/**
* @brief	デストラクタ
*/
CScriptSystem::~CScriptSystem()
{

}


/**
* @brief	生成時処理
*/
void CScriptSystem::OnCreate()
{

}


/**
* @brief	削除時処理
*/
void CScriptSystem::OnDestroy()
{

}


/**
* @brief	更新時処理
*/
void CScriptSystem::OnUpdate()
{
	std::for_each(m_pComponentList.begin(),m_pComponentList.end(),
		[](CScriptBase* script)
		{
			if (script->m_spGameObject.lock()->IsActive())	script->Update();
		});
}
