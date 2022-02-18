#pragma once
/**
*
* @file		Collision.h
* @brief	当たり判定関数群
* @author	SHONOSUKE MAKITA
* @date		2021/01/01	実装開始
* @date		2021/01/01	OBBとOBBの判定作成
* @date		2021/01/03	球と四角形の判定作成
*
*/

class Vector3;
class CCollider;

bool CircleToPoint		(Vector3 circlePos,float rad, Vector3 point);
bool SphereToSpphere	(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other);
bool SphereToBox		(std::weak_ptr<CCollider> ownder, std::weak_ptr<CCollider> other);
bool BoxToBox			(std::weak_ptr<CCollider> ownder, std::weak_ptr<CCollider> other);
bool BoxToSphere		(std::weak_ptr<CCollider> ownder, std::weak_ptr<CCollider> other);
