#pragma once
/**
*
* @file		CPutWaterAction.h
* @brief	��������A�N�V�����N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/06	�����J�n
* @date		2021/12/18	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CAction.h>

/** ��������A�N�V�����N���X */
class CPutWaterAction final : public CAction
{
public:
	CPutWaterAction();
	virtual ~CPutWaterAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	bool m_bIsWater;
};