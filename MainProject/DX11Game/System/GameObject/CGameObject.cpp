/**
*
* @file		CGameObject.cpp
* @brief	�Q�[���I�u�W�F�N�g�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/28	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/GameObject/CGameObject.h>
#include <System/Component/CTransform.h>
#include <System/GameObject/CGameObjectManager.h>

/**
* @brief	�R���X�g���N�^
*/
CGameObject::CGameObject()
	: m_tag("None")
	, m_isActive(true)
	, m_eObjectID(EObjectType::None)
{
	
}


/**
* @brief	�f�X�g���N�^
*/
CGameObject::~CGameObject()
{

}


/**
* @brief	������
*/
void CGameObject::Init()
{
	m_spGameObject = m_self.lock();

	// �g�����X�t�H�[���쐬
	m_spTransform = AddComponent<CTransform>();
	m_spTransform.lock()->SetGameObject(m_spGameObject);
}


/**
* @brief	�I������
*/
void CGameObject::Uninit()
{

}


/**
* @brief	�X�V����
*/
void CGameObject::Update()
{
	std::for_each(m_spComponentList.begin(),m_spComponentList.end(),
		[](std::weak_ptr<CComponent> com)
	{
		com.lock()->Update();
	});
}


/**
* @brief	���g�̍폜
* @param	selfObj		���g�̃Q�[���I�u�W�F�N�g
*/
void CGameObject::Destroy()
{
	// �q�I�u�W�F�N�g�����݂���ꍇ�q�I�u�W�F�N�g���폜
	while (m_spTransform.lock()->GetChildList().size() > 0)
	{
		auto childObj = m_spTransform.lock()->GetChildList().begin()->lock();
		childObj->Destroy();
	}
	
	// ���g�̍폜
	GAMEOBJECT_MANAGER->DestroyGameObject(m_self);
}