#pragma once
/**
*
* @file		CPutAction.h
* @brief	�u���A�N�V�����N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	�����J�n
* @date		2021/12/16	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CAction.h>

/** �u���A�N�V�����N���X */
class CPutAction final : public CAction
{
public:
	CPutAction();
	virtual ~CPutAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;
};
