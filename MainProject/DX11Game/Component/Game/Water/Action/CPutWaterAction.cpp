/**
*
* @file		CPutWaterAction.cpp
* @brief	��������A�N�V�����N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/06	�����J�n
* @date		2021/12/18	�R���|�[�l���g�ɕύX
* @date		2021/12/28	�A�N�V�����Q�[�W�ǉ�
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Water/Action/CPutWaterAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Sound/CSound.h>
#include <System/Effect/CEffectManager.h>

// �R���|�[�l���g
#include <Component/Game/Water/CWell.h>
#include <Component/Game/Water/CBucket.h>

/** �}�N����` */
namespace
{
	const int	TIME = 180;						// �A�N�V��������
	const int	SE_IN_TIME = TIME - TIME / 4;	// ����SE�Đ��^�C�~���O
	const int	SE_OUT_TIME = TIME / 2 / 2;		// �oSE�Đ��^�C�~���O
	const float	PUT_SPEED = 0.4f;				// ���[�J�����W�ړ����x
}

/**
* @brief	�R���X�g���N�^
*/
CPutWaterAction::CPutWaterAction()
	: m_bIsWater(false)
{
	
}


/**
* @brief	�f�X�g���N�^
*/
CPutWaterAction::~CPutWaterAction()
{

}


/**
* @brief	������
*/
void CPutWaterAction::OnCreate()
{
	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �R���|�[�l���gID�ݒ�
	SetID(EComponentType::Action);
	// �^�C�}�[�̐���
	m_pTimer = new CTimer(TIME);
	// �A�N�V�����Q�[�WUI����
	CreateActionGauge(TIME, EDirection::Up, 30.0f, EDirection::Front, 10.0f);
	// SE�{�����[���Z�b�g
	SOUND_MANAGER->SetVolume(SE_WELL_IN, 4.0f);
	SOUND_MANAGER->SetVolume(SE_WELL_OUT, 4.0f);
	SOUND_MANAGER->SetVolume(SE_WELL_PULLEY, 0.5f);
	SOUND_MANAGER->Play(SE_WELL_PULLEY);
}


/**
* @brief	�X�V
*/
void CPutWaterAction::Update()
{
	// �������މ��o����
	if (m_pTimer->GetTime() >= TIME / 2)
	{
		m_spTargetItem.lock()->m_spTransform.lock()->SetLocalPosition(EDirection::Down, PUT_SPEED, true);
		// SE�Đ� + �G�t�F�N�g�Đ�
		if (m_pTimer->GetTime() == SE_IN_TIME)
		{
			SOUND_MANAGER->Play(SE_WELL_IN);
			auto pos = m_spTransform.lock()->GetPosition();
			pos->y += 10.0f;
			EFFECT_MANAGER->Play(EEffectType::Water, pos);
		}
	}
	else
	{
		// ��x�������s
		// �����b�V�����A�N�e�B�u��
		if (!m_bIsWater)
		{
			m_spTargetItem.lock()->GetComponent<CBucket>().lock()->m_spWaterObj.lock()->SetActive(true);
			m_bIsWater = true;
		}
		m_spTargetItem.lock()->m_spTransform.lock()->SetLocalPosition(EDirection::Up, PUT_SPEED, true);
		// SE�Đ�
		if (m_pTimer->GetTime() == SE_OUT_TIME)
		{
			SOUND_MANAGER->Play(SE_WELL_OUT);
			auto pos = m_spTransform.lock()->GetPosition();
			pos->y += 10.0f;
			EFFECT_MANAGER->Play(EEffectType::Water, pos);
		}
	}

	// �X�V�o���Ȃ���ΏI��
	if (!IsUpdate())
	{
		// �A�N�V�����I�����̏���
		EndProcess();
		// �A�N�V�����t���OOFF
		m_spGameObject.lock()->GetComponent<CWell>().lock()->SetActionFlag(false);
		// SE��~
		SOUND_MANAGER->Stop(SE_WELL_PULLEY);
		return;
	}
}


/**
* @brief	�A�N�V�����I�����̏���
*/
void CPutWaterAction::EndProcess()
{
	// ���t���OON
	m_spTargetItem.lock()->GetComponent<CBucket>().lock()->SetWaterFlag(true);
	// �A�N�V�����Q�[�W�폜
	DeleteActionGauge();
}
