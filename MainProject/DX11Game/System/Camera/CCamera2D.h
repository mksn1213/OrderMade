#pragma once
/**
*
* @file		CCamera2D.h
* @brief	カメラ2Dクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	実装開始
*
*/

/** インクルード */
#include <System/Camera/CCamera.h>

/** カメラ2Dクラス */
class CCamera2D final : public CCamera
{
public:
	CCamera2D();
	virtual ~CCamera2D();

	void Update() override;

private:
	XMMATRIX CalcProjection() override;
};