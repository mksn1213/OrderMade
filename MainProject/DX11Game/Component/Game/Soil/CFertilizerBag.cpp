/**
*
* @file		CFertilizerBag.cpp
* @brief	�엿�܃N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/16	�����J�n
* @date		2021/12/11	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Soil/CFertilizerBag.h>
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
CFertilizerBag::CFertilizerBag()
{

}


/**
* @brief	�f�X�g���N�^
*/
CFertilizerBag::~CFertilizerBag()
{

}


/**
* @brief	������
*/
void CFertilizerBag::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Stationary");

	// ���O�ݒ�
	obj->SetName("FertilizerBag");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// ���f���̃Z�b�g
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::FertilizerBagC);

	// �R���|�[�l���g�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(20.0f, 10.0f, 30.0f),Vector3::up() * 5.0f);
	collider->m_pMainScript = this;
}


/**
* @brief	�j����
*/
void CFertilizerBag::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CFertilizerBag::Update()
{

}


/**
* @brief	�����蔻��
* @param	collider		����̃R���C�_�[
*/
void CFertilizerBag::OnCollision(std::weak_ptr<CCollider> collider)
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
* @details	���肪�A�C�e���������Ă��Ȃ������ꍇ�̏���
* @param	collider		����̃R���C�_�[
* @return	bool			�A�N�V�����̗L��
* @
*/
bool CFertilizerBag::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// ����I�u�W�F�N�g�ɂ���ď������ς��
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----�v���C���[�^�[�Q�b�g
	{
		// �엿�I�u�W�F�N�g�𐶐�
		const auto& fertilizerObj = Create();

		// �e�q�֌W�����
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		CTransform::SetParentChildRelation(playerObj, fertilizerObj, EDirection::Front, 15.0f);

		// �A�C�e���Z�b�g
		const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>().lock();
		playerCom->SetItem(fertilizerObj);

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
void CFertilizerBag::SetColor(CColor::EColor color)
{
	// �F�̃Z�b�g
	m_eColor.colorType = color;

	// ���f���̐؂�ւ�
	const auto& renderer = m_spGameObject.lock()->GetComponent<CModelRenderer>().lock();
	switch (m_eColor.colorType)
	{
	case CColor::EColor::Cyan:		renderer->SetModel(EModelType::FertilizerBagC);
									m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerBagC);			break;
	case CColor::EColor::Magenta:	renderer->SetModel(EModelType::FertilizerBagM);
									m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerBagM);			break;
	case CColor::EColor::Yellow:	renderer->SetModel(EModelType::FertilizerBagY);
									m_spGameObject.lock()->SetObjectID(EObjectType::FertilizerBagY);			break;
	default:																									break;
	}
}


/**
* @brief	���g�̐F�̃I�u�W�F�N�g�𐶐�
* @return	std::weak_ptr<CGameObject> ���������I�u�W�F�N�g
*/
std::weak_ptr<CGameObject> CFertilizerBag::Create()
{
	std::weak_ptr<CGameObject> obj;
	switch (m_eColor.colorType)
	{
	case CColor::EColor::Cyan:		obj = CStageFactory::CreateGameObject(EObjectType::FertilizerC);	break;
	case CColor::EColor::Magenta:	obj = CStageFactory::CreateGameObject(EObjectType::FertilizerM);	break;
	case CColor::EColor::Yellow:	obj = CStageFactory::CreateGameObject(EObjectType::FertilizerY);	break;
	default:break;
	}
	return obj;
}