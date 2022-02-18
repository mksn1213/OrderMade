/**
*
* @file		CDepthStencilState.cpp
* @brief	�[�x�X�e���V���X�e�[�g�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Graphics/CDepthStencilState.h>
#include <System/Graphics/CGraphics.h>

/**
* @brief	�R���X�g���N�^
*/
CDepthStencilState::CDepthStencilState()
	: m_pState(nullptr)
{

}


/**
* @brief	�f�X�g���N�^
*/
CDepthStencilState::~CDepthStencilState()
{
	SAFE_RELEASE(m_pState);
}


/**
* @brief	�쐬
*/
HRESULT CDepthStencilState::Create(bool depthEnable, bool stencilEnable)
{
	D3D11_DEPTH_STENCIL_DESC desc;
	// �[�x�l
	desc.DepthEnable = depthEnable;
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	// �X�e���V��
	desc.StencilEnable = stencilEnable;
	desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL;
	desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	desc.BackFace.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL;

	// ����
	return GetDevice()->CreateDepthStencilState(&desc, &m_pState);
}


/**
* @brief	���蓖��
*/
void CDepthStencilState::Bind()
{
	GetDeviceContext()->OMSetDepthStencilState(m_pState, 0);
	GRAPHICS->SetDepthStencilState(this);
}
