#pragma once
/**
*
* @file		Math.h
* @brief	計算関連関数
* @author	SHONOSUKE MAKITA
* @date		2021/12/31	実装開始
*
*/

/** インクルード部 */
#include <iostream>

class Vector3;
class CCollider;

float	Dot(Vector3 vec1, Vector3 vec2);
Vector3	Cross(Vector3 vec1, Vector3 vec2);
float	Length(Vector3 vec);
float	Length(Vector3 vec1, Vector3 vec2);
float	LengthNotSqrt(Vector3 vec);
Vector3 Normalize(Vector3 vec);
Vector3 WallScratchVector(Vector3 front, Vector3 normal);
Vector3 WallReflectVector(Vector3 front, Vector3 normal);
Vector3 WallVerticalVector(Vector3 front, Vector3 normal);
Vector3 GetRotateVector(Vector3 vec, float degree);
float	ClampOnRange(float x, float min, float max);
Vector3	ClampOnRectangle(Vector3 point, std::weak_ptr<CCollider> rectangle);
Vector3 LenAABBToPoint(Vector3 min, Vector3 max, Vector3 p);
Vector3 CulcParametricCurves(Vector3 startPos, Vector3 destPos, Vector3 vector, Vector3 destVector, int nSplit, int nFrame);