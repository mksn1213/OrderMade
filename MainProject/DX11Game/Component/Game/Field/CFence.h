#pragma once
/**
*
* @file		CFence.h
* @brief	��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/01/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** ��N���X */
class CFence final : public CScriptBase
{
public:
	CFence();
	virtual ~CFence();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
};