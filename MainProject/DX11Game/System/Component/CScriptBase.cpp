/**
*
* @file		CScriptBase.cpp
* @brief	�X�N���v�g�x�[�X�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <System/Systems/CScriptSystem.h>
#include <Scene/CSceneManager.h>

/** �ÓI�����o */
const EComponentType CScriptBase::comID = EComponentType::Script;

/**
* @brief	�R���X�g���N�^
*/
CScriptBase::CScriptBase()
{

}


/**
* @brief	�f�X�g���N�^
*/
CScriptBase::~CScriptBase()
{

}


/**
* @brief	������
*/
void CScriptBase::OnCreate()
{
	// �g�����X�t�H�[���擾
	m_spTransform = m_spGameObject.lock()->GetComponent<CTransform>();
	// �V�X�e�����X�g�Ɋi�[
	CScriptSystem* pSystem = SCENE_MANAGER->GetSystem<CScriptSystem>(EComponentType::Script);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	�j����
*/
void CScriptBase::OnDestroy()
{
	// �V�X�e�����珜�O
	CScriptSystem* pSystem = SCENE_MANAGER->GetSystem<CScriptSystem>(EComponentType::Script);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}