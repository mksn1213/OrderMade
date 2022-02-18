/**
*
* @file		CRenderTarget.cpp
* @brief	�[�x�X�e���V���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Texture/CDepthStencil.h>

/**
* @brief	�R���X�g���N�^
*/
CDepthStencil::CDepthStencil()
	: m_pDSV(nullptr)
{

}


/**
* @brief	�R���X�g���N�^
*/
CDepthStencil::~CDepthStencil()
{

}


/**
* @brief	���
*/
void CDepthStencil::Release()
{
	CTexture::Release();
	SAFE_RELEASE(m_pDSV);
}


HRESULT CDepthStencil::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// �X�e���V���g�p����
	bool useStencil = (desc.Format == DXGI_FORMAT_D24_UNORM_S8_UINT);

	// ���\�[�X����
	desc.Format = useStencil ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
	HRESULT hr = CTexture::CreateResource(desc, nullptr);

	// �ݒ�
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = useStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	// ����
	return GetDevice()->CreateDepthStencilView(m_pTex, &dsvDesc, &m_pDSV);
}