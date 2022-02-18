#pragma once
/**
*
* @file		Collision.h
* @brief	�����蔻��֐��Q
* @author	SHONOSUKE MAKITA
* @date		2021/01/01	�����J�n
* @date		2021/01/01	OBB��OBB�̔���쐬
* @date		2021/01/03	���Ǝl�p�`�̔���쐬
*
*/

class Vector3;
class CCollider;

bool CircleToPoint		(Vector3 circlePos,float rad, Vector3 point);
bool SphereToSpphere	(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other);
bool SphereToBox		(std::weak_ptr<CCollider> ownder, std::weak_ptr<CCollider> other);
bool BoxToBox			(std::weak_ptr<CCollider> ownder, std::weak_ptr<CCollider> other);
bool BoxToSphere		(std::weak_ptr<CCollider> ownder, std::weak_ptr<CCollider> other);
