#pragma once
/**
*
* @file		CCollisionSystem.h
* @brief	�R���W�����V�X�e���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CTemplateSystem.h>

// �O��`
class CCollider;

/** �R���W�����V�X�e���N���X */
class CCollisionSystem final : public CTemplateSystem<CCollider>
{
public:
	CCollisionSystem();
	virtual ~CCollisionSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnUpdate()		override;
};