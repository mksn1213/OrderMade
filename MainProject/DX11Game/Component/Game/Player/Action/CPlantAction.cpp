/**
*
* @file		CPlantAction.cpp
* @brief	�A����A�N�V�����N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/28	�����J�n
* @date		2021/12/17	�R���|�[�l���g�ɕύX
* @date		2021/12/28	�A�N�V�����Q�[�W�ǉ�
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CPlantAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Effect/CEffectManager.h>
#include <System/Sound/CSound.h>

// �R���|�[�l���g
#include <Component/Game/Player/CPlayer.h>

/** �}�N����` */
namespace
{
	const int TIME = 60;			// �A�N�V��������
	const int PLAY_INTERVAL = 20;	// SE.�G�t�F�N�g�Đ��Ԋu
}

/**
* @brief	�R���X�g���N�^
*/
CPlantAction::CPlantAction()
	: m_nFrame(PLAY_INTERVAL)

{

}


/**
* @brief	�f�X�g���N�^
*/
CPlantAction::~CPlantAction()
{

}


/**
* @brief	������
*/
void CPlantAction::OnCreate()
{
	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �R���|�[�l���gID�ݒ�
	SetID(EComponentType::Action);
	// �^�C�}�[�̐���
	m_pTimer = new CTimer(TIME);
	// �A�N�V�����Q�[�WUI����
	CreateActionGauge(TIME, EDirection::Up, 15.0f);
	// SE�{�����[���Z�b�g
	SOUND_MANAGER->SetVolume(SE_PLANT, 3.0f);
}


/**
* @brief	�X�V����
*/
void CPlantAction::Update()
{
	if (m_nFrame > PLAY_INTERVAL)
	{
		// SE�Đ�
		SOUND_MANAGER->Play(SE_PLANT);
		m_nFrame = 0;
		// �G�t�F�N�g�Đ�
		Vector3 pos = m_spTargetObject.lock()->m_spTransform.lock()->GetPosition() + Vector3::up()*5.0f;
		EFFECT_MANAGER->Play(EEffectType::PlantSmoke, pos);
	}
	m_nFrame++;

	// �X�V�o���Ȃ���ΏI��
	if (!IsUpdate())
	{
		// �A�N�V�����I�����̏���
		EndProcess();
		// �A�N�V�����t���OOFF
		m_spGameObject.lock()->GetComponent<CPlayer>().lock()->SetActionFlag(false);		
		// SE�Đ���~
		SOUND_MANAGER->Stop(SE_PLANT);
		return;
	}
}


/**
* @brief	�A�N�V�����I�����̏���
*/
void CPlantAction::EndProcess()
{
	// �A�C�e���̃����[�X
	m_spGameObject.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();
	// �e�q�֌W������
	m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(m_spTargetItem);
	// �e�q�֌W�����
	CTransform::SetParentChildRelation(m_spTargetObject, m_spTargetItem, EDirection::Up, 0.0f);
	
	// �A�N�V�����Q�[�W�폜
	DeleteActionGauge();
}
