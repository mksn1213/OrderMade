#pragma once
/**
*
* @file		CWater.h
* @brief	���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/09	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** ���N���X */
class CWater final : public CScriptBase
{
public:
	CWater();
	virtual ~CWater();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
};
