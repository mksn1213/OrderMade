/**
*
* @file		CRigidbodySystem.cpp
* @brief	リジッドボディシステムクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CRigidbodySystem.h>
#include <System/Component/CRigidbody.h>
#include <System/GameObject/CGameObject.h>
#include <algorithm>

/**
* @brief	コンストラクタ
*/
CRigidbodySystem::CRigidbodySystem()
{

}


/**
* @brief	コンストラクタ
*/
CRigidbodySystem::~CRigidbodySystem()
{

}


/**
* @brief	生成時処理
*/
void CRigidbodySystem::OnCreate()
{

}


/**
* @brief	削除時処理
*/
void CRigidbodySystem::OnDestroy()
{

}


/**
* @brief	更新時処理
*/
void CRigidbodySystem::OnUpdate()
{
	std::for_each(m_pComponentList.begin(), m_pComponentList.end(),
		[](CRigidbody* rb)
		{
		if (rb->m_spGameObject.lock()->IsActive())	rb->Update();
		});
}