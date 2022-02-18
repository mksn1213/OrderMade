#pragma once
/**
*
* @file		CCamera2D.h
* @brief	�J����2D�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	�����J�n
*
*/

/** �C���N���[�h */
#include <System/Camera/CCamera.h>

/** �J����2D�N���X */
class CCamera2D final : public CCamera
{
public:
	CCamera2D();
	virtual ~CCamera2D();

	void Update() override;

private:
	XMMATRIX CalcProjection() override;
};