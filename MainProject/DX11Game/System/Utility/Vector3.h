#pragma once
/**
*
* @file		Vector3.h
* @brief	ベクター3クラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/29	実装開始
*
*/

/** インクルード部 */
#include <DirectXMath.h>

using namespace DirectX;

/** ベクター3クラス */
class Vector3
{
public:
	Vector3() { m_vector = XMFLOAT3(0.0f, 0.0f, 0.0f); }
	Vector3(XMFLOAT3 vec) { m_vector = vec; }
	Vector3(float x, float y, float z) { m_vector.x = x; m_vector.y = y; m_vector.z = z; }

	Vector3 operator + (const Vector3 &vec)const	{ return Vector3(m_vector.x + vec.m_vector.x, m_vector.y + vec.m_vector.y, m_vector.z + vec.m_vector.z); }
	Vector3 operator - (const Vector3 &vec)const	{ return Vector3(m_vector.x - vec.m_vector.x, m_vector.y - vec.m_vector.y, m_vector.z - vec.m_vector.z); }
	Vector3 operator * (float value) const			{ return Vector3(m_vector.x * value, m_vector.y * value, m_vector.z * value); }
	Vector3 operator / (float value) const			{ return Vector3(m_vector.x / value, m_vector.y / value, m_vector.z / value); }

	void operator += (const Vector3 &vec)	{ (*this) = (*this) + vec; }
	void operator -= (const Vector3 &vec)	{ (*this) = (*this) - vec; }
	void operator *= (float value)			{ (*this) = (*this) * value; }
	void operator /= (float value)			{ (*this) = (*this) / value; }

	XMFLOAT3* operator -> () { return &m_vector; }

	static Vector3 one()		{ return Vector3( 1.0f,  1.0f,  1.0f); }
	static Vector3 zero()		{ return Vector3( 0.0f,  0.0f,  0.0f); }
	static Vector3 up()			{ return Vector3( 0.0f,  1.0f,  0.0f); }
	static Vector3 down()		{ return Vector3( 0.0f, -1.0f,  0.0f); }
	static Vector3 right()		{ return Vector3( 1.0f,  0.0f,  0.0f); }
	static Vector3 left()		{ return Vector3(-1.0f,  0.0f,  0.0f); }
	static Vector3 forward()	{ return Vector3( 0.0f,  0.0f,  1.0f); }
	static Vector3 back()		{ return Vector3( 0.0f,  0.0f, -1.0f); }

	XMFLOAT3 m_vector;
};