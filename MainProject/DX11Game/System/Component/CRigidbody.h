#pragma once
/**
*
* @file		CRigidbody.h
* @brief	���W�b�h�{�f�B�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/31	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CComponent.h>
#include <System/Utility/Vector3.h>

class CTransform;
/** ���W�b�h�{�f�B�N���X */
class CRigidbody final : public CComponent
{
public:
	CRigidbody();
	virtual ~CRigidbody();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	//-----�ړ��֌W
	Vector3 GetForce()		{ return m_force; }
	Vector3 GetVelocity()	{ return m_velocity; }
	// �Z�b�g
	void SetForce(Vector3 force) { m_force = force; }
	void SetForceX(float forceX) { m_force->x = forceX; }
	void SetForceY(float forceY) { m_force->y = forceY; }
	void SetForceZ(float forceZ) { m_force->z = forceZ; }
	// ���Z
	void AddForce(Vector3 force) { m_force += force; }
	void AddForceX(float forceX) { m_force->x += forceX; }
	void AddForceY(float forceY) { m_force->y += forceY; }
	void AddForceZ(float forceZ) { m_force->z += forceZ; }
	// ���Z
	void SubForce(float force);

	//-----��]�֌W
	Vector3 GetTorque() { return m_torque; }
	// �Z�b�g
	void SetTorque(Vector3 torque) { m_torque = torque; }
	void SetTorqueX(float torqueX) { m_torque->x = torqueX; }
	void SetTorqueY(float torqueY) { m_torque->y = torqueY; }
	void SetTorqueZ(float torqueZ) { m_torque->z = torqueZ; }
	// ���Z
	void AddTorque(Vector3 torque) { m_torque += torque; }
	void AddTorqueX(float torqueX) { m_torque->x += torqueX; }
	void AddTorqueY(float torqueY) { m_torque->y += torqueY; }
	void AddTorqueZ(float torqueZ) { m_torque->z += torqueZ; }

	/**
	* @brief	�d�͎g�p���邩�ǂ����Z�b�g
	* @param	bUse		�g�p���邩�ǂ���(true/�g�p,flase/�s�g�p)
	*/
	void SetUseGravity(bool bUse) { m_bUseGravity = bUse; }

	/**
	* @brief	�d�͂̃Z�b�g
	* @param	force	�d��
	*/
	void SetGravityForce(float force) { m_fGravityForce = force; }

	/**
	* @brief	���ʂ̃Z�b�g
	* @param	fMass	����
	*/
	void SetMass(float fMass) { m_fMass = fMass; }

	/**
	* @brief	�����g�p���邩�ǂ���
	* @return	bool	�����g�p(true/����,false/���Ȃ�)
	*/
	bool GetUsePhysics() { return m_bUsePhysics; }

	/**
	* @brief	�����g�p���邩�ǂ����̃Z�b�g
	* @param	use		�����g�p(true/����,false/���Ȃ�)
	*/
	void SetUsePhysics(bool use) { m_bUsePhysics = use; }

	/**
	* @brief	���C�̃Z�b�g
	* @param	fStaticFriction		���I���C
	* @param	fDynamicFriction	�ÓI���C
	*/
	void SetFriction(float fStaticFriction, float fDynamicFriction)
	{
		m_fStaticFriction = fStaticFriction;
		m_fDynamicFriction = fDynamicFriction;
	}

	/**
	* @brief	�����W���Z�b�g
	* @param	fCoefficient	�W��
	*/
	void SetCoefficient(float fCoefficient) { m_fCoefficient = fCoefficient; }

	void CollisionPhysics(const std::weak_ptr<CRigidbody>& other, Vector3 normal);

private:
	// �A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃g�����X�t�H�[��
	std::weak_ptr<CTransform>	m_spTransform;

	// �ړ��֌W
	Vector3 m_force;
	Vector3 m_velocity;
	Vector3 m_resistance;

	// ��]�֌W
	Vector3 m_angularVeclocity;
	Vector3 m_torque;

	// �d�͊֌W
	float   m_fGravityForce;
	bool	m_bUseGravity;

	// ����
	float	m_fMass;

	// ��������̗L��
	bool	m_bUsePhysics;

	// ���C
	float	m_fStaticFriction;
	float	m_fDynamicFriction;
	float	m_fCoefficient;

public:
	// �R���|�[�l���gID
	static const EComponentType comID;
};