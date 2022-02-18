/**
*
* @file		CSceneBase.cpp
* @brief	シーンベースクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	実装開始
*
*/

/** インクルード部 */
#include <Scene/CSceneBase.h>
#include <System/Resource/CModelManager.h>
#include <System/Renderer/AssimpModel.h>

/**
* @brief	コンストラクタ
*/
CSceneBase::CSceneBase()
	: m_eSceneType(SceneTitle)
{
	
}


/**
* @brief	デストラクタ
*/
CSceneBase::~CSceneBase()
{
}