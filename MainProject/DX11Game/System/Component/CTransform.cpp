/**
*
* @file		CTransform.cpp
* @brief	�g�����X�t�H�[���N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CTransform.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <System/Systems/CTransformSystem.h>
#include <Scene/CSceneManager.h>

/** �ÓI�����o */
const EComponentType CTransform::comID = EComponentType::Transform;

/**
* @brief	�R���X�g���N�^
*/
CTransform::CTransform()
	: m_position(Vector3::zero())
	, m_rotation(Vector3::zero())
	, m_scale(Vector3::one())
{
	XMStoreFloat4x4(&m_mtxWorld, XMMatrixIdentity());
	XMStoreFloat4x4(&m_mtxLocalWorld, XMMatrixIdentity());
}


/**
* @brief	�f�X�g���N�^
*/
CTransform::~CTransform()
{

}


/**
* @brief	������
*/
void CTransform::OnCreate()
{
	SetID(Transform);
	// �V�X�e���Ɋi�[
	CTransformSystem* pSystem = SCENE_MANAGER->GetSystem<CTransformSystem>(EComponentType::Transform);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	�j����
*/
void CTransform::OnDestroy()
{
	// �V�X�e�����珜�O
	CTransformSystem* pSystem = SCENE_MANAGER->GetSystem<CTransformSystem>(EComponentType::Transform);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	�X�V����
*/
void CTransform::Update()
{
	// �e�Q�[���I�u�W�F�N�g�����݂���ꍇ
	if (m_spParent.lock())
	{
		// �r���{�[�h�͍��W�̂ݔ��f
		if (m_spGameObject.lock()->GetTag() == "Billboard")
		{
			const auto& parentPos = m_spParent.lock()->m_spTransform.lock()->GetPosition();
			m_mtxWorld._41 = m_mtxLocalWorld._41 + parentPos.m_vector.x;
			m_mtxWorld._42 = m_mtxLocalWorld._42 + parentPos.m_vector.y;
			m_mtxWorld._43 = m_mtxLocalWorld._43 + parentPos.m_vector.z;
		}
		else
		{
			XMMATRIX mtxRot;

			// ��]�𔽉f
			mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_rotation->x),
				XMConvertToRadians(m_rotation->y), XMConvertToRadians(m_rotation->z));
			auto mtx = XMLoadFloat4x4(&m_mtxLocalWorld);
			mtx *= mtxRot;

			// �e�̍s��������ăg�����X�t�H�[���𔽉f������
			mtx *= XMLoadFloat4x4(&m_spParent.lock()->m_spTransform.lock()->GetWorldMatrix());

			// ���[���h�ϊ��s��Z�b�g
			XMStoreFloat4x4(&m_mtxWorld, mtx);
		}

		// �q�I�u�W�F�N�g�����݂��Ă���΍X�V
		if (m_spChildList.size() > 0)
		{
			for (auto child : m_spChildList)
			{
				child.lock()->m_spTransform.lock()->Update();
			}
		}
	}
	else
	{
		// �s��̍X�V
		UpdateMatrix();

		// �q�I�u�W�F�N�g�����݂��Ă���΍X�V
		if (m_spChildList.size() > 0)
		{
			for (auto child : m_spChildList)
			{
				child.lock()->m_spTransform.lock()->Update();
			}
		}
	}

	// �����蔻��Ɏg�p���邽�ߍ��W����ɍX�V����
	m_position = Vector3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
}


/**
* @brief	�s��̍X�V
*/
void CTransform::UpdateMatrix()
{
	XMMATRIX mtxWorld, mtxTranslate, mtxRot, mtxScale;

	// ���[���h�}�g���b�N�X������
	mtxWorld = XMMatrixIdentity();

	// �X�P�[�����f
	mtxScale = XMMatrixScaling(m_scale->x, m_scale->y, m_scale->z);
	mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

	// ��]�𔽉f
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_rotation->x),
		XMConvertToRadians(m_rotation->y), XMConvertToRadians(m_rotation->z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(m_position->x, m_position->y, m_position->z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ���[���h�ϊ��s��Z�b�g
	XMStoreFloat4x4(&m_mtxWorld, mtxWorld);
}


/**
* @brief	�e�̃Z�b�g
* @param	spParent	�e�ƂȂ�Q�[���I�u�W�F�N�g
* @param	dir			�e����̕���
* @param	fLocalPos	�Z�b�g���郍�[�J�����W
*/
void CTransform::SetParent(std::weak_ptr<CGameObject> spParent, EDirection dir, float fLocalPos)
{
	m_spParent = spParent;

	// ���[�J�����W�̏�����
	XMStoreFloat4x4(&m_mtxLocalWorld, XMMatrixIdentity());

	// ���[�J�����W�̃Z�b�g
	SetLocalPosition(dir, fLocalPos);
}


/**
* @brief	�e�̃Z�b�g
* @param	spParent	�e�ƂȂ�Q�[���I�u�W�F�N�g
* @param	dir			�e����̕���
* @param	fLocalPos	�Z�b�g���郍�[�J�����W
* @param	dir2		�e����̕���2
* @param	fLocalPos2	�Z�b�g���郍�[�J�����W2
*/
void CTransform::SetParent(std::weak_ptr<CGameObject> spParent, EDirection dir, float fLocalPos, EDirection dir2, float fLocalPos2)
{
	m_spParent = spParent;

	// ���[�J�����W�̏�����
	XMStoreFloat4x4(&m_mtxLocalWorld, XMMatrixIdentity());

	// ���[�J�����W�̃Z�b�g
	SetLocalPosition(dir, fLocalPos);

	// ���[�J�����W�̃Z�b�g2
	SetLocalPosition(dir2, fLocalPos2);
}


/**
* @brief	���[�J�����W�̃Z�b�g
* @param	dir			�Z�b�g�������
* @param	fLocalPos	�Z�b�g���郍�[�J�����W
* @param	add			���Z���ǂ���(true/���Z,false/���)
*/
void CTransform::SetLocalPosition(EDirection dir, float fLocalPos, bool add)
{
	// ���[�J�����W�̃Z�b�g
	if (add)
	{
		switch (dir)
		{
		case Front:		m_mtxLocalWorld._43 += -fLocalPos;	break;
		case Back:		m_mtxLocalWorld._43 += fLocalPos;	break;
		case Up:		m_mtxLocalWorld._42 += fLocalPos;	break;
		case Down:		m_mtxLocalWorld._42 += -fLocalPos;	break;
		case Right:		m_mtxLocalWorld._41 += fLocalPos;	break;
		case Left:		m_mtxLocalWorld._41 += -fLocalPos;	break;
		default:											break;
		}
	}
	else
	{
		switch (dir)
		{
		case Front:		m_mtxLocalWorld._43 = -fLocalPos;	break;
		case Back:		m_mtxLocalWorld._43 = fLocalPos;	break;
		case Up:		m_mtxLocalWorld._42 = fLocalPos;	break;
		case Down:		m_mtxLocalWorld._42 = -fLocalPos;	break;
		case Right:		m_mtxLocalWorld._41 = fLocalPos;	break;
		case Left:		m_mtxLocalWorld._41 = -fLocalPos;	break;
		default:											break;
		}
	}
}


/**
* @brief	�q����ǉ�����
* @param	spChild
*/
void CTransform::AddChild(std::weak_ptr<CGameObject> spChild)
{
	m_spChildList.push_back(spChild);
}


/**
* @brief	�e�q�֌W������
* @detail	�e������Ăяo�����ƂŐe�q�֌W����������
* @param	childObj	�����������q���I�u�W�F�N�g
*/
void CTransform::ReleaseRelationship(std::weak_ptr<CGameObject> childObj)
{
	// �e�q�֌W�̉���
	for (auto it = m_spChildList.begin(); it != m_spChildList.end();)
	{
		if (childObj.lock() == it->lock())
		{
			// �q����e�ւ̃����N���N���A
			it->lock()->m_spTransform.lock()->m_spParent.reset();
			// �e�̎q���X�g����폜
			it = m_spChildList.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
}


/**
* @brief	�e�q�֌W������
* @param	parent		�e�ɂȂ�Q�[���I�u�W�F�N�g
* @param	child		�q�ɂȂ�Q�[���I�u�W�F�N�g
* @param	dir			�e����̕���
* @param	fLocalPos	�Z�b�g���郍�[�J�����W
*/
void CTransform::SetParentChildRelation(std::weak_ptr<CGameObject> parent, std::weak_ptr<CGameObject> child, EDirection dir, float fLocalPos)
{
	// �q�̃Z�b�g
	parent.lock()->m_spTransform.lock()->AddChild(child);
	// �e�̃Z�b�g
	child.lock()->m_spTransform.lock()->SetParent(parent, dir, fLocalPos);
	// �q�I�u�W�F�N�g�̍s��X�V
	child.lock()->m_spTransform.lock()->Update();
}


/**
* @brief	�e�q�֌W������
* @param	parent		�e�ɂȂ�Q�[���I�u�W�F�N�g
* @param	child		�q�ɂȂ�Q�[���I�u�W�F�N�g
* @param	dir			�e����̕���
* @param	fLocalPos	�Z�b�g���郍�[�J�����W
* @param	dir2		�e����̕���2
* @param	fLocalPos2	�Z�b�g���郍�[�J�����W2
*/
void CTransform::SetParentChildRelation(std::weak_ptr<CGameObject> parent, std::weak_ptr<CGameObject> child, EDirection dir, float fLocalPos, EDirection dir2, float fLocalPos2)
{
	// �q�̃Z�b�g
	parent.lock()->m_spTransform.lock()->AddChild(child);
	// �e�̃Z�b�g
	child.lock()->m_spTransform.lock()->SetParent(parent, dir, fLocalPos, dir2, fLocalPos2);
	// �q�I�u�W�F�N�g�̍s��X�V
	child.lock()->m_spTransform.lock()->Update();
}


/**
* @brief	�S�Ă̎q�I�u�W�F�N�g�����ւ���
* @param	parent		�t���ւ��鑊��I�u�W�F�N�g
*/
void CTransform::ReplaceChildAll(std::weak_ptr<CGameObject> parent)
{
	while (m_spChildList.size() > 0)
	{
		// �e�q�֌W�̉���
		auto childObj = m_spChildList.begin()->lock();
		ReleaseRelationship(childObj);

		// �V�����e�I�u�W�F�N�g�Ɏ��ւ���
		// �r���{�[�h(�A�C�R��)�������ꍇ�A�ʒu�𒲐�����
		if (childObj->GetTag() == "Billboard")
		{
			const auto& parentChildList = parent.lock()->m_spTransform.lock()->GetChildList();
			int size = parentChildList.size();

			if (size == 1)
			{
				const auto& iconCom = parentChildList.begin()->lock()->GetComponent<CIconUI>().lock();
				if (iconCom)	iconCom->MoveON(-5.0f);
				CTransform::SetParentChildRelation(parent, childObj, EDirection::Up, 20.0f, EDirection::Right, 5.0f);
			}
			else if (size = 2)
			{
				const auto& iconCom = parentChildList.begin()->lock()->GetComponent<CIconUI>().lock();
				if (iconCom)	iconCom->MoveON(-5.0f);
				const auto& iconCom2 = parentChildList.back().lock()->GetComponent<CIconUI>().lock();
				if (iconCom2)	iconCom2->MoveON(-5.0f);

				CTransform::SetParentChildRelation(parent, childObj, EDirection::Up, 20.0f, EDirection::Right, 10.0f);
			}			
		}
		else
		{
			CTransform::SetParentChildRelation(parent, childObj, EDirection::Up, 10.0f);
		}
	}
}


/**
* @brief	�O���͌�̎q�I�u�W�F�N�g�����ւ���
* @param	parent		�t���ւ��鑊��I�u�W�F�N�g
* @param	forward		�擪�̎q�I�u�W�F�N�g���ǂ���(false/�Ō��,true/�擪)
*/
void CTransform::ReplaceChild(std::weak_ptr<CGameObject> parent, bool forward)
{
	// �q�I�u�W�F�N�g�����݂��Ȃ��ꍇ�I��
	if (m_spChildList.size() == 0)	return;

	// �e�q�֌W�̉���
	std::weak_ptr<CGameObject> childObj;
	if (forward)	childObj = m_spChildList.begin()->lock();
	else			childObj = m_spChildList.back();
	ReleaseRelationship(childObj);
	// �V�����e�I�u�W�F�N�g�Ɏ��ւ���
	CTransform::SetParentChildRelation(parent, childObj, EDirection::Up, 20.0f, EDirection::Right, 5.0f);

	// �A�C�R���̈ړ�
	for (auto it = m_spChildList.begin(); it != m_spChildList.end(); ++it)
	{
		const auto& iconCom = it->lock()->GetComponent<CIconUI>().lock();
		if (iconCom)	iconCom->MoveON(5.0f);
	}
	const auto& iconCom2 =  childObj.lock()->GetComponent<CIconUI>().lock();
	if (iconCom2)	iconCom2->MoveON(-5.0f);
}
