/**
*
* @file		COvec.cpp
* @brief	�}�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/11	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Potted/COven.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CPutAction.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Potted/Action/CBakeAction.h>

#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Potted/CClay.h>
#include <Component/Game/Player/CPlayerTarget.h>

/**
* @brief	�R���X�g���N�^
*/
COven::COven()
	: m_bIsAction(false)
	, m_bOldIsAction(false)
{

}


/**
* @brief	�f�X�g���N�^
*/
COven::~COven()
{

}


/**
* @brief	������
*/
void COven::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Stationary");

	// ���O�ݒ�
	obj->SetName("Oven");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Oven);

	// �R���|�[�l���g�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(25.0f, 30.0f, 25.0f),Vector3::up() * 15.0f);
	collider->m_pMainScript = this;
}


/**
* @brief	�j����
*/
void COven::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void COven::Update()
{
	if (m_bOldIsAction && !m_bIsAction)
	{
		m_spGameObject.lock()->RemoveComponent<CAction>();
		m_bOldIsAction = m_bIsAction;
	}

	if (m_bIsAction)
	{
		m_bOldIsAction = m_bIsAction;
	}
}


/**
* @brief	�����蔻��
*/
void COven::OnCollision(std::weak_ptr<CCollider> collider)
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
bool COven::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// �A�N�V�������������ꍇ�I��
	if (m_bIsAction)	return false;

	// ����I�u�W�F�N�g�ɂ���ď������ς��
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----�v���C���[�^�[�Q�b�g
	{
		const auto& childList = m_spTransform.lock()->GetChildList();

		// �q�I�u�W�F�N�g������ꍇ
		if (childList.size() > 0)
		{
			// �v���C���[�擾
			const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();

			// �e�q�֌W�̉���
			m_spTransform.lock()->ReleaseRelationship(childList.begin()->lock());

			// �e�q�֌W�����
			CTransform::SetParentChildRelation(playerObj, childList.begin()->lock(), EDirection::Front, 15.0f);
		
			// �A�C�e���Z�b�g
			const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>().lock();
			playerCom->SetItem(childList.begin()->lock());

			// �v���C���[�ɃA�N�V�����ǉ�
			playerObj.lock()->AddComponent<CTakeAction>();
			return true;
		}
	}
	return false;
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
bool COven::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	// �A�N�V�������������ꍇ�I��
	if (m_bIsAction)	return false;

	// �����Ă���A�C�e���ɂ���ď�����ς���
	switch (itemObj.lock()->GetObjectID())
	{
	case EObjectType::Clay:		//-----�S�y
		// �S�y�������H�������ꍇ�I��
		if (!itemObj.lock()->GetComponent<CClay>().lock()->GetProcessedFlag())	return false;

		// �q�I�u�W�F�N�g���Ȃ���Ύ��s
		if (m_spTransform.lock()->GetChildList().size() == 0)
		{
			// �v���C���[�ɃA�N�V�����ǉ�
			const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
			const auto& playerAction = playerObj.lock()->AddComponent<CPutAction>();
			playerAction.lock()->SetTarget(playerObj, itemObj);

			// �A�C�e���̃����[�X
			playerObj.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();

			// �e�q�֌W���폜
			playerObj.lock()->m_spTransform.lock()->ReleaseRelationship(itemObj);

			// �e�q�֌W�����
			CTransform::SetParentChildRelation(m_spGameObject, itemObj, EDirection::Up, 12.0f,EDirection::Front,5.0f);

			// �Ă��A�N�V������ǉ�
			const auto& bakeAction = m_spGameObject.lock()->AddComponent<CBakeAction>();
			bakeAction.lock()->SetTarget(m_spGameObject, itemObj);

			// �A�N�V����ON
			SetActionFlag(true);
			return true;
		}
		return false;
	default:break;
	}

	return false;
}
