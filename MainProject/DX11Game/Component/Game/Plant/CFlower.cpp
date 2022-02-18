/**
*
* @file		CFlower.cpp
* @brief	�ԃN���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/09	�����J�n
* @date		2021/12/19	�R���|�[�l���g�ɕύX
* @date		2021/12/28	�A�C�R��UI�ǉ�
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Plant/CFlower.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Utility/Search.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <Component/Game/Player/CPlayerTarget.h>

/**
* @brief	�R���X�g���N�^
*/
CFlower::CFlower()
{

}


/**
* @brief	�f�X�g���N�^
*/
CFlower::~CFlower()
{

}


/**
* @brief	������
*/
void CFlower::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Item");

	// ���O�ݒ�
	obj->SetName("Flower");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Flower_W);

	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(5.0f, 10.0f, 10.0f), Vector3::up() * 10.0f);
	collider->m_pMainScript = this;

	// �A�C�R��UI�쐬
	const auto& uiObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& uiCom = uiObj->AddComponent<CIconUI>().lock();
	uiCom->SetIconTexture(ETexture::Icon_Flower);

	// �e�q�֌W�����
	CTransform::SetParentChildRelation(m_spGameObject, uiObj, EDirection::Up, 20.0f);
}


/**
* @brief	�j����
*/
void CFlower::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CFlower::Update()
{

}


/**
* @brief	���������ۂ̏���
* @param	collider		�����葊��̃R���C�_�[
*/
void CFlower::OnCollision(std::weak_ptr<CCollider> collider)
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
bool CFlower::ExistsProcess(std::weak_ptr<CCollider> collider)
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
* @brief	�s�����������邩�ǂ��� �� ����Ώ��������s����
* @details	���肪�A�C�e���������Ă���ꍇ�̏���
* @param	collider		����̃R���C�_�[
* @param	item			�A�C�e���̃Q�[���I�u�W�F�N�g
* @return	bool			�����̗L��
*/
bool CFlower::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	// �����Ă���A�C�e���ɂ���ď�����ς���
	switch (itemObj.lock()->GetObjectID())
	{
	case EObjectType::Potted:		//-----���A��
	{
		// ���ɔ��A���ɃA�C�e���I�u�W�F�N�g�������Ă����ꍇ�I��
		const auto& childList = itemObj.lock()->m_spTransform.lock()->GetChildList();
		const auto& childObj = SearchExistsList(childList, "Item").lock();
		if (childObj)	return false;
		
		// �q�I�u�W�F�N�g�����ւ���
		m_spGameObject.lock()->m_spTransform.lock()->ReplaceChildAll(itemObj);

		// �e�q�֌W�����
		CTransform::SetParentChildRelation(itemObj, m_spGameObject, EDirection::Up, 0.0f);

		// �v���C���[�ɃA�N�V�����ǉ�
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		playerObj.lock()->AddComponent<CTakeAction>();
		return true;
	}
	default:	break;
	}

	return false;
}


/**
* @brief	�F���̃Z�b�g
* @param	color		�F���
*/
void CFlower::SetColor(CColor color)
{
	// �F�̃Z�b�g
	m_eColor = color;

	// ���f���̐؂�ւ�
	const auto& renderer = m_spGameObject.lock()->GetComponent<CModelRenderer>().lock();
	switch (m_eColor.colorType)
	{
	case CColor::EColor::White:		renderer->SetModel(EModelType::Flower_W);	break;
	case CColor::EColor::Cyan:		renderer->SetModel(EModelType::Flower_C);	break;
	case CColor::EColor::Magenta:	renderer->SetModel(EModelType::Flower_M);	break;
	case CColor::EColor::Yellow:	renderer->SetModel(EModelType::Flower_Y);	break;
	case CColor::EColor::Red:		renderer->SetModel(EModelType::Flower_R);	break;
	case CColor::EColor::Green:		renderer->SetModel(EModelType::Flower_G);	break;
	case CColor::EColor::Blue:		renderer->SetModel(EModelType::Flower_B);	break;
	default:																	break;
	}
}