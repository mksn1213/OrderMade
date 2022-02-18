#pragma once
/**
*
* @file		CScriptSystem.h
* @brief	�X�N���v�g�V�X�e���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CTemplateSystem.h>

// �O��`
class CScriptBase;

/** �X�N���v�g�V�X�e���N���X */
class CScriptSystem final : public CTemplateSystem<CScriptBase>
{
public:
	CScriptSystem();
	virtual ~CScriptSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnUpdate()		override;
};

