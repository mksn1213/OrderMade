#pragma once
/**
*
* @file		CLightCamera.h
* @brief	���C�g�J�����N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Camera/CCamera.h>

/** ���C�g�J�����N���X */
class CLightCamera final : public CCamera
{
public:
	CLightCamera();
	virtual ~CLightCamera();

	void SetDirection(Vector3 dir);

private:
	XMMATRIX CalcProjection() override;
};