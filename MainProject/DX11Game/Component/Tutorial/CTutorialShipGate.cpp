/**
*
* @file		CTutorialShipGate.cpp
* @brief	�`���[�g���A���p�o�׃Q�[�g�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Tutorial/CTutorialShipGate.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Component/Tutorial/CTutorialManager.h>
#include <System/Effect/CEffectManager.h>
#include <System/Utility/Search.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CPutAction.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Order/CShipTruck.h>
#include <Component/Game/Player/CPlayerTarget.h>

/**
* @brief	�R���X�g���N�^
*/
CTutorialShipGate::CTutorialShipGate()
{

}


/**
* @brief	�f�X�g���N�^
*/
CTutorialShipGate::~CTutorialShipGate()
{

}


/**
* @brief	������
*/
void CTutorialShipGate::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Stationary");
	// ���O�ݒ�
	obj->SetName("ShipGate");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ShipGate);
	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(40.0f, 40.0f, 10.0f), Vector3(0.0f, 20.0f, 0.0f));
	collider->m_pMainScript = this;
	// �o�׃g���b�N�̐���
	const auto& truckObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	truckObj->AddComponent<CShipTruck>();
	truckObj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3(0.0f, 0.0f, 30.0f));
	truckObj->m_spTransform.lock()->SetRotation(Vector3(0.0f, 270.0f, 0.0f));
	m_spTruckList.push_back(truckObj);
}


/**
* @brief	�j����
*/
void CTutorialShipGate::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTutorialShipGate::Update()
{

}


/**
* @brief	�����蔻��
* @param	collider		����̃R���C�_�[
*/
void CTutorialShipGate::OnCollision(std::weak_ptr<CCollider> collider)
{
	// �^�[�Q�b�g�ɑI������Ă���ꍇ�`���ς���
	if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)
	{
		// �^�[�Q�b�g�����ɑ��݂��Ă����ꍇ�I��
		const auto& target = collider.lock()->m_spGameObject.lock()->GetComponent<CPlayerTarget>().lock();
		if (target->IsTarget())	return;
		// �^�[�Q�b�g�̌���
		target->TargetON();
		const auto& obj = m_spGameObject.lock();
		// �V�F�[�_�[�ύX
		obj->SetShader(EVertexShaderKind::AssimpVS, EPixelShaderKind::AssimpTargetPS);
	}
}


/**
* @brief	�s�����������邩�ǂ��� �� ����Ώ��������s����
* @details	���肪�A�C�e���������Ă���ꍇ�̏���
* @param	collider		����̃R���C�_�[
* @param	item			�A�C�e���̃Q�[���I�u�W�F�N�g
* @return	bool			�����̗L��
*/
bool CTutorialShipGate::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	if (TUTORIAL_MANAGER->GetStageNo() != 3)	return false;

	// �����Ă���A�C�e���ɂ���ď�����ς���
	switch (itemObj.lock()->GetObjectID())
	{
	case EObjectType::Sprout:	//-----��
	case EObjectType::Flower:	//-----��
	{
		// �G�t�F�N�g�Đ�
		EFFECT_MANAGER->Play(EEffectType::Ship, m_spTransform.lock()->GetPosition() + Vector3::up() * 20.0f);
		// �v���C���[�ɃA�N�V�����ǉ�
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		playerObj.lock()->AddComponent<CPutAction>();
		// �A�C�e���̃����[�X
		playerObj.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();
		// �e�q�֌W�̉���
		playerObj.lock()->m_spTransform.lock()->ReleaseRelationship(itemObj);
		// �e�q�֌W�����
		CTransform::SetParentChildRelation(m_spTruckList.back().lock(), itemObj, EDirection::Up, 10.0f, EDirection::Back, 10.0f);
		// �A�C�R��UI�폜
		auto childList = itemObj.lock()->m_spTransform.lock()->GetChildList();
		for (auto it = childList.begin(); it != childList.end();)
		{
			auto obj = it->lock();
			it = childList.erase(it);
			obj->Destroy();
		}

		// �o�׃t���O�𗧂Ă�
		const auto& com = m_spTruckList.back().lock()->GetComponent<CShipTruck>().lock();
		com->SetShipFlag();
		// �V�����o�׃g���b�N�𐶐�
		const auto& truckObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
		const auto& truckCom = truckObj->AddComponent<CShipTruck>().lock();
		truckObj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3(-300.0f, 0.0f, 30.0f));
		truckObj->m_spTransform.lock()->SetRotation(Vector3(0.0f, -90.0f, 0.0f));
		m_spTruckList.push_back(truckObj);
		truckCom->SetMoveFlag(m_spTransform.lock()->GetPosition());
		// �`���[�g���A���I��
		TUTORIAL_MANAGER->Fin();
		return true;
	}
	case EObjectType::Potted:	//-----���A��
	{
		// ���A���ɉ��������Ă��Ȃ���ΏI��
		auto childList = itemObj.lock()->m_spTransform.lock()->GetChildList();
		const auto& plantObj = SearchExistsList(childList, "Item").lock();
		if (!plantObj)	return false;

		// �G�t�F�N�g�Đ�
		EFFECT_MANAGER->Play(EEffectType::Ship, m_spTransform.lock()->GetPosition() + Vector3::up() * 20.0f);
		// �v���C���[�ɃA�N�V�����ǉ�
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		playerObj.lock()->AddComponent<CPutAction>();
		// �A�C�e���̃����[�X
		playerObj.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();
		// �e�q�֌W�̉���
		playerObj.lock()->m_spTransform.lock()->ReleaseRelationship(itemObj);
		// �e�q�֌W�����
		CTransform::SetParentChildRelation(m_spTruckList.back().lock(), itemObj, EDirection::Up, 10.0f, EDirection::Back, 10.0f);
		// �A�C�R��UI�폜
		for (auto it = childList.begin(); it != childList.end();)
		{
			if (it->lock()->GetTag() == "Billboard")
			{
				auto obj = it->lock();
				it = childList.erase(it);
				obj->Destroy();
			}
			else
			{
				++it;
			}
		}
		// �o�׃t���O�𗧂Ă�
		const auto& com = m_spTruckList.back().lock()->GetComponent<CShipTruck>().lock();
		com->SetShipFlag();
		// �V�����o�׃g���b�N�𐶐�
		const auto& truckObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
		const auto& truckCom = truckObj->AddComponent<CShipTruck>().lock();
		truckObj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3(-300.0f, 0.0f, 30.0f));
		truckObj->m_spTransform.lock()->SetRotation(Vector3(0.0f, -90.0f, 0.0f));
		m_spTruckList.push_back(truckObj);
		truckCom->SetMoveFlag(m_spTransform.lock()->GetPosition());
		// �`���[�g���A���I��
		TUTORIAL_MANAGER->Fin();
		return true;
	}
	default:break;
	}

	return false;
}
