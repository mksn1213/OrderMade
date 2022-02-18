/**
*
* @file		CCollisionSystem.cpp
* @brief	コリジョンシステムクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CCollisionSystem.h>
#include <System/Component/CCollider.h>
#include <System/GameObject/CGameObject.h>
#include <algorithm>

/**
* @brief	コンストラクタ
*/
CCollisionSystem::CCollisionSystem()
{

}


/**
* @brief	デストラクタ
*/
CCollisionSystem::~CCollisionSystem()
{

}


/**
* @brief	生成時処理
*/
void CCollisionSystem::OnCreate()
{

}


/**
* @brief	削除時処理
*/
void CCollisionSystem::OnDestroy()
{

}

/**
* @brief	更新時処理
*/
void CCollisionSystem::OnUpdate()
{
	std::for_each(m_pComponentList.begin(),m_pComponentList.end(),
		[](CCollider* collider)
		{
			if (collider->m_spGameObject.lock()->IsActive())	collider->Update();
		});
}
