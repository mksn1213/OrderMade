/**
*
* @file		CBakeAction.cpp
* @brief	�Ă��A�N�V�����N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	�����J�n
* @date		2021/12/19	�R���|�[�l���g�ɕύX
* @date		2021/12/28	�A�N�V�����Q�[�W�ǉ�
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Potted/Action/CBakeAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Factory/CStageFactory.h>
#include <System/Effect/CEffectManager.h>
#include <Component/Tutorial/CTutorialManager.h>
#include <Scene/CSceneManager.h>
#include <System/Sound/CSound.h>

// �R���|�[�l���g
#include <Component/Game/Potted/COven.h>
#include <Component/Game/Potted/CClay.h>

/** �}�N����` */
namespace
{
	const int TIME = 300;					// �A�N�V��������
	const int EFFECT_PLAY_INTERVAL = 20;	// �G�t�F�N�g�Đ��Ԋu
}

/**
* @brief	�R���X�g���N�^
*/
CBakeAction::CBakeAction()
	: m_nFrame(EFFECT_PLAY_INTERVAL)
	, m_effectPos(Vector3::zero())
{

}


/**
* @brief	�f�X�g���N�^
*/
CBakeAction::~CBakeAction()
{

}


/**
* @brief	������
*/
void CBakeAction::OnCreate()
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
	SOUND_MANAGER->SetVolume(SE_BAKE, 3.0f);
	SOUND_MANAGER->Play(SE_BAKE);

	// �G�t�F�N�g�`����W�����O�Ɍv�Z���Ă���
	XMFLOAT4X4 localWorld;
	XMStoreFloat4x4(&localWorld, XMMatrixIdentity());
	localWorld._41 = 6.0f;
	localWorld._42 = 30.0f;
	localWorld._43 = 0.0f;
	auto mtx = XMLoadFloat4x4(&localWorld);
	mtx *= XMLoadFloat4x4(&m_spTransform.lock()->GetWorldMatrix());
	XMFLOAT4X4 world;
	XMStoreFloat4x4(&world, XMMatrixIdentity());
	XMStoreFloat4x4(&world, mtx);
	m_effectPos = Vector3(world._41, world._42, world._43);
}


/**
* @brief	�X�V
*/
void CBakeAction::Update()
{
	// �G�t�F�N�g�Đ�
	if (m_nFrame > EFFECT_PLAY_INTERVAL)
	{
		// ���G�t�F�N�g
		Vector3 pos = m_spTargetItem.lock()->m_spTransform.lock()->GetPosition();
		pos->y -= 10.0f;
		EFFECT_MANAGER->Play(EEffectType::OvenFire, pos);
		
		// ���G�t�F�N�g
		EFFECT_MANAGER->Play(EEffectType::OvenSmoke, m_effectPos);
		m_nFrame = 0;
	}
	m_nFrame++;

	// �X�V�o���Ȃ���ΏI��
	if (!IsUpdate())
	{
		// �A�N�V�����I�����̏���
		EndProcess();
		// �A�N�V�����t���OOFF
		m_spGameObject.lock()->GetComponent<COven>().lock()->SetActionFlag(false);
		// SE��~
		SOUND_MANAGER->Stop(SE_BAKE);
		return;
	}
}


/**
* @brief	�A�N�V�����I�����̏���
*/
void CBakeAction::EndProcess()
{
	// �S�y�I�u�W�F�N�g�̍폜
	m_spTargetItem.lock()->Destroy();
	// ���A���I�u�W�F�N�g�̐���
	const auto& pottedObj = CStageFactory::CreateGameObject(EObjectType::Potted);
	// �e�q�֌W�����
	CTransform::SetParentChildRelation(m_spGameObject, pottedObj, EDirection::Up, 12.0f,EDirection::Front,5.0f);

	// �A�N�V�����Q�[�W�폜
	DeleteActionGauge();

	// �`���[�g���A���V�[���������ꍇ
	if (SCENE_MANAGER->GetScene()->GetSceneType() == ESceneType::SceneTutorial)
	{
		if (TUTORIAL_MANAGER->GetStageNo() == 2)
		{
			TUTORIAL_MANAGER->Fin();
		}
	}
}
