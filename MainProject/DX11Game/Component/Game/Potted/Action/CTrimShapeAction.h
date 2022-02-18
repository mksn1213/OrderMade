#pragma once
/**
*
* @file		CTrimShapeAction.h
* @brief	�`��𐮂���A�N�V�����N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	�����J�n
* @date		2021/12/19	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CAction.h>

/** �`��𐮂���A�N�V�����N���X */
class CTrimShapeAction final : public CAction
{
public:
	CTrimShapeAction();
	virtual ~CTrimShapeAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	// SE�Đ��p
	int m_nFrame;
};