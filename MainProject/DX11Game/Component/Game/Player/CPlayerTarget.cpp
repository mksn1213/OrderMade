/**
*
* @file		CPlayerTarget.cpp
* @brief	�v���C���[�^�[�Q�b�g�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/20	�����J�n
* @date		2021/12/03	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/CPlayerTarget.h>
#include <System/GameObject/CGameObject.h>
#include <System/CInput.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/CPlayer.h>
#include <System/Component/CRigidbody.h>

/** �}�N����` */
namespace
{
	const float SUBTRACT = 0.6f;
}

/**
* @brief	�R���X�g���N�^
*/
CPlayerTarget::CPlayerTarget()
	: m_bIsTarget(false)
{

}


/**
* @brief	�f�X�g���N�^
*/
CPlayerTarget::~CPlayerTarget()
{

}



/**
* @brief	������
*/
void CPlayerTarget::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Target");
	// ���O�ݒ�
	obj->SetName("PlayerTarget");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �I�u�W�F�N�gID�ݒ�
	obj->SetObjectID(EObjectType::PlayerTarget);
	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(8.0f, 5.0f, 6.0f));
	collider->m_pMainScript = this;
	// �����蔻�茳�t���OON
	collider->SetCollisionFlag(true);
}


/**
* @brief	�j����
*/
void CPlayerTarget::OnDestroy()
{
	CScriptBase::OnDestroy();
}



/**
* @brief	�X�V����
*/
void CPlayerTarget::Update()
{
	// �A�C�e���������Ă���ꍇ
	if (m_spPlayer.lock()->GetItemFlag())
	{
		if (CInput::GetKeyTrigger(VK_L))
		{
			// �I�u�W�F�N�g�������
			const auto& playerTrans = m_spTransform.lock()->GetParent().lock()->m_spTransform.lock();
			playerTrans->ReleaseRelationship(m_spPlayer.lock()->GetItem());
			// �A�C�e���̃����[�X
			m_spPlayer.lock()->ReleaseItem();
		}
	}

	// �^�[�Q�b�g�����Z�b�g
	m_bIsTarget = false;
}


/**
* @brief	�����������̏���
* @param	collider		����̃R���C�_�[
*/
void CPlayerTarget::OnCollision(std::weak_ptr<CCollider> collider)
{
	// �v���C���[���A�N�V�������̏ꍇ�I��
	if (m_spPlayer.lock()->IsAction())	return;

	// �{�^���������ꂽ�Ƃ��̂ݏ������s��
	if (CInput::GetKeyTrigger(VK_J))
	{
		// ����I�u�W�F�N�g�ɐe�������ꍇ�͔�������Ȃ�
		if (collider.lock()->m_spTransform.lock()->GetParent().lock())	return;

		// �A�C�e���������Ă����ꍇ
		if (m_spPlayer.lock()->GetItemFlag())
		{
			// ���s���鏈�������邩���f
			if (collider.lock()->m_pMainScript->ExistsProcess(m_spGameObject.lock()->GetComponent<CCollider>(), m_spPlayer.lock()->GetItem()))
			{
				// �A�N�V����ON
				m_spPlayer.lock()->SetActionFlag(true);
				// �v���C���[������
				const auto& rb = m_spPlayer.lock()->m_spGameObject.lock()->GetComponent<CRigidbody>().lock();
				rb->SubForce(SUBTRACT);
			}
		}
		// �A�C�e���������Ă��Ȃ������ꍇ
		else
		{
			// ���s���鏈�������邩���f
			if (collider.lock()->m_pMainScript->ExistsProcess(m_spGameObject.lock()->GetComponent<CCollider>()))
			{
				// �A�N�V����ON
				m_spPlayer.lock()->SetActionFlag(true);
				// �v���C���[�̌���
				const auto& rb = m_spPlayer.lock()->m_spGameObject.lock()->GetComponent<CRigidbody>().lock();
				rb->SubForce(SUBTRACT);
			}
		}
	}
}