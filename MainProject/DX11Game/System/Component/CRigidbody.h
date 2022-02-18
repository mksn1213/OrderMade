#pragma once
/**
*
* @file		CRigidbody.h
* @brief	リジッドボディクラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/31	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CComponent.h>
#include <System/Utility/Vector3.h>

class CTransform;
/** リジッドボディクラス */
class CRigidbody final : public CComponent
{
public:
	CRigidbody();
	virtual ~CRigidbody();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	//-----移動関係
	Vector3 GetForce()		{ return m_force; }
	Vector3 GetVelocity()	{ return m_velocity; }
	// セット
	void SetForce(Vector3 force) { m_force = force; }
	void SetForceX(float forceX) { m_force->x = forceX; }
	void SetForceY(float forceY) { m_force->y = forceY; }
	void SetForceZ(float forceZ) { m_force->z = forceZ; }
	// 加算
	void AddForce(Vector3 force) { m_force += force; }
	void AddForceX(float forceX) { m_force->x += forceX; }
	void AddForceY(float forceY) { m_force->y += forceY; }
	void AddForceZ(float forceZ) { m_force->z += forceZ; }
	// 減算
	void SubForce(float force);

	//-----回転関係
	Vector3 GetTorque() { return m_torque; }
	// セット
	void SetTorque(Vector3 torque) { m_torque = torque; }
	void SetTorqueX(float torqueX) { m_torque->x = torqueX; }
	void SetTorqueY(float torqueY) { m_torque->y = torqueY; }
	void SetTorqueZ(float torqueZ) { m_torque->z = torqueZ; }
	// 加算
	void AddTorque(Vector3 torque) { m_torque += torque; }
	void AddTorqueX(float torqueX) { m_torque->x += torqueX; }
	void AddTorqueY(float torqueY) { m_torque->y += torqueY; }
	void AddTorqueZ(float torqueZ) { m_torque->z += torqueZ; }

	/**
	* @brief	重力使用するかどうかセット
	* @param	bUse		使用するかどうか(true/使用,flase/不使用)
	*/
	void SetUseGravity(bool bUse) { m_bUseGravity = bUse; }

	/**
	* @brief	重力のセット
	* @param	force	重力
	*/
	void SetGravityForce(float force) { m_fGravityForce = force; }

	/**
	* @brief	質量のセット
	* @param	fMass	質量
	*/
	void SetMass(float fMass) { m_fMass = fMass; }

	/**
	* @brief	物理使用するかどうか
	* @return	bool	物理使用(true/する,false/しない)
	*/
	bool GetUsePhysics() { return m_bUsePhysics; }

	/**
	* @brief	物理使用するかどうかのセット
	* @param	use		物理使用(true/する,false/しない)
	*/
	void SetUsePhysics(bool use) { m_bUsePhysics = use; }

	/**
	* @brief	摩擦のセット
	* @param	fStaticFriction		動的摩擦
	* @param	fDynamicFriction	静的摩擦
	*/
	void SetFriction(float fStaticFriction, float fDynamicFriction)
	{
		m_fStaticFriction = fStaticFriction;
		m_fDynamicFriction = fDynamicFriction;
	}

	/**
	* @brief	反発係数セット
	* @param	fCoefficient	係数
	*/
	void SetCoefficient(float fCoefficient) { m_fCoefficient = fCoefficient; }

	void CollisionPhysics(const std::weak_ptr<CRigidbody>& other, Vector3 normal);

private:
	// アタッチしているゲームオブジェクトのトランスフォーム
	std::weak_ptr<CTransform>	m_spTransform;

	// 移動関係
	Vector3 m_force;
	Vector3 m_velocity;
	Vector3 m_resistance;

	// 回転関係
	Vector3 m_angularVeclocity;
	Vector3 m_torque;

	// 重力関係
	float   m_fGravityForce;
	bool	m_bUseGravity;

	// 質量
	float	m_fMass;

	// 物理判定の有無
	bool	m_bUsePhysics;

	// 摩擦
	float	m_fStaticFriction;
	float	m_fDynamicFriction;
	float	m_fCoefficient;

public:
	// コンポーネントID
	static const EComponentType comID;
};