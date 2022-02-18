#pragma once
/**
*
* @file		CBakeAction.h
* @brief	�Ă��A�N�V�����N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	�����J�n
* @date		2021/12/19	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CAction.h>

/** �Ă��A�N�V�����N���X */
class CBakeAction final : public CAction
{
public:
	CBakeAction();
	virtual ~CBakeAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	// �G�t�F�N�g�Đ��p
	int		m_nFrame;
	Vector3 m_effectPos;
};