/**
*
* @file		CFertilizer.cpp
* @brief	�엿�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/16  �����J�n
* @date		2021/12/20	�R���|�[�l���g�ɕύX
* @date		2021/12/28	�A�C�R��UI�ǉ�
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Soil/CFertilizer.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <System/Renderer/CMeshRenderer.h>
#include <Component/Game/Player/CPlayerTarget.h>

/**
* @brief	�R���X�g���N�^
*/
CFertilizer::CFertilizer()
{

}


/**
* @brief	�f�X�g���N�^
*/
CFertilizer::~CFertilizer()
{

}


/**
* @brief	������
*/
void CFertilizer::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("SupportItem");

	// ���O�ݒ�
	obj->SetName("Fertilizer");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// ���f���̃Z�b�g
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::FertilizerC);

	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(8.0f, 10.0f, 10.0f));
	collider->m_pMainScript = this;

	// �A�C�R��UI�쐬
	const auto& uiObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	uiObj->AddComponent<CIconUI>().lock();
	m_spRenderer = uiObj->GetComponent<CMeshRenderer>();

	// �e�q�֌W�����
	CTransform::SetParentChildRelation(m_spGameObject, uiObj, EDirection::Up, 20.0f);
}


/**
* @brief	�j����
*/
void CFertilizer::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CFertilizer::Update()
{

}


/**
* @brief	���������ۂ̏���
* @param	collider		�����葊��̃R���C�_�[
*/
void CFertilizer::OnCollision(std::weak_ptr<CCollider> collider)
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
bool CFertilizer::ExistsProcess(std::weak_ptr<CCollider> collider)
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


/**
* @brief	�F���̃Z�b�g
* @param	color	�F�^�C�v
*/
void CFertilizer::SetColor(CColor::EColor color)
{
	// �F�̃Z�b�g
	m_eColor.colorType = color;

	// ���f���̐؂�ւ�
	const auto& renderer = m_spGameObject.lock()->GetComponent<CModelRenderer>().lock();
	switch (m_eColor.colorType)
	{
	case CColor::EColor::Cyan:
		renderer->SetModel(EModelType::FertilizerC);
		m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerC);			
		m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Cyan);
		break;
	case CColor::EColor::Magenta:
		renderer->SetModel(EModelType::FertilizerM);
		m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerM);
		m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Magenta);
		break;
	case CColor::EColor::Yellow:
		renderer->SetModel(EModelType::FertilizerY);
		m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerY);
		m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Yellow);
		break;
	default:
		break;
	}	
}