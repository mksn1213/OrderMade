/**
*
* @file		CRigidbody.cpp
* @brief	���W�b�h�{�f�B�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/31	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CRigidbody.h>
#include <System/GameObject/CGameObject.h>
#include <System/Utility/Math.h>
#include <System/Systems/CRigidbodySystem.h>
#include <Scene/CSceneManager.h>

#include <System/CDebugProc.h>

/** �}�N����` */
namespace
{
	const float GRAVITYFORCE = 9.8f / 60.0f;
}

/** �ÓI�����o */
const EComponentType CRigidbody::comID = EComponentType::Rigidbody;

/**
* @brief	�R���X�g���N�^
*/
CRigidbody::CRigidbody()
	: m_force(Vector3::zero())
	, m_velocity(Vector3::zero())
	, m_resistance(0.2f, 0.0f, 0.2f)
	, m_angularVeclocity(Vector3::zero())
	, m_torque(Vector3::zero())
	, m_fGravityForce(-GRAVITYFORCE)
	, m_bUseGravity(false)
	, m_fMass(1.0f)
	, m_bUsePhysics(false)
	, m_fStaticFriction(0.0f)
	, m_fDynamicFriction(0.0f)
	, m_fCoefficient(1.0f)
{
	SetID(Rigidbody);
}


/**
* @brief	�f�X�g���N�^
*/
CRigidbody::~CRigidbody()
{

}


/**
* @brief	������
*/
void CRigidbody::OnCreate()
{
	// �g�����X�t�H�[���擾
	m_spTransform = m_spGameObject.lock()->GetComponent<CTransform>();
	// �V�X�e�����X�g�Ɋi�[
	CRigidbodySystem* pSystem = SCENE_MANAGER->GetSystem<CRigidbodySystem>(EComponentType::Rigidbody);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	�j����
*/
void CRigidbody::OnDestroy()
{
	// �V�X�e�����珜�O
	CRigidbodySystem* pSystem = SCENE_MANAGER->GetSystem<CRigidbodySystem>(EComponentType::Rigidbody);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	�X�V����
*/
void CRigidbody::Update()
{
	const auto& transform = m_spTransform.lock();
	Vector3 pos = transform->GetPosition();
	//Vector3 rot = transform->GetRotation();
	//Vector3 scale = transform->GetScale();

	// �d�͉��Z
	//if (m_bUseGravity)	m_force->y += m_fGravityForce * m_fMass;
	m_velocity = Vector3::zero();

	m_velocity += m_force;
	if (m_velocity->x > 1.0f)	m_velocity->x = 1.0f;
	if (m_velocity->x < -1.0f)	m_velocity->x = -1.0f;
	//if (m_velocity->y > 1.0f)	m_velocity->y = 1.0f;
	//if (m_velocity->y < -1.0f)	m_velocity->y = -1.0f;
	if (m_velocity->z > 1.0f)	m_velocity->z = 1.0f;
	if (m_velocity->z < -1.0f)	m_velocity->z = -1.0f;

	// ���W�X�V
	pos += m_velocity;
	m_spTransform.lock()->SetPosition(pos);

	// ���x�̌��Z
	m_force->x *= (1.0f - m_resistance->x);
	if (fabsf(m_force->x) < 0.01f)	m_force->x = 0.0f;
	m_force->y *= (1.0f - m_resistance->y);
	if (fabsf(m_force->y) < 0.01f)	m_force->y = 0.0f;
	m_force->z *= (1.0f - m_resistance->z);
	if (fabsf(m_force->z) < 0.01f)	m_force->z = 0.0f;
}


/**
* @brief	�����v�Z
* @param	other	����̃��W�b�h�{�f�B
* @param	normal	�i�s�x�N�g��
*/
void CRigidbody::CollisionPhysics(const std::weak_ptr<CRigidbody>& other, Vector3 normal)
{
	// ���W�b�h�{�f�B�擾
	//const auto& rb1 = this;
	//const auto& rb2 = other.lock();

	// �x�N�g���̑傫��
	//float magnitude = Length(rb1->m_velocity);

	// �ǂ���x�N�g��
	//Vector3 scratch = WallScratchVector(rb1->m_velocity, normal);

	//m_velocity = scratch;
	//m_force = Vector3::zero();

	// ���W�𔽉f
	//Vector3 pos = m_spTransform.lock()->GetPosition();
	// ���W�����ɖ߂�
	//pos -= m_velocity;
	// �V�������W�𔽉f
	//pos += scratch;
	//m_spTransform.lock()->SetPosition(pos);
	//rb1->m_force = scratch;
	//rb1->m_velocity = scratch;
	
	//// �����x�N�g��
	//Vector3 vertical = WallVerticalVector(rb1->m_velocity, normal);
	//Vector3 vertical2 = WallVerticalVector(rb2->m_velocity, normal);

	//float fCoefficient = rb1->m_fCoefficient*rb2->m_fCoefficient;

	//// �������x
	//Vector3 verticalVector = (vertical2 - vertical) * (1 + fCoefficient) / (rb1->m_fMass / rb2->m_fMass + 1);
	//Vector3 verticalVector2 = (vertical - vertical2) * (1 + fCoefficient) / (rb2->m_fMass / rb1->m_fMass + 1);

	//// ��������
	//Vector3 horizontalVector;
	//Vector3 horizontalVector2;
	//Vector3 N = vertical;
	//float fFrictionS = rb1->m_fStaticFriction*rb2->m_fStaticFriction;
	//float fFrictionD = rb1->m_fDynamicFriction*rb2->m_fDynamicFriction;
	//float fFrictionForce = fFrictionD * Length(N);
	//if (fFrictionForce > 1.0f)fFrictionForce = 1.0f;

	//if (Length(scratch) > fFrictionS * Length(N))
	//{
	//	horizontalVector = scratch - scratch * fFrictionForce;
	//}
	//if (fFrictionForce > fFrictionS * Length(vertical2))
	//{
	//	horizontalVector2 = scratch * fFrictionForce;
	//}

	//if (rb1->GetUsePhysics())
	//{
	//	Vector3 force = horizontalVector + verticalVector;

	//	rb1->m_force = force;
	//	rb1->m_velocity = force;
	//}

	//if (rb2->GetUsePhysics())
	//{
	//	Vector3 force = horizontalVector2 + verticalVector2;

	//	rb2->m_force = force;
	//	rb2->m_velocity = force;
	//}
}


/**
* @brief	�͌��Z
* @param	force	���Z����傫��
*/
void CRigidbody::SubForce(float force)
{
	if (m_force->x > 0)
	{
		m_force->x -= force;
		if (m_force->x < 0)	m_force->x = 0;
	}
	else
	{
		m_force->x += force;
		if (m_force->x > 0)	m_force->x = 0;
	}
	//if (m_force->y > 0)
	//{
	//	m_force->y -= force;
	//	if (m_force->y < 0)	m_force->y = 0;
	//}
	//else
	//{
	//	m_force->y += force;
	//	if (m_force->y > 0)	m_force->y = 0;
	//}
	if (m_force->z > 0)
	{
		m_force->z -= force;
		if (m_force->z < 0)	m_force->z = 0;
	}
	else
	{
		m_force->z += force;
		if (m_force->z > 0)	m_force->z = 0;
	}
}