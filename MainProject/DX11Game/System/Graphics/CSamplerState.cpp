/**
*
* @file		CSamplerState.cpp
* @brief	�T���v���[�X�e�[�g�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Graphics/CSamplerState.h>
#include <System/Graphics/CGraphics.h>

/**
* @brief	�R���X�g���N�^
*/
CSamplerState::CSamplerState()
	: m_pState(nullptr)
{

}


/**
* @brief	�f�X�g���N�^
*/
CSamplerState::~CSamplerState()
{

}


/**
* @brief	�쐬
*/
HRESULT CSamplerState::Create(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address)
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = filter;
	desc.AddressU = address;
	desc.AddressV = address;
	desc.AddressW = address;
	return GetDevice()->CreateSamplerState(&desc, &m_pState);
}


/**
* @brief	���蓖��
*/
void CSamplerState::Bind()
{
	GetDeviceContext()->PSSetSamplers(0, 1, &m_pState);
	GRAPHICS->SetSamplerState(this);
}