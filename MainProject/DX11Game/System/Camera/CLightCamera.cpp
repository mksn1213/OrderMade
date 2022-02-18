/**
*
* @file		CLightCamera.cpp
* @brief	���C�g�J�����N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Camera/CLightCamera.h>

/**
* @brief	�R���X�g���N�^
*/
CLightCamera::CLightCamera()
{
	m_pos = Vector3(0.0f, 50.0f, 0.0f);
	m_screenSize = XMFLOAT2(300.0f, 300.0f);
	SetDirection(Vector3(0.5f, -1.0f, 1.0f));
	Enable(true);
}


/**
* @brief	�f�X�g���N�^
*/
CLightCamera::~CLightCamera()
{

}


/**
* @brief	�v���W�F�N�V�����s��v�Z
* @return	�v���W�F�N�V�����s��
*/
XMMATRIX CLightCamera::CalcProjection()
{
	return XMMatrixOrthographicLH(m_screenSize.x, m_screenSize.y, m_fNearClip, m_fFarClip);
}


/**
* @brief	�v���W�F�N�V�����s��v�Z
* @return	�v���W�F�N�V�����s��
*/
void CLightCamera::SetDirection(Vector3 dir)
{
	XMStoreFloat3(&dir.m_vector, XMVector3Normalize(XMLoadFloat3(&dir.m_vector)));
	m_look = m_pos + dir;
}
