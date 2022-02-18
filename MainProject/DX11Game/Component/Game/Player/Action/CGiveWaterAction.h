#pragma once
/**
*
* @file		CGiveWaterAction.h
* @brief	����^����A�N�V�����N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/07	�����J�n
* @date		2021/12/18	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CAction.h>

/** ����^����A�N�V�����N���X */
class CGiveWaterAction final : public CAction
{
public:
	CGiveWaterAction();
	virtual ~CGiveWaterAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	// SE�Đ��p
	int	m_nFrame;
};