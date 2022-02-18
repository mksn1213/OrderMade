/**
*
* @file		CPlayer.cpp
* @brief	�v���C���[�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/13  �����J�n
* @date		2021/12/03	�R���|�[�l���g�ɕύX
* @data		2021/12/09	�^�[�Q�b�g�|�C���g�̃Q�[���I�u�W�F�N�g�쐬
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/CPlayer.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Factory/CStageFactory.h>
#include <System/CInput.h>
#include <Component/Game/Player/Action/CAction.h>
#include <System/Resource/CModelManager.h>
#include <System/Camera/CCameraManager.h>
#include <System/Sound/CSound.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <System/Component/CTransform.h>
#include <System/Resource/ModelTypeID.h>
#include <Component/Game/Player/CPlayerTarget.h>
#include <Component/Game/Player/Action/GameUI/CActionGaugeUI.h>
#include <System/Component/CRigidbody.h>

/** �}�N����` */
namespace
{
	const float SPEED = 0.2f;			// �ړ����x
	const float ROTATE_RATE = 0.2f;		// ��]
}

/**
* @brief	�R���X�g���N�^
*/
CPlayer::CPlayer()
	: m_pModel(nullptr)
	, m_bHasItem(false)
	, m_bIsAction(false)
	, m_bOldIsAction(false)
	, m_rotDest(Vector3::zero())

{
	
}


/**
* @brief	�f�X�g���N�^
*/
CPlayer::~CPlayer()
{
	if (m_pModel != nullptr)	m_pModel = nullptr;
}


/**
* @brief	������
*/
void CPlayer::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Player");

	// ���O�ݒ�
	obj->SetName("Player");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Player);
	m_pModel = MODEL_MANAGER->GetModel(EModelType::Player);
	// �A�j���[�V�����Z�b�g
	m_pModel->SetAnimIndex(3);
	m_pModel->SetAnimTime(1.5f);

	// ���W�b�h�{�f�B�ǉ�
	const auto& rigidbody = obj->AddComponent<CRigidbody>().lock();
	rigidbody->SetUseGravity(true);
	rigidbody->SetUsePhysics(true);
	m_spRigidbody = rigidbody;

	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(5.0f, 10.0f, 10.0f));
	collider->m_pMainScript = this;

	// �����蔻�茳�t���OON
	collider->SetCollisionFlag(true);

	// �^�[�Q�b�g�I�u�W�F�N�g����
	m_spTargetPoint = CStageFactory::CreateGameObject(EObjectType::PlayerTarget);

	// �e�q�֌W������
	CTransform::SetParentChildRelation(m_spGameObject, m_spTargetPoint, EDirection::Front, 10.0f);
	
	// �v���C���[�Z�b�g
	m_spTargetPoint.lock()->GetComponent<CPlayerTarget>().lock()->m_spPlayer = obj->GetComponent<CPlayer>();

	// �J�����ɃZ�b�g
	CAMERA->Get(0)->SetChaseTarget(m_spTransform);

	// SE�{�����[���Z�b�g
	SOUND_MANAGER->SetVolume(SE_TAKE, 2.0f);
	SOUND_MANAGER->SetVolume(SE_PUT, 2.0f);
}


/**
* @brief	�j����
*/
void CPlayer::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CPlayer::Update()
{
	if (m_bOldIsAction && !m_bIsAction)
	{
		m_spGameObject.lock()->RemoveComponent<CAction>();
		m_bOldIsAction = m_bIsAction;
	}

	// �A�N�V�������͓��삵�Ȃ�
	if (m_bIsAction)
	{
		m_pModel->SetAnimIndex(3);
		m_bOldIsAction = m_bIsAction;
		return;
	}

	// �ړ��X�V
	MoveUpdate();

	// ��]�X�V
	AngleUpdate();
}


/**
* @brief	�ړ��X�V
*/
void CPlayer::MoveUpdate()
{
	m_pModel->SetAnimIndex(3);

	if (CInput::GetKeyPress(VK_A))
	{
		if (CInput::GetKeyPress(VK_W))			//-----���O
		{
			m_spRigidbody.lock()->AddForce(Vector3(-SPEED, 0.0f, SPEED));
			m_rotDest->y = XM_PI * 0.75f;
		}
		else if (CInput::GetKeyPress(VK_S))		//-----����
		{
			m_spRigidbody.lock()->AddForce(Vector3(-SPEED, 0.0f, -SPEED));
			m_rotDest->y = XM_PI * 0.25f;
		}
		else									//-----��
		{
			m_spRigidbody.lock()->AddForce(Vector3(-SPEED, 0.0f, 0.0f));
			m_rotDest->y = XM_PIDIV2;
		}
		m_pModel->SetAnimIndex(0);
	}
	else if (CInput::GetKeyPress(VK_D))
	{
		if (CInput::GetKeyPress(VK_W))			//-----�E�O
		{
			m_spRigidbody.lock()->AddForce(Vector3(SPEED, 0.0f, SPEED));
			m_rotDest->y = -XM_PI * 0.75f;
		}
		else if (CInput::GetKeyPress(VK_S))		//-----�E��
		{
			m_spRigidbody.lock()->AddForce(Vector3(SPEED, 0.0f, -SPEED));
			m_rotDest->y = -XM_PI * 0.25f;
		}
		else									//-----�E
		{
			m_spRigidbody.lock()->AddForce(Vector3(SPEED, 0.0f, 0.0f));
			m_rotDest->y = -XM_PIDIV2;
		}
		m_pModel->SetAnimIndex(0);
	}
	else if (CInput::GetKeyPress(VK_W))			//-----�O
	{
		m_spRigidbody.lock()->AddForce(Vector3(0.0f, 0.0f, SPEED));
		m_rotDest->y = XM_PI;
		m_pModel->SetAnimIndex(0);
	}
	else if (CInput::GetKeyPress(VK_S))			//-----��
	{
		m_spRigidbody.lock()->AddForce(Vector3(0.0f, 0.0f, -SPEED));
		m_rotDest->y = 0.0f;
		m_pModel->SetAnimIndex(0);
	}	
}


/**
* @brief	�p�x�X�V
*/
void CPlayer::AngleUpdate()
{
	// �ړI�̊p�x�܂ł̍���
	Vector3 rotate = m_spTransform.lock()->GetRotation();
	float fDiffRotY = m_rotDest->y - XMConvertToRadians(rotate->y);
	if (fDiffRotY > XM_PI)	fDiffRotY -= XM_2PI;
	if (fDiffRotY < -XM_PI)	fDiffRotY += XM_2PI;

	// �ړI�̊p�x�܂Ŋ�����������
	rotate->y += XMConvertToDegrees(fDiffRotY * ROTATE_RATE);
	if (rotate->y > XM_PI)rotate->y -= XMConvertToDegrees(XM_2PI);
	else rotate->y += XMConvertToDegrees(XM_2PI);

	// �p�x�𔽉f
	m_spTransform.lock()->SetRotation(rotate);
}


/**
* @brief	���������ۂ̏���
* @param	collider		����̃R���C�_�[
*/
void CPlayer::OnCollision(std::weak_ptr<CCollider> collider)
{

}


/**
* @brief	�A�C�e���̃Z�b�g
* @param	item		�Z�b�g����A�C�e��
*/
void CPlayer::SetItem(std::weak_ptr<CGameObject> item)
{
	m_spItem = item.lock();
	m_bHasItem = true;
	// SE�Đ�
	SOUND_MANAGER->Play(SE_TAKE);
}


/**
* @brief	�A�C�e���̉��
*/
void CPlayer::ReleaseItem()
{
	m_spItem.reset();
	m_bHasItem = false;
	// SE�Đ�
	SOUND_MANAGER->Play(SE_PUT);
}