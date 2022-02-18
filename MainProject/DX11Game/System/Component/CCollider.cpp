/**
*
* @file		CCollider.cpp
* @brief	�R���C�_�[�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	�����J�n
* @date		2021/12/05	collision�N���X����collider�N���X�ɕύX
*						�R���|�[�l���g��
* @date		2021/01/02	���W�b�h�{�f�B�ɂ�铮��ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CCollider.h>
#include <System/GameObject/CGameObject.h>
#include <System/Component/CTransform.h>
#include <System/Utility/Vector3.h>
#include <Scene/CSceneManager.h>
#include <System/Utility/Math.h>
#include <System/Utility/Collision.h>
#include <System/Systems/CCollisionSystem.h>
#include <Scene/CSceneManager.h>

#include <System/CDebugProc.h>
#include <System/Renderer/CMeshRenderer.h>
#include <System/Component/CRigidbody.h>

/** �ÓI�����o */
const EComponentType CCollider::comID = EComponentType::Collider;
std::list<std::weak_ptr<CCollider>>	CCollider::m_spColliderList;

/**
* @brief	�R���X�g���N�^
*/
CCollider::CCollider()
	: m_pMainScript(nullptr)
	, m_bIsCollision(false)
	, m_colliderSize(Vector3::one())
	, m_center(Vector3::zero())
	, m_eColliderType(Box)
{
	SetID(Collider);
}


/**
* @brief	�f�X�g���N�^
*/
CCollider::~CCollider()
{
	if (m_pMainScript != nullptr)	m_pMainScript = nullptr;
}


/**
* @brief	������
*/
void CCollider::OnCreate()
{
	// �g�����X�t�H�[���擾
	m_spTransform = m_spGameObject.lock()->GetComponent<CTransform>();
	// ���W�b�h�{�f�B�擾
	m_spRigidbody = m_spGameObject.lock()->GetComponent<CRigidbody>();
	// �R���C�_�[���X�g�ɒǉ�
	m_spColliderList.push_back(m_spGameObject.lock()->GetComponent<CCollider>());
	// �V�X�e�����X�g�Ɋi�[
	CCollisionSystem* pSystem = SCENE_MANAGER->GetSystem<CCollisionSystem>(EComponentType::Collider);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	�j����
*/
void CCollider::OnDestroy()
{
	// �V�X�e�����珜�O
	CCollisionSystem* pSystem = SCENE_MANAGER->GetSystem<CCollisionSystem>(EComponentType::Collider);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	�X�V����
*/
void CCollider::Update()
{
	// TODO : �f�o�b�O�p���b�V���F�ύX
	if(m_spRenderer.lock())m_spRenderer.lock()->SetColor(XMFLOAT4(0.0f, 1.0f, 0.0f, 0.3f));

	// �����蔻����s���t���O�������Ă����
	if (m_bIsCollision)
	{
		// ���g��weak�|�C���^���R���C�_�[�^�ɕϊ�
		std::weak_ptr<CCollider> main = std::static_pointer_cast<CCollider>(m_self.lock());

		for (auto collider : m_spColliderList)
		{
			// ���g�Ɣ�����Ƃ�Ȃ�
			if (main.lock() == collider.lock())	continue;

			if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)	continue;

			// �����蔻��
			CheckCollision(main, collider);
		}
	}
}


/**
* @brief	�����蔻��
* @param	owner	���g�̃R���C�_�[
* @param	other	����̃R���C�_�[
*/
void CCollider::CheckCollision(std::weak_ptr<CCollider> owner,std::weak_ptr<CCollider> other)
{
	bool hit = false;
	// �R���C�_�[�̌`��Ŕ���𕪂���
	const auto& mainType = owner.lock()->m_eColliderType;
	const auto& otherType = other.lock()->m_eColliderType;

	// �l�p�Ǝl�p
	if (mainType == EColliderType::Box && otherType == EColliderType::Box)
	{
		if (BoxToBox(owner, other))			hit = true;
	}
	// �l�p�Ƌ�
	else if (mainType == EColliderType::Box && otherType == EColliderType::Sphere)
	{
		if (BoxToSphere(owner, other))		hit = true;
	}
	// ���Ƌ�
	else if (mainType == EColliderType::Sphere && otherType == EColliderType::Sphere)
	{
		if (SphereToSpphere(owner, other))	hit = true;
	}
	// ���Ǝl�p
	else if (mainType == EColliderType::Sphere && otherType == EColliderType::Box)
	{
		if (SphereToBox(owner, other))		hit = true;
	}

	// ���������ۂ̏���
	if (hit)
	{
		owner.lock()->m_pMainScript->OnCollision(other.lock());
		other.lock()->m_pMainScript->OnCollision(owner.lock());

		// TODO : �f�o�b�O�p���b�V���F�ύX
		//if(m_spRenderer.lock())	m_spRenderer.lock()->SetColor(XMFLOAT4(1.0f, 0.0f, 0.0f, 0.5f));
	}
}


/**
* @brief	�R���C�_�[�T�C�Y�Z�b�g
* @param	size		�R���C�_�[�T�C�Y
* @param	center		�R���C�_�[���S
*/
void CCollider::SetColliderSize(EColliderType type, Vector3 size, Vector3 center)
{
	m_eColliderType = type;
	m_colliderSize = size;
	m_center = center;

	//// �����蔻�����
	//const auto& renderer = m_spGameObject.lock()->AddComponent<CMeshRenderer>().lock();
	//if (m_eColliderType == EColliderType::Box)
	//{
	//	renderer->MakeBox(size, m_center);
	//	renderer->SetBaseTexture(ETexture::Mesh);
	//}
	//else if (m_eColliderType == EColliderType::Sphere)
	//{
	//	renderer->MakeSphere(size, m_center);
	//	renderer->SetBaseTexture(ETexture::Mesh);
	//}
	//renderer->GetMesh()->m_pMaterial->m_diffuse = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f);
	//renderer->GetMesh()->m_ePrimitiveType = PT_TRIANGLE;

	//// TODO : �f�o�b�O�p
	//m_spRenderer = renderer;
}