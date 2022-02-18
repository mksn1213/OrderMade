#pragma once
/**
*
* @file		CField.h
* @brief	�t�B�[���h�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/20	�����J�n
* @date		2021/12/05	�R���|�[�l���g�ɕύX
* @date		2022/01/30	CScriptBase���p��
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �t�B�[���h�N���X */
class CField final : public CScriptBase
{
public:
	CField();
	virtual ~CField();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
};