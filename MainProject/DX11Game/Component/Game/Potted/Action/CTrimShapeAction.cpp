/**
*
* @file		CTrimShapeAction.cpp
* @brief	�`��𐮂���A�N�V�����N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	�����J�n
* @date		2021/12/19	�R���|�[�l���g�ɕύX
* @date		2021/12/28	�A�N�V�����Q�[�W�ǉ�
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Potted/Action/CTrimShapeAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Sound/CSound.h>

// �R���|�[�l���g
#include <Component/Game/Potted/CPotteryWheel.h>
#include <Component/Game/Potted/CClay.h>
#include <System/Renderer/CModelRenderer.h>

/** �}�N����` */
namespace
{
	const int TIME = 240;				// �A�N�V��������
	const int SE_PLAY_INTERVAL = 30;	// SE�Đ��Ԋu
}

/**
* @brief	�R���X�g���N�^
*/
CTrimShapeAction::CTrimShapeAction()
	: m_nFrame(SE_PLAY_INTERVAL)
{

}


/**
* @brief	�f�X�g���N�^
*/
CTrimShapeAction::~CTrimShapeAction()
{

}


/**
* @brief	������
*/
void CTrimShapeAction::OnCreate()
{
	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �R���|�[�l���gID�ݒ�
	SetID(EComponentType::Action);
	// �^�C�}�[�̐���
	m_pTimer = new CTimer(TIME);
	// �A�N�V�����Q�[�WUI����
	CreateActionGauge(TIME, EDirection::Up, 30.0f);
	// SE�{�����[���Z�b�g
	SOUND_MANAGER->SetVolume(SE_TRIM, 5.0f);
}


/**
* @brief	�X�V
*/
void CTrimShapeAction::Update()
{
	// SE�Đ�
	if (m_nFrame > SE_PLAY_INTERVAL)
	{
		SOUND_MANAGER->Play(SE_TRIM);
		m_nFrame = 0;
	}
	m_nFrame++;

	if (m_pTimer->GetTime() == TIME / 2)
	{
		m_spTargetItem.lock()->GetComponent<CModelRenderer>().lock()->SetModel(EModelType::TrimClay);
	}

	// �X�V�o���Ȃ���ΏI��
	if (!IsUpdate())
	{
		// �A�N�V�����I�����̏���
		EndProcess();
		// �A�N�V�����t���OOFF
		m_spGameObject.lock()->GetComponent<CPotteryWheel>().lock()->SetActionFlag(false);
		return;
	}
}


/**
* @brief	�A�N�V�����I�����̏���
*/
void CTrimShapeAction::EndProcess()
{
	// ���H�t���OON
	m_spTargetItem.lock()->GetComponent<CClay>().lock()->SetProcessedFlag(true);
	
	// �A�N�V�����Q�[�W�폜
	DeleteActionGauge();
}
