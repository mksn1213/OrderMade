#pragma once
/**
*
* @file		CActionGaugeBaseUI.h
* @brief	�A�N�V�����Q�[�W�x�[�XUI�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/26	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �A�N�V�����Q�[�W�x�[�XUI�N���X */
class CActionGaugeBaseUI final : public CScriptBase
{
public:
	CActionGaugeBaseUI();
	virtual ~CActionGaugeBaseUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
};
