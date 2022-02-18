/**
*
* @file		CRigidbody.cpp
* @brief	リジッドボディクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/31	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CRigidbody.h>
#include <System/GameObject/CGameObject.h>
#include <System/Utility/Math.h>
#include <System/Systems/CRigidbodySystem.h>
#include <Scene/CSceneManager.h>

#include <System/CDebugProc.h>

/** マクロ定義 */
namespace
{
	const float GRAVITYFORCE = 9.8f / 60.0f;
}

/** 静的メンバ */
const EComponentType CRigidbody::comID = EComponentType::Rigidbody;

/**
* @brief	コンストラクタ
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
* @brief	デストラクタ
*/
CRigidbody::~CRigidbody()
{

}


/**
* @brief	生成時
*/
void CRigidbody::OnCreate()
{
	// トランスフォーム取得
	m_spTransform = m_spGameObject.lock()->GetComponent<CTransform>();
	// システムリストに格納
	CRigidbodySystem* pSystem = SCENE_MANAGER->GetSystem<CRigidbodySystem>(EComponentType::Rigidbody);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	破棄時
*/
void CRigidbody::OnDestroy()
{
	// システムから除外
	CRigidbodySystem* pSystem = SCENE_MANAGER->GetSystem<CRigidbodySystem>(EComponentType::Rigidbody);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	更新処理
*/
void CRigidbody::Update()
{
	const auto& transform = m_spTransform.lock();
	Vector3 pos = transform->GetPosition();
	//Vector3 rot = transform->GetRotation();
	//Vector3 scale = transform->GetScale();

	// 重力加算
	//if (m_bUseGravity)	m_force->y += m_fGravityForce * m_fMass;
	m_velocity = Vector3::zero();

	m_velocity += m_force;
	if (m_velocity->x > 1.0f)	m_velocity->x = 1.0f;
	if (m_velocity->x < -1.0f)	m_velocity->x = -1.0f;
	//if (m_velocity->y > 1.0f)	m_velocity->y = 1.0f;
	//if (m_velocity->y < -1.0f)	m_velocity->y = -1.0f;
	if (m_velocity->z > 1.0f)	m_velocity->z = 1.0f;
	if (m_velocity->z < -1.0f)	m_velocity->z = -1.0f;

	// 座標更新
	pos += m_velocity;
	m_spTransform.lock()->SetPosition(pos);

	// 速度の減算
	m_force->x *= (1.0f - m_resistance->x);
	if (fabsf(m_force->x) < 0.01f)	m_force->x = 0.0f;
	m_force->y *= (1.0f - m_resistance->y);
	if (fabsf(m_force->y) < 0.01f)	m_force->y = 0.0f;
	m_force->z *= (1.0f - m_resistance->z);
	if (fabsf(m_force->z) < 0.01f)	m_force->z = 0.0f;
}


/**
* @brief	物理計算
* @param	other	相手のリジッドボディ
* @param	normal	進行ベクトル
*/
void CRigidbody::CollisionPhysics(const std::weak_ptr<CRigidbody>& other, Vector3 normal)
{
	// リジッドボディ取得
	//const auto& rb1 = this;
	//const auto& rb2 = other.lock();

	// ベクトルの大きさ
	//float magnitude = Length(rb1->m_velocity);

	// 壁ずりベクトル
	//Vector3 scratch = WallScratchVector(rb1->m_velocity, normal);

	//m_velocity = scratch;
	//m_force = Vector3::zero();

	// 座標を反映
	//Vector3 pos = m_spTransform.lock()->GetPosition();
	// 座標を元に戻す
	//pos -= m_velocity;
	// 新しく座標を反映
	//pos += scratch;
	//m_spTransform.lock()->SetPosition(pos);
	//rb1->m_force = scratch;
	//rb1->m_velocity = scratch;
	
	//// 垂直ベクトル
	//Vector3 vertical = WallVerticalVector(rb1->m_velocity, normal);
	//Vector3 vertical2 = WallVerticalVector(rb2->m_velocity, normal);

	//float fCoefficient = rb1->m_fCoefficient*rb2->m_fCoefficient;

	//// 垂直速度
	//Vector3 verticalVector = (vertical2 - vertical) * (1 + fCoefficient) / (rb1->m_fMass / rb2->m_fMass + 1);
	//Vector3 verticalVector2 = (vertical - vertical2) * (1 + fCoefficient) / (rb2->m_fMass / rb1->m_fMass + 1);

	//// 水平方向
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
* @brief	力減算
* @param	force	減算する大きさ
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