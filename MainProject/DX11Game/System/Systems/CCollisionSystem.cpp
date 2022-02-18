/**
*
* @file		CCollisionSystem.cpp
* @brief	�R���W�����V�X�e���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CCollisionSystem.h>
#include <System/Component/CCollider.h>
#include <System/GameObject/CGameObject.h>
#include <algorithm>

/**
* @brief	�R���X�g���N�^
*/
CCollisionSystem::CCollisionSystem()
{

}


/**
* @brief	�f�X�g���N�^
*/
CCollisionSystem::~CCollisionSystem()
{

}


/**
* @brief	����������
*/
void CCollisionSystem::OnCreate()
{

}


/**
* @brief	�폜������
*/
void CCollisionSystem::OnDestroy()
{

}

/**
* @brief	�X�V������
*/
void CCollisionSystem::OnUpdate()
{
	std::for_each(m_pComponentList.begin(),m_pComponentList.end(),
		[](CCollider* collider)
		{
			if (collider->m_spGameObject.lock()->IsActive())	collider->Update();
		});
}
