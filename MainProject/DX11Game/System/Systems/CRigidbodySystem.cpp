/**
*
* @file		CRigidbodySystem.cpp
* @brief	���W�b�h�{�f�B�V�X�e���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CRigidbodySystem.h>
#include <System/Component/CRigidbody.h>
#include <System/GameObject/CGameObject.h>
#include <algorithm>

/**
* @brief	�R���X�g���N�^
*/
CRigidbodySystem::CRigidbodySystem()
{

}


/**
* @brief	�R���X�g���N�^
*/
CRigidbodySystem::~CRigidbodySystem()
{

}


/**
* @brief	����������
*/
void CRigidbodySystem::OnCreate()
{

}


/**
* @brief	�폜������
*/
void CRigidbodySystem::OnDestroy()
{

}


/**
* @brief	�X�V������
*/
void CRigidbodySystem::OnUpdate()
{
	std::for_each(m_pComponentList.begin(), m_pComponentList.end(),
		[](CRigidbody* rb)
		{
		if (rb->m_spGameObject.lock()->IsActive())	rb->Update();
		});
}