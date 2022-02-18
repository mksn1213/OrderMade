/**
*
* @file		CSeed.cpp
* @brief	��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/17  �����J�n
* @date		2021/12/14	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Plant/CSeed.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/CPlayer.h>
#include <System/Component/CRigidbody.h>
#include <Component/Game/Player/CPlayerTarget.h>

/**
* @brief	�R���X�g���N�^
*/
CSeed::CSeed()
{

}


/**
* @brief	�f�X�g���N�^
*/
CSeed::~CSeed()
{

}


/**
* @brief	������
*/
void CSeed::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Item");

	// ���O�ݒ�
	obj->SetName("Seed");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Seed);

	// ���W�b�h�{�f�B�ǉ�
	const auto& rigidbody = obj->AddComponent<CRigidbody>().lock();
	rigidbody->SetUseGravity(true);
	rigidbody->SetUsePhysics(true);

	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(5.0f, 10.0f, 10.0f));
	collider->m_pMainScript = this;
}


/**
* @brief	�j����
*/
void CSeed::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CSeed::Update()
{

}


/**
* @brief	���������ۂ̏���
* @param	collider		�����葊��̃R���C�_�[
*/
void CSeed::OnCollision(std::weak_ptr<CCollider> collider)
{
	// �^�[�Q�b�g�ɑI������Ă���ꍇ�`���ς���
	if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)
	{
		// �^�[�Q�b�g�����ɑ��݂��Ă����ꍇ�I��
		const auto& taget = collider.lock()->m_spGameObject.lock()->GetComponent<CPlayerTarget>().lock();
		if (taget->IsTarget())	return;
		const auto& obj = m_spGameObject.lock();
		// �e�����݂��Ă����ꍇ�I��
		if (obj->m_spTransform.lock()->GetParent().lock())	return;
		// �^�[�Q�b�g�̌���
		taget->TargetON();
		// �V�F�[�_�[�ύX
		obj->SetShader(EVertexShaderKind::AssimpVS, EPixelShaderKind::AssimpTargetPS);
	}
}


/**
* @brief	�s�����������邩�ǂ��� �� ����Ώ��������s����
* @param	collider		����̃R���C�_�[
* @return	bool			�A�N�V�����L��
*/
bool CSeed::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// ����I�u�W�F�N�g�ɂ���ď������ς��
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----�v���C���[�^�[�Q�b�g
	{
		// �v���C���[�擾
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();

		// �e�q�֌W�����
		m_spTransform.lock()->GetParent().reset();
		CTransform::SetParentChildRelation(playerObj, m_spGameObject, EDirection::Front, 15.0f);
		
		// �A�C�e���Z�b�g
		const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>();
		playerCom.lock()->SetItem(m_spGameObject);

		// �v���C���[�ɃA�N�V�����ǉ�
		playerObj.lock()->AddComponent<CTakeAction>();
		return true;
	}
	default:	break;
	}

	return false;
}