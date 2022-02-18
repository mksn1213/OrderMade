/**
*
* @file		CLightCamera.cpp
* @brief	ライトカメラクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	実装開始
*
*/

/** インクルード部 */
#include <System/Camera/CLightCamera.h>

/**
* @brief	コンストラクタ
*/
CLightCamera::CLightCamera()
{
	m_pos = Vector3(0.0f, 50.0f, 0.0f);
	m_screenSize = XMFLOAT2(300.0f, 300.0f);
	SetDirection(Vector3(0.5f, -1.0f, 1.0f));
	Enable(true);
}


/**
* @brief	デストラクタ
*/
CLightCamera::~CLightCamera()
{

}


/**
* @brief	プロジェクション行列計算
* @return	プロジェクション行列
*/
XMMATRIX CLightCamera::CalcProjection()
{
	return XMMatrixOrthographicLH(m_screenSize.x, m_screenSize.y, m_fNearClip, m_fFarClip);
}


/**
* @brief	プロジェクション行列計算
* @return	プロジェクション行列
*/
void CLightCamera::SetDirection(Vector3 dir)
{
	XMStoreFloat3(&dir.m_vector, XMVector3Normalize(XMLoadFloat3(&dir.m_vector)));
	m_look = m_pos + dir;
}
