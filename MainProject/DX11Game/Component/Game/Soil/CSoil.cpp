/**
*
* @file		CSoil.cpp
* @brief	�y�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/11	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Soil/CSoil.h>
#include <System/GameObject/CGameObject.h>
#include <System/Utility/Search.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CPlantAction.h>
#include <Component/Game/Player/Action/CGiveWaterAction.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/Action/CPutAction.h>
#include <Component/Game/Water/CBucket.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <Component/Game/Player/CPlayerTarget.h>

/** �}�N����` */
namespace
{
	// ���f���T�C�Y
	const Vector3 MODEL_SCALE = Vector3(18.0f, 5.0f, 18.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CSoil::CSoil()
	: m_bIsAction(false)
	, m_bOldIsAction(false)
{

}


/**
* @brief	�f�X�g���N�^
*/
CSoil::~CSoil()
{

}


/**
* @brief	������
*/
void CSoil::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Stationary");

	// ���O�ݒ�
	obj->SetName("Soil");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Soil);

	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, MODEL_SCALE);
	collider->m_pMainScript = this;
}


/**
* @brief	�j����
*/
void CSoil::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CSoil::Update()
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
* @param	collider		����̃R���C�_�[
*/
void CSoil::OnCollision(std::weak_ptr<CCollider> collider)
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
*/
bool CSoil::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// �A�N�V�������������ꍇ�I��
	if (m_bIsAction)	return false;

	// �������Ă��鑊��ɂ���ď�����ς���
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----�v���C���[�^�[�Q�b�g
	{
		const auto& childList = m_spTransform.lock()->GetChildList();

		// �q�I�u�W�F�N�g�ɃA�C�e�������݂��Ȃ��ꍇ�I��
		const auto& itemObj = SearchExistsList(childList, "Item");
		if (childList.size() == 0 || !itemObj.lock())	return false;

		// �q�I�u�W�F�N�g�ɔ엿�����݂��Ă���ꍇ�A�C�R���ړ�
		const auto& fertilizerObj = SearchExistsList(childList, "SupportItem").lock();
		if (fertilizerObj)
		{
			itemObj.lock()->m_spTransform.lock()->ReplaceChild(fertilizerObj, false);
		}

		// �v���C���[�擾
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();

		// �e�q�֌W�̉���
		m_spTransform.lock()->ReleaseRelationship(itemObj);

		// �e�q�֌W�����
		CTransform::SetParentChildRelation(playerObj, itemObj, EDirection::Front, 15.0f);

		// �A�C�e���Z�b�g
		const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>().lock();
		playerCom->SetItem(itemObj);

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
bool CSoil::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	// �A�N�V�������������ꍇ�I��
	if (m_bIsAction)	return false;

	const auto& childList = m_spTransform.lock()->GetChildList();

	// �����Ă���A�C�e���ɂ���ď�����ς���
	switch (itemObj.lock()->GetObjectID())
	{
	case EObjectType::Seed:		//-----��
		// �q�I�u�W�F�N�g���Ȃ������ꍇ
		if (childList.size() == 0)
		{
			// �v���C���[�ɃA�N�V�����ǉ�
			const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
			const auto& playerAction = playerObj.lock()->AddComponent<CPlantAction>();
			playerAction.lock()->SetTarget(m_spGameObject, itemObj);
			return true;
		}
		// �엿�I�u�W�F�N�g�̂ݑ��݂��Ă���ꍇ
		else if (childList.size() == 1 && SearchExistsList(childList, "SupportItem").lock())
		{
			// �v���C���[�ɃA�N�V�����ǉ�
			const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
			const auto& playerAction = playerObj.lock()->AddComponent<CPlantAction>();
			playerAction.lock()->SetTarget(m_spGameObject, itemObj);
			return true;
		}
		return false;

	case EObjectType::Bucket:	//-----�o�P�c
		// �q�I�u�W�F�N�g������Ύ��s
		if (childList.size() > 0)
		{
			// �w��̃I�u�W�F�N�g�����݂��Ă����ꍇ
			const auto& plantObj = SearchExistsList(childList, "Item");
			if (plantObj.lock())
			{
				// �I�u�W�F�N�g�������ς݂������ꍇ�I��
				if (plantObj.lock()->GetObjectID() == EObjectType::Flower)		return false;

				// ���������Ă����ꍇ
				if (itemObj.lock()->GetComponent<CBucket>().lock()->GetWaterFlag())
				{
					// �v���C���[�ɃA�N�V�����ǉ�
					const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
					const auto& playerAction = playerObj.lock()->AddComponent<CGiveWaterAction>();
					playerAction.lock()->SetTarget(m_spGameObject, itemObj);
					return true;
				}
			}
		}
		return false;

	case EObjectType::Potted:	//-----���A��
		// ���ɔ��A���ɃI�u�W�F�N�g�������Ă����ꍇ�I��(1�ɂȂ��Ă���̂͐�������UI�A�C�R�����q�Ƃ��Ă����Ă��邽��)
		if (itemObj.lock()->m_spTransform.lock()->GetChildList().size() > 1)	return false;

		// �q�I�u�W�F�N�g���Ȃ������ꍇ�I��
		if (childList.size() == 0)	return false;
		// �q�I�u�W�F�N�g�����݂��Ă���ꍇ
		else
		{
			// �w��̃I�u�W�F�N�g�����݂��Ă����ꍇ
			const auto& plantObj = SearchExistsList(childList, "Item").lock();
			if (plantObj)
			{
				// ��I�u�W�F�N�g�������ꍇ�I��
				if (plantObj->GetObjectID() == EObjectType::Seed)	return false;

				// �엿���������ꍇ
				const auto& fertilizerObj = SearchExistsList(childList, "SupportItem").lock();
				if (fertilizerObj)
				{
					plantObj->m_spTransform.lock()->ReplaceChild(fertilizerObj, false);
					const auto& plantChild = plantObj->m_spTransform.lock()->GetChildList();
					for (auto it = plantChild.begin(); it != plantChild.end(); ++it)
					{
						it->lock()->GetComponent<CIconUI>().lock()->MoveON(-5.0f);
					}
				}

				// �q�I�u�W�F�N�g�����ւ���
				plantObj->m_spTransform.lock()->ReplaceChildAll(itemObj);

				// �e�q�֌W�̉���
				m_spTransform.lock()->ReleaseRelationship(plantObj);

				// �e�q�֌W�����
				CTransform::SetParentChildRelation(itemObj, plantObj, EDirection::Up, 0.0f);

				// �v���C���[�ɃA�N�V�����ǉ�
				const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
				playerObj.lock()->AddComponent<CTakeAction>();
				return true;
			}
		}
		 return false;
	case EObjectType::FertilizerC:	//-----�엿
	case EObjectType::FertilizerM:
	case EObjectType::FertilizerY:
		// �q�I�u�W�F�N�g���������ꍇ
		if (childList.size() > 0)
		{
			// ���ɔ엿�����݂��Ă����ꍇ�I��
			if (SearchExistsList(childList, "SupportItem").lock())		return false;

			// �q�I�u�W�F�N�g�������ς݂������ꍇ�I��
			const auto& plantObj = SearchExistsList(childList, "Item");
			if (!plantObj.lock() || plantObj.lock()->GetObjectID() == EObjectType::Flower)	return false;

			// �v���C���[�ɃA�N�V�����ǉ�
			const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
			const auto& playerAction = playerObj.lock()->AddComponent<CPutAction>();
			playerAction.lock()->SetTarget(playerObj, itemObj);

			// �A�C�e���̃����[�X
			playerObj.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();

			// �e�q�֌W������
			playerObj.lock()->m_spTransform.lock()->ReleaseRelationship(itemObj);

			if (plantObj.lock()->GetObjectID() == EObjectType::Sprout)
			{
				// �q�I�u�W�F�N�g�����ւ���
				itemObj.lock()->m_spTransform.lock()->ReplaceChildAll(plantObj);
			}

			// �e�q�֌W�����
			CTransform::SetParentChildRelation(m_spGameObject, itemObj, EDirection::Up, 0.0f);
		}
		// �q�I�u�W�F�N�g���Ȃ������ꍇ
		else
		{
			// �v���C���[�ɃA�N�V�����ǉ�
			const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
			const auto& playerAction = playerObj.lock()->AddComponent<CPutAction>();
			playerAction.lock()->SetTarget(playerObj, itemObj);

			// �A�C�e���̃����[�X
			playerObj.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();

			// �e�q�֌W������
			playerObj.lock()->m_spTransform.lock()->ReleaseRelationship(itemObj);

			// �e�q�֌W�����
			CTransform::SetParentChildRelation(m_spGameObject, itemObj, EDirection::Up, 0.0f);
		}
		return true;
	default:break;
	}

	return false;
}
