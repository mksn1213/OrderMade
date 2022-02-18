/**
*
* @file		CTransformSystem.cpp
* @brief	�g�����X�t�H�[���V�X�e���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CTransformSystem.h>
#include <System/Component/CTransform.h>
#include <System/GameObject/CGameObject.h>
#include <algorithm>

/**
* @brief	�R���X�g���N�^
*/
CTransformSystem::CTransformSystem()
{

}


/**
* @brief	�f�X�g���N�^
*/
CTransformSystem::~CTransformSystem()
{

}


/**
* @brief	����������
*/
void CTransformSystem::OnCreate()
{

}


/**
* @brief	�폜������
*/
void CTransformSystem::OnDestroy()
{

}


/**
* @brief	�X�V������
*/
void CTransformSystem::OnUpdate()
{
	std::for_each(m_pComponentList.begin(), m_pComponentList.end(),
		[](CTransform* transform)
		{
			// �A�N�e�B�u��Ԃ��e�I�u�W�F�N�g�����݂��Ȃ��ꍇ�X�V
			if (transform->m_spGameObject.lock()->IsActive() && !transform->GetParent().lock())	transform->Update();
		});
}