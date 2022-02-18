/**
*
* @file		CBucket.cpp
* @brief	�o�P�c�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/17  �����J�n
* @date		2021/12/17	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Water/CBucket.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Player/CPlayerTarget.h>
#include <Component/Game/Water/CWater.h>

/**
* @brief	�R���X�g���N�^
*/
CBucket::CBucket()
	: m_bHasWater(false)
{

}


/**
* @brief	�f�X�g���N�^
*/
CBucket::~CBucket()
{

}


/**
* @brief	������
*/
void CBucket::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Item");

	// ���O�ݒ�
	obj->SetName("Bucket");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Bucket);

	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(5.0f, 10.0f, 10.0f));
	collider->m_pMainScript = this;

	// �����b�V���̐���
	const auto& waterObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	waterObj->AddComponent<CWater>();
	waterObj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3::up() * 7.0f);
	waterObj->m_spTransform.lock()->SetScale(Vector3(3.0f, 1.0f, 3.0f));
	waterObj->SetActive(false);
	m_spWaterObj = waterObj;
}


/**
* @brief	�j����
*/
void CBucket::OnDestroy()
{
	CScriptBase::OnDestroy();
}



/**
* @brief	�X�V����
*/
void CBucket::Update()
{
	m_spWaterObj.lock()->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3::up() * 7.0f);
}


/**
* @brief	���������ۂ̏���
* @param	collider		�����葊��̃R���C�_�[
*/
void CBucket::OnCollision(std::weak_ptr<CCollider> collider)
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
* @details	���肪�A�C�e���������Ă��Ȃ������ꍇ�̏���
* @param	collider		����̃R���C�_�[
* @return	bool			�A�N�V�����L��
*/
bool CBucket::ExistsProcess(std::weak_ptr<CCollider> collider)
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
	default:break;
	}

	return false;
}