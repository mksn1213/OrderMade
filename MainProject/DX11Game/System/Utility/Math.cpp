/**
*
* @file		Math.cpp
* @brief	�v�Z�֘A�֐�����
* @author	SHONOSUKE MAKITA
* @date		2021/12/31	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Utility/Math.h>
#include <System/Utility/Vector3.h>
#include <iostream>
#include <System/Component/CCollider.h>
#include <System/Component/CTransform.h>

/**
* @brief	����
* @param	vec1
* @param	vec2
*/
float Dot(Vector3 vec1, Vector3 vec2)
{
	float dot;
	dot = vec1->x*vec2->x + vec1->y*vec2->y + vec1->z*vec2->z;
	return dot;
}


/**
* @brief	�O��
* @param	vec1
* @param	vec2
*/
Vector3	Cross(Vector3 vec1, Vector3 vec2)
{
	Vector3 vec;
	vec->x = vec1->y*vec2->z - vec1->z*vec2->y;
	vec->y = vec1->z*vec2->x - vec1->x*vec2->z;
	vec->z = vec1->x*vec2->y - vec1->y*vec2->x;
	return vec;
}


/**
* @brief	�x�N�g���̒���
* @param	vec
*/
float	Length(Vector3 vec)
{
	return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}


/**
* @brief	2�_�Ԃ̋���
* @param	vec1
* @param	vec2
*/
float	Length(Vector3 vec1, Vector3 vec2)
{
	Vector3 vec = vec1 - vec2;
	return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}


/**
* @brief	�x�N�g���̒���(�������Ȃ�)
* @param	vec
*/
float	LengthNotSqrt(Vector3 vec)
{
	return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}


/**
* @brief	�x�N�g���̐��K��
* @param	vec1
*/
Vector3 Normalize(Vector3 vec)
{
	float magnitude = Length(vec);
	if (!magnitude)	return vec;
	vec->x /= magnitude;
	vec->y /= magnitude;
	vec->z /= magnitude;
	return vec;
}


/**
* @brief	�ǂ���x�N�g��
* @param	front		�i�s�x�N�g��
* @param	normal		�@���x�N�g��
*/
Vector3 WallScratchVector(Vector3 front, Vector3 normal)
{
	normal = Normalize(normal);
	return (front - normal * Dot(front, normal));
}


/**
* @brief	���˃x�N�g��
* @param	front		�i�s�x�N�g��
* @param	normal		�@���x�N�g��
*/
Vector3 WallReflectVector(Vector3 front, Vector3 normal)
{
	normal = Normalize(normal);
	return (front - normal * Dot(front, normal) * 2.0f);

}


/**
* @brief	�����x�N�g��
* @param	front		�i�s�x�N�g��
* @param	normal		�@���x�N�g��
*/
Vector3 WallVerticalVector(Vector3 front, Vector3 normal)
{
	normal = Normalize(normal);
	return normal * Dot(front, normal);
}


/**
*
*/
Vector3 GetRotateVector(Vector3 vec, float degree)
{
	float radian = degree * XM_PI / 180;

	float sin = sinf(radian);
	float cos = cosf(radian);

	Vector3 r;
	r->x = vec->x * cos - vec->z * sin;
	r->z = vec->x * sin + vec->z * cos;
	return r;
}


/**
* @brief	�w�肵���ŏ��l�E�ő�l�̒l�ȉ���Ԃ�
*/
float	ClampOnRange(float x, float min, float max)
{
	if (x < min)		return min;
	else if (x > max)	return max;
	else				return x;
}


/**
* @brief	�l�p�`�Ɖ~�̒��S�_�Ƃ̍ŒZ�_��Ԃ�
*/
Vector3	ClampOnRectangle(Vector3 point, std::weak_ptr<CCollider> rectangle)
{
	Vector3 clamp;
	// x����y���̍ŒZ�_���擾���Ԃ�
	Vector3 pos = rectangle.lock()->m_spTransform.lock()->GetPosition();
	Vector3 size = rectangle.lock()->GetColliderSize() / 2;
	Vector3 min = Vector3(pos->x - size->x, pos->y, pos->z - size->z);
	Vector3 max = Vector3(pos->x + size->x, pos->y, pos->z + size->z);
	clamp->x = ClampOnRange(point->x, min->x, max->x);
	clamp->z = ClampOnRange(point->z, min->z, max->z);

	return clamp;
}



Vector3 LenAABBToPoint(Vector3 min, Vector3 max, Vector3 p)
{
	Vector3 len;

	// X��
	if (p->x < min->x)
		len->x += (p->x - min->x);
	if (p->x > max->x)
		len->x += (p->x - max->x);

	//// Y��
	//if (p->y < min->y)
	//	len->y += (p->y - min->y);
	//if (p->y > max->y)
	//	len->y += (p->y - max->y);

	// Z��
	if (p->z < min->z)
		len->z += (p->z - min->z);
	if (p->z > max->z)
		len->z += (p->z - max->z);

	return len;
}


/**
* @brief	�p�����g���b�N�Ȑ����W�v�Z
* @param	startPos	�X�^�[�g���W
* @param	destPos		�ړI���W
* @param	vector		�ڐ��x�N�g��
* @param	destVector	�ړI�ڐ��x�N�g��
* @param	nSplit		������
* @param	nFrame		�o�߃t���[����
* @return	Vector3		�v�Z���W
*/
Vector3 CulcParametricCurves(Vector3 startPos, Vector3 destPos, Vector3 vector, Vector3 destVector, int nSplit, int nFrame)
{
	// �Ȑ��̌v�Z
	float t = 1.0f / nSplit * nFrame;
	float H00, H01, H10, H11;
	H00 = (t - 1) * (t - 1) * (2 * t + 1);
	H01 = t * t * (3 - 2 * t);
	H10 = (1 - t) * (1 - t) * t;
	H11 = (t - 1) * t * t;
	Vector3 pos;
	pos->x = (float)(H00 * startPos->x + H01 * destPos->x + H10 * vector->x + H11 * destVector->x);
	pos->y = (float)(H00 * startPos->y + H01 * destPos->y + H10 * vector->y + H11 * destVector->y);
	pos->z = (float)(H00 * startPos->z + H01 * destPos->z + H10 * vector->z + H11 * destVector->z);
	return pos;
}