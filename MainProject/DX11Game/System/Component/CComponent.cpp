/**
*
* @file		CComponent.cpp
* @brief	�R���|�[�l���g�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/28	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CComponent.h>

/**
* @brief	�R���X�g���N�^
* @param	pObject		�A�^�b�`���Ă���Q�[���I�u�W�F�N�g
*/
CComponent::CComponent(std::weak_ptr<CGameObject> spObj)
	: m_spGameObject(spObj)
{

}


/**
* @brief	�f�X�g���N�^
*/
CComponent::~CComponent()
{

}
