/**
*
* @file		CGiveWaterAction.cpp
* @brief	����^����A�N�V�����N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/07	�����J�n
* @date		2021/12/18	�R���|�[�l���g�ɕύX
* @date		2021/12/28	�A�N�V�����Q�[�W�ǉ�
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CGiveWaterAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Water/CBucket.h>
#include <System/Sound/CSound.h>
#include <System/Utility/Search.h>

// �R���|�[�l���g
#include <Component/Game/Soil/Action/CGrowAction.h>
#include <Component/Game/Soil/CSoil.h>

/** �}�N����` */
namespace
{
	const int TIME = 60;				// �A�N�V����
	const int SE_PLAY_INTERVAL = 20;	// SE�Đ��Ԋu
}

/**
* @brief	�R���X�g���N�^
*/
CGiveWaterAction::CGiveWaterAction()
	: m_nFrame(SE_PLAY_INTERVAL)
{

}


/**
* @brief	�f�X�g���N�^
*/
CGiveWaterAction::~CGiveWaterAction()
{

}


/**
* @brief	������
*/
void CGiveWaterAction::OnCreate()
{
	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �R���|�[�l���gID�ݒ�
	SetID(EComponentType::Action);
	// �^�C�}�[����
	m_pTimer = new CTimer(TIME);
	// �A�N�V�����Q�[�WUI����
	CreateActionGauge(TIME, EDirection::Up, 15.0f);
	// SE�{�����[���Z�b�g
	SOUND_MANAGER->SetVolume(SE_GIVEWATER, 2.0f);
}


/**
* @brief	�X�V����
*/
void CGiveWaterAction::Update()
{
	// SE�Đ�
	if (m_nFrame > SE_PLAY_INTERVAL)
	{
		SOUND_MANAGER->Play(SE_GIVEWATER);
		m_nFrame = 0;
	}
	m_nFrame++;

	// �X�V�o���Ȃ���ΏI��
	if (!IsUpdate())
	{
		// �A�N�V�����I�����̏���
		EndProcess();
		// �A�N�V�����t���OOFF
		m_spGameObject.lock()->GetComponent<CPlayer>().lock()->SetActionFlag(false);
	}
}


/**
* @brief	�A�N�V�����I�����̏���
*/
void CGiveWaterAction::EndProcess()
{
	// ���t���OOFF
	const auto& bucket = m_spTargetItem.lock()->GetComponent<CBucket>().lock();
	bucket->SetWaterFlag(false);
	// �����b�V����A�N�e�B�u��
	bucket->m_spWaterObj.lock()->SetActive(false);

	// �����A�N�V�����ǉ�
	const auto& action = m_spTargetObject.lock()->AddComponent<CGrowAction>();
	const auto& childList = m_spTargetObject.lock()->m_spTransform.lock()->GetChildList();
	const auto& plantObj = SearchExistsList(childList, "Item");
	action.lock()->SetTarget(m_spTargetObject, plantObj);
	m_spTargetObject.lock()->GetComponent<CSoil>().lock()->SetActionFlag(true);

	// �A�N�V�����Q�[�W�폜
	DeleteActionGauge();
}
