/**
*
* @file		CLight.cpp
* @brief	���C�g�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	�����J�n
* @date		2022/01/21	���C�g�}�l�[�W���[���쐬
*
*/

/** �C���N���[�h */
#include <System/Light/CLight.h>

/** �}�N����` */
namespace
{
	const XMFLOAT4 DIFFUSE   = XMFLOAT4(1.0f,  1.0f,  1.0f,  1.0f);
	const XMFLOAT4 AMBIENT   = XMFLOAT4(0.1f,  0.1f,  0.1f,  1.0f);
	const XMFLOAT4 SPECULAR	 = XMFLOAT4(0.2f,  0.2f,  0.2f,  1.0f);
	const XMFLOAT3 DIRECTION = XMFLOAT3(0.5f, -1.0f,  1.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CLight::CLight()
	: m_diffuse(DIFFUSE)
	, m_ambient(AMBIENT)
	, m_specular(SPECULAR)
	, m_bIsEnable(false)
{
	XMStoreFloat3(&m_direction, XMVector3Normalize(XMLoadFloat3(&DIRECTION)));
}


/**
* @brief	�f�X�g���N�^
*/
CLight::~CLight()
{

}


/**
* @brief	�X�V����
*/
void CLight::Update()
{

}