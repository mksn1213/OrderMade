#pragma once
/**
*
* @file		CRigidbodySystem.h
* @brief	���W�b�h�{�f�B�V�X�e���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CTemplateSystem.h>

// �O��`
class CRigidbody;

/** ���W�b�h�{�f�B�V�X�e���N���X */
class CRigidbodySystem final : public CTemplateSystem<CRigidbody>
{
public:
	CRigidbodySystem();
	virtual ~CRigidbodySystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnUpdate()		override;
};