/**
*
* @file		Collision.cpp
* @brief	�����蔻��֐��Q����
* @author	SHONOSUKE MAKITA
* @date		2021/01/01	�����J�n
* @date		2021/01/01	OBB��OBB�̔���쐬
* @date		2021/01/02	�~�Ɠ_�̔���쐬
* @date		2021/01/03	���Ǝl�p�`�̔���쐬
* @date		2021/01/04	�����o�������쐬
* @date		2021/01/05	�l�p�`�Ƌ��̔���쐬
*						���Ƌ��̔���쐬
* @date		2021/01/13	�p�x�t���l�p�`�Ɖ~�̔���쐬
*
*/

/** �C���N���[�h�� */
#include <System/Utility/Vector3.h>
#include <System/Utility/Math.h>
#include <System/Component/CCollider.h>
#include <System/Component/CRigidbody.h>
#include <System/GameObject/CGameObject.h>

/**
* @brief	�~�Ɠ_
* @param	circlePos	�~�̒��S���W
* @param	rad			�~�̔��a
* @param	point		�_�̍��W
* @return	bool		true/������,false/�������ĂȂ�
*/
bool CircleToPoint(Vector3 circlePos, float rad, Vector3 point)
{
	Vector3 dif = point - circlePos;
	float distance = sqrt(dif->x*dif->x + dif->z*dif->z);

	if (distance <= rad)	return true;
	else				return false;
}


/**
* @brief	���Ƌ�
* @param	owner	���g�̃R���C�_�[
* @param	other	����̃R���C�_�[
* @return	��������/�������ĂȂ�
*/
bool SphereToSpphere(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other)
{
	// ���S���W
	const Vector3& ownerPos = owner.lock()->m_spTransform.lock()->GetPosition() + owner.lock()->GetCenter();
	const Vector3& otherPos = other.lock()->m_spTransform.lock()->GetPosition() + owner.lock()->GetCenter();

	// ���a
	float radius1 = owner.lock()->GetColliderSize()->x;
	float radius2 = other.lock()->GetColliderSize()->x;

	// 2�_�Ԃ̋���
	Vector3 distance = ownerPos - otherPos;

	// ����
	if (LengthNotSqrt(distance) >= (radius1 + radius2) * (radius1 + radius2))	return false;

	const auto& rb1 = owner.lock()->GetRigidbody().lock();
	const auto& rb2 = other.lock()->GetRigidbody().lock();

	// ���������̗L�薳��
	//if (rb1 && rb1->GetUsePhysics())
	//{
	//	// �����v�Z
	//	rb1->CollisionPhysics(rb2, Normalize(distance));
	//}

	// �����o��
	// 2�_�Ԃ�2���a�̍�
	float len = (radius1 + radius2) - Length(distance);
	// �����o������
	Vector3 vec = Normalize(distance) * len;
	Vector3 pos = owner.lock()->m_spTransform.lock()->GetPosition();
	pos += vec;
	pos->y = 0.0f;
	owner.lock()->m_spTransform.lock()->SetPosition(pos);

	return true;
}


/**
* @brief	�l�p(OBB)�Ǝl�p(OBB)
* @param	owner	���g�̃R���C�_�[
* @param	other	����̃R���C�_�[
* @return	��������/�������ĂȂ�
*/
bool BoxToBox(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other)
{
	const auto& rb1 = owner.lock()->GetRigidbody().lock();
	const auto& rb2 = other.lock()->GetRigidbody().lock();

	// ���[���h�}�g���b�N�X�擾
	XMFLOAT4X4 mW1 = owner.lock()->m_spTransform.lock()->GetWorldMatrix();
	XMFLOAT4X4 mW2 = other.lock()->m_spTransform.lock()->GetWorldMatrix();

	// ���S���W�擾
	Vector3 vP1, vP2;

	// ���S���W�Ԃ̃x�N�g�������߂�
	XMVECTOR vD;
	vP1 = owner.lock()->m_spTransform.lock()->GetPosition() + owner.lock()->GetCenter();
	if (rb1)
	{
		const auto velocity = rb1->GetVelocity();
		vP1 += velocity;
	}
	vP2 = other.lock()->m_spTransform.lock()->GetPosition() + owner.lock()->GetCenter();
	vD = XMVectorSet(vP2->x - vP1->x, vP2->y - vP1->y, vP2->z - vP1->z, 0.0f);

	// ���f�����W�������߂�
	XMVECTOR vN[8];
	vN[0] = XMVectorSet(mW1._11, mW1._12, mW1._13, 0.0f);
	vN[1] = XMVectorSet(mW1._21, mW1._22, mW1._23, 0.0f);
	vN[2] = XMVectorSet(mW1._31, mW1._32, mW1._33, 0.0f);
	vN[4] = XMVectorSet(mW2._11, mW2._12, mW2._13, 0.0f);
	vN[5] = XMVectorSet(mW2._21, mW2._22, mW2._23, 0.0f);
	vN[6] = XMVectorSet(mW2._31, mW2._32, mW2._33, 0.0f);

	// OBB�̑傫��(����)���|�����x�N�g�������߂�
	Vector3 half = owner.lock()->GetColliderSize() / 2;
	Vector3 half2 = other.lock()->GetColliderSize() / 2;
	XMFLOAT3 vBB1 = half.m_vector;
	XMFLOAT3 vBB2 = half2.m_vector;
	XMVECTOR vL[8];
	vL[0] = XMVectorSet(mW1._11 * vBB1.x, mW1._12 * vBB1.x, mW1._13 * vBB1.x, 0.0f);
	vL[1] = XMVectorSet(mW1._21 * vBB1.y, mW1._22 * vBB1.y, mW1._23 * vBB1.y, 0.0f);
	vL[2] = XMVectorSet(mW1._31 * vBB1.z, mW1._32 * vBB1.z, mW1._33 * vBB1.z, 0.0f);
	vL[3] = XMVectorSet(mW2._11 * vBB2.x, mW2._12 * vBB2.x, mW2._13 * vBB2.x, 0.0f);
	vL[4] = XMVectorSet(mW2._21 * vBB2.y, mW2._22 * vBB2.y, mW2._23 * vBB2.y, 0.0f);
	vL[5] = XMVectorSet(mW2._31 * vBB2.z, mW2._32 * vBB2.z, mW2._33 * vBB2.z, 0.0f);

	// ��������₪�ʂ̖@���x�N�g��(���f�����W��)
	float fL, f, fD;
	for (int i = 0; i < 6; ++i)
	{
		// ���������
		XMVECTOR& vS = vN[i];
		// OBB�̉e(�̔���)�̍��v
		fL = 0.0f;
		for (int j = 0; j < 6; ++j)
		{
			XMStoreFloat(&f, XMVector3Dot(vS, vL[j]));
			fL += fabsf(f);
		}
		// ���S���W�Ԃ̋����Ɣ�r
		XMStoreFloat(&fD, XMVector3Dot(vS, vD));
		fD = fabsf(fD);
		// �������Ă��Ȃ��ꍇ�I��
		if (fL < fD)	return false;
	}

	// ��������₪���ꂼ��̕ӂɐ����ȃx�N�g��
	XMVECTOR vS;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 3; j < 6; ++j)
		{
			// �������������߂�
			vS = XMVector3Normalize(XMVector3Cross(vN[i], vN[j]));
			// OBB�̉e(�̔���)�̍��v
			fL = 0.0f;
			for (int k = 0; k < 6; ++k)
			{
				XMStoreFloat(&f, XMVector3Dot(vS, vL[k]));
				fL += fabsf(f);
			}
			// ���S���W�Ԃ̋����Ɣ�r
			XMStoreFloat(&fD, XMVector3Dot(vS, vD));
			fD = fabsf(fD);
			// �������Ă��Ȃ��ꍇ�I��
			if (fL < fD)	return false;
		}
	}

	// �@��(��)
	Vector3 normal(0.0f, 0.0f, 1.0f);

	// ���������̗L�薳��
	if (rb1 && rb1->GetUsePhysics())
	{
		// �����v�Z
		rb1->CollisionPhysics(rb2, normal);
	}

	// �����܂ŗ����瓖�����Ă���
	return true;
}


/**
* @brief	���Ǝl�p
* @detail	�l�p�`�̊p�x��0�x�ɂ��Ĕ�������
* @param	owner	���g�̃R���C�_�[
* @param	other	����̃R���C�_�[
* @return	��������/�������ĂȂ�
*/
bool SphereToBox(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other)
{
	// �l�p�`�̒��_�����_�Ƃ������S���W
	Vector3 rectHalfSize = other.lock()->GetColliderSize() / 2;
	Vector3 rectCenterPos = Vector3(rectHalfSize->x, 0.0f, rectHalfSize->z);

	// �l�p�`�̍��W����ɂ����~�̒��S���W
	Vector3 v = owner.lock()->m_spTransform.lock()->GetPosition() - other.lock()->m_spTransform.lock()->GetPosition();
	Vector3 distance = GetRotateVector(v, other.lock()->m_spTransform.lock()->GetRotation()->y);	
	Vector3 circleCenterPos = rectCenterPos + distance;

	// �Z���^�[���f
	circleCenterPos += owner.lock()->GetCenter();
	rectCenterPos += other.lock()->GetCenter();

	// �{�b�N�X�̍ő�ŏ�
	Vector3 boxMax = Vector3(rectCenterPos->x + rectHalfSize->x, rectCenterPos->y, rectCenterPos->z + rectHalfSize->z);
	Vector3 boxMin = Vector3(rectCenterPos->x - rectHalfSize->x, rectCenterPos->y, rectCenterPos->z - rectHalfSize->z);

	// ���a�擾
	float radius = owner.lock()->GetColliderSize()->x;

	// �ŒZ�������v�Z
	Vector3 vlen = LenAABBToPoint(boxMin, boxMax, circleCenterPos);
	float len = Length(vlen);

	// ����
	if (len >= radius)	return false;

	// ���W�b�h�{�f�B�擾
	const auto& rb1 = owner.lock()->GetRigidbody().lock();
	const auto& rb2 = other.lock()->GetRigidbody().lock();

	if (rb1 && rb1->GetUsePhysics())
	{
		// �g�����X�t�H�[���擾
		const auto& ownerTrans = owner.lock()->m_spTransform.lock();

		// �����v�Z
		//rb1->CollisionPhysics(rb2, Normalize(vlen));

		// �����o��
		// �x�N�g���Ɋp�x�𔽉f������
		vlen = GetRotateVector(vlen, -other.lock()->m_spTransform.lock()->GetRotation()->y);
		float len = Length(vlen);

		len = radius - len;
		Vector3 vec = Normalize(vlen) * len;
		Vector3 pos = ownerTrans->GetPosition();
		pos += vec;
		ownerTrans->SetPosition(pos);
	}
	return true;
}


/**
* @brief	�l�p�Ƌ�
* @param	owner	���g�̃R���C�_�[
* @param	other	����̃R���C�_�[
* @return	��������/�������ĂȂ�
*/
bool BoxToSphere(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other)
{
	// �g�����X�t�H�[���擾
	const auto& ownerTrans = owner.lock()->m_spTransform.lock();
	const auto& otherTrans = other.lock()->m_spTransform.lock();

	// ���S���W
	Vector3 boxPos = ownerTrans->GetPosition() + owner.lock()->GetCenter();
	Vector3 spherePos = otherTrans->GetPosition() + other.lock()->GetCenter();

	// �T�C�Y
	Vector3 boxSize = owner.lock()->GetColliderSize() / 2;

	// �{�b�N�X�̍ő�ŏ�
	Vector3 boxMax = Vector3(boxPos->x + boxSize->x, boxPos->y, boxPos->z + boxSize->z);
	Vector3 boxMin = Vector3(boxPos->x - boxSize->x, boxPos->y, boxPos->z - boxSize->z);

	// ���a
	float radius = other.lock()->GetColliderSize()->x;

	// �ŒZ�������v�Z
	Vector3 vlen = LenAABBToPoint(boxMin, boxMax, spherePos);
	float len = Length(vlen);

	// ����
	if (len >= radius)	return false;

	// ���W�b�h�{�f�B�擾
	const auto& rb1 = owner.lock()->GetRigidbody().lock();
	const auto& rb2 = other.lock()->GetRigidbody().lock();

	if (rb1 && rb1->GetUsePhysics())
	{
		// �����v�Z
		//rb1->CollisionPhysics(rb2, Normalize(vlen));

		// �����o��
		len = radius - len;
		Vector3 vec = Normalize(vlen)*len;
		Vector3 pos = ownerTrans->GetPosition();
		pos -= vec;
		ownerTrans->SetPosition(pos);
	}
	return true;
}
