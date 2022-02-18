#pragma once
/**
*
* @file		CTakeAction.h
* @brief	���A�N�V�����N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	�����J�n
* @date		2021/12/16	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CAction.h>

/** ���A�N�V�����N���X */
class CTakeAction final : public CAction
{
public:
	CTakeAction();
	virtual ~CTakeAction();
	
	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;
};
