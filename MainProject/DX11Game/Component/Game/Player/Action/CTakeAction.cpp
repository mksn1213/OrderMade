/**
*
* @file		CTakeAction.cpp
* @brief	���A�N�V�����N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	�����J�n
* @date		2021/12/16	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CTakeAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Player/CPlayer.h>


/** �}�N����` */
namespace
{
	const int TIME = 5;
}

/**
* @brief	�R���X�g���N�^
*/
CTakeAction::CTakeAction()
{

}


/**
* @brief	�f�X�g���N�^
*/
CTakeAction::~CTakeAction()
{

}


/**
* @brief	������
*/
void CTakeAction::OnCreate()
{
	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �R���|�[�l���gID�ݒ�
	SetID(EComponentType::Action);
	// �^�C�}�[�̐���
	m_pTimer = new CTimer(TIME);
}


/**
* @brief	�X�V����
*/
void CTakeAction::Update()
{
	// �X�V�o���Ȃ���ΏI��
	if (!IsUpdate())
	{
		// �A�N�V�����I�����̏���
		EndProcess();
		// �A�N�V�����t���OOFF
		m_spGameObject.lock()->GetComponent<CPlayer>().lock()->SetActionFlag(false);
		return;
	}
}


/**
* @brief	�A�N�V�����I�����̏���
*/
void CTakeAction::EndProcess()
{

}