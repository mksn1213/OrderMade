/**
*
* @file		CRenderTarget.cpp
* @brief	�����_�[�^�[�Q�b�g�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Texture/CRenderTarget.h>

/**
* @brief	�R���X�g���N�^
*/
CRenderTarget::CRenderTarget()
	: m_pRTV(nullptr)
{

}


/**
* @brief	�f�X�g���N�^
*/
CRenderTarget::~CRenderTarget()
{
	//CTexture::Release();
	//SAFE_RELEASE(m_pRTV);
}


/**
* @brief	���
*/
void CRenderTarget::Release()
{
	CTexture::Release();
	SAFE_RELEASE(m_pRTV);
}


/**
* @brief	���\�[�X����
*/
HRESULT CRenderTarget::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// �e�N�X�`�����\�[�X�쐬
	HRESULT hr = CTexture::CreateResource(desc, nullptr);
	if (FAILED(hr)) { return hr; }

	// �ݒ�
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = desc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// ����
	return GetDevice()->CreateRenderTargetView(m_pTex, &rtvDesc, &m_pRTV);
}