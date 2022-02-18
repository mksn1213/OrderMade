/**
*
* @file		CSeedBox.cpp
* @brief	�픠�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/11	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Plant/CSeedBox.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/CPlayerTarget.h>

// �I�u�W�F�N�g�����p
#include <System/Factory/CStageFactory.h>

/**
* @brief	�R���X�g���N�^
*/
CSeedBox::CSeedBox()
{

}


/**
* @brief	�f�X�g���N�^
*/
CSeedBox::~CSeedBox()
{

}


/**
* @brief	������
*/
void CSeedBox::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Stationary");
	// ���O�ݒ�
	obj->SetName("SeedBox");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::SeedBox);
	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(25.0f, 20.0f, 25.0f));
	collider->m_pMainScript = this;
}


/**
* @brief	�j����
*/
void CSeedBox::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CSeedBox::Update()
{

}


/**
* @brief	�����������̏���
* @param	collider		����̃R���C�_�[
*/
void CSeedBox::OnCollision(std::weak_ptr<CCollider> collider)
{
	// �^�[�Q�b�g�ɑI������Ă���ꍇ�`���ς���
	if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)
	{
		// �^�[�Q�b�g�����ɑ��݂��Ă����ꍇ�I��
		const auto& taget = collider.lock()->m_spGameObject.lock()->GetComponent<CPlayerTarget>().lock();
		if (taget->IsTarget())	return;
		// �^�[�Q�b�g�̌���
		taget->TargetON();
		const auto& obj = m_spGameObject.lock();
		// �V�F�[�_�[�ύX
		obj->SetShader(EVertexShaderKind::AssimpVS, EPixelShaderKind::AssimpTargetPS);
	}
}


/**
* @brief	�s�����������邩�ǂ��� �� ����Ώ��������s����
* @param	collider		����̃R���C�_�[
* @return	bool			�A�N�V�����̗L��
*/
bool CSeedBox::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// ����I�u�W�F�N�g�ɂ���ď������ς��
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----�v���C���[�^�[�Q�b�g
	{
		// ��I�u�W�F�N�g�𐶐�
		const auto& seedObj = CStageFactory::CreateGameObject(EObjectType::Seed);

		// �e�q�֌W�����
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		CTransform::SetParentChildRelation(playerObj, seedObj, EDirection::Front, 15.0f);

		// �A�C�e���Z�b�g
		const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>().lock();
		playerCom->SetItem(seedObj);
		
		// �v���C���[�ɃA�N�V�����ǉ�
		playerObj.lock()->AddComponent<CTakeAction>();
		return true;
	}
	default:	break;
	}

	return false;
}