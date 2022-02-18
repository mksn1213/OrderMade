#pragma once
/**
*
* @file		CLightCamera.h
* @brief	ライトカメラクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	実装開始
*
*/

/** インクルード部 */
#include <System/Camera/CCamera.h>

/** ライトカメラクラス */
class CLightCamera final : public CCamera
{
public:
	CLightCamera();
	virtual ~CLightCamera();

	void SetDirection(Vector3 dir);

private:
	XMMATRIX CalcProjection() override;
};