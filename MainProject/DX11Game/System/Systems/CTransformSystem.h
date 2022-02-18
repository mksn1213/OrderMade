#pragma once
/**
*
* @file		CTransformSystem.h
* @brief	�g�����X�t�H�[���V�X�e���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CTemplateSystem.h>

// �O��`
class CTransform;

/** �g�����X�t�H�[���V�X�e���N���X */
class CTransformSystem final : public CTemplateSystem<CTransform>
{
public:
	CTransformSystem();
	virtual ~CTransformSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnUpdate()		override;
};