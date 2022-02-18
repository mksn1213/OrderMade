/**
*
* @file		CCamera2D.cpp
* @brief	�J����2D�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	�����J�n
*
*/

/** �C���N���[�h */
#include <System/Camera/CCamera2D.h>

/**
* @brief	�R���X�g���N�^
*/
CCamera2D::CCamera2D()
{

}


/**
* @brief	�f�X�g���N�^
*/
CCamera2D::~CCamera2D()
{

}


/**
* @brief	�X�V����
*/
void CCamera2D::Update()
{

}


/**
* @brief	�v���W�F�N�V�����s��v�Z
* @return	XMMATRIX	�v���W�F�N�V�����s��
*/
XMMATRIX CCamera2D::CalcProjection()
{
	return XMMatrixOrthographicOffCenterLH(
		0.0f, m_screenSize.x, m_screenSize.y, 0.0f, m_fNearClip, m_fFarClip);
}