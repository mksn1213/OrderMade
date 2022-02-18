#pragma once
/**
*
* @file		CPlantAction.h
* @brief	�A����A�N�V�����N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/28	�����J�n
* @date		2021/12/17	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CAction.h>

/** �A����A�N�V�����N���X */
class CPlantAction final : public CAction
{
public:
	CPlantAction();
	virtual ~CPlantAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	// SE�Đ��p
	int m_nFrame;
};
