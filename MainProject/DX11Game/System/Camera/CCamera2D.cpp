/**
*
* @file		CCamera2D.cpp
* @brief	カメラ2Dクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	実装開始
*
*/

/** インクルード */
#include <System/Camera/CCamera2D.h>

/**
* @brief	コンストラクタ
*/
CCamera2D::CCamera2D()
{

}


/**
* @brief	デストラクタ
*/
CCamera2D::~CCamera2D()
{

}


/**
* @brief	更新処理
*/
void CCamera2D::Update()
{

}


/**
* @brief	プロジェクション行列計算
* @return	XMMATRIX	プロジェクション行列
*/
XMMATRIX CCamera2D::CalcProjection()
{
	return XMMatrixOrthographicOffCenterLH(
		0.0f, m_screenSize.x, m_screenSize.y, 0.0f, m_fNearClip, m_fFarClip);
}