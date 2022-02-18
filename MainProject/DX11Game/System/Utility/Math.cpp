/**
*
* @file		Math.cpp
* @brief	計算関連関数実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/31	実装開始
*
*/

/** インクルード部 */
#include <System/Utility/Math.h>
#include <System/Utility/Vector3.h>
#include <iostream>
#include <System/Component/CCollider.h>
#include <System/Component/CTransform.h>

/**
* @brief	内積
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
* @brief	外積
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
* @brief	ベクトルの長さ
* @param	vec
*/
float	Length(Vector3 vec)
{
	return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}


/**
* @brief	2点間の距離
* @param	vec1
* @param	vec2
*/
float	Length(Vector3 vec1, Vector3 vec2)
{
	Vector3 vec = vec1 - vec2;
	return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}


/**
* @brief	ベクトルの長さ(平方根なし)
* @param	vec
*/
float	LengthNotSqrt(Vector3 vec)
{
	return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}


/**
* @brief	ベクトルの正規化
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
* @brief	壁ずりベクトル
* @param	front		進行ベクトル
* @param	normal		法線ベクトル
*/
Vector3 WallScratchVector(Vector3 front, Vector3 normal)
{
	normal = Normalize(normal);
	return (front - normal * Dot(front, normal));
}


/**
* @brief	反射ベクトル
* @param	front		進行ベクトル
* @param	normal		法線ベクトル
*/
Vector3 WallReflectVector(Vector3 front, Vector3 normal)
{
	normal = Normalize(normal);
	return (front - normal * Dot(front, normal) * 2.0f);

}


/**
* @brief	垂直ベクトル
* @param	front		進行ベクトル
* @param	normal		法線ベクトル
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
* @brief	指定した最小値・最大値の値以下を返す
*/
float	ClampOnRange(float x, float min, float max)
{
	if (x < min)		return min;
	else if (x > max)	return max;
	else				return x;
}


/**
* @brief	四角形と円の中心点との最短点を返す
*/
Vector3	ClampOnRectangle(Vector3 point, std::weak_ptr<CCollider> rectangle)
{
	Vector3 clamp;
	// x軸とy軸の最短点を取得し返す
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

	// X軸
	if (p->x < min->x)
		len->x += (p->x - min->x);
	if (p->x > max->x)
		len->x += (p->x - max->x);

	//// Y軸
	//if (p->y < min->y)
	//	len->y += (p->y - min->y);
	//if (p->y > max->y)
	//	len->y += (p->y - max->y);

	// Z軸
	if (p->z < min->z)
		len->z += (p->z - min->z);
	if (p->z > max->z)
		len->z += (p->z - max->z);

	return len;
}


/**
* @brief	パラメトリック曲線座標計算
* @param	startPos	スタート座標
* @param	destPos		目的座標
* @param	vector		接線ベクトル
* @param	destVector	目的接線ベクトル
* @param	nSplit		分割数
* @param	nFrame		経過フレーム数
* @return	Vector3		計算座標
*/
Vector3 CulcParametricCurves(Vector3 startPos, Vector3 destPos, Vector3 vector, Vector3 destVector, int nSplit, int nFrame)
{
	// 曲線の計算
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