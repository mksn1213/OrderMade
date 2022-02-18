/**
*
* @file		CRenderTarget.cpp
* @brief	深度ステンシルクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	実装開始
*
*/

/** インクルード部 */
#include <System/Texture/CDepthStencil.h>

/**
* @brief	コンストラクタ
*/
CDepthStencil::CDepthStencil()
	: m_pDSV(nullptr)
{

}


/**
* @brief	コンストラクタ
*/
CDepthStencil::~CDepthStencil()
{

}


/**
* @brief	解放
*/
void CDepthStencil::Release()
{
	CTexture::Release();
	SAFE_RELEASE(m_pDSV);
}


HRESULT CDepthStencil::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// ステンシル使用判定
	bool useStencil = (desc.Format == DXGI_FORMAT_D24_UNORM_S8_UINT);

	// リソース生成
	desc.Format = useStencil ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
	HRESULT hr = CTexture::CreateResource(desc, nullptr);

	// 設定
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = useStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	// 生成
	return GetDevice()->CreateDepthStencilView(m_pTex, &dsvDesc, &m_pDSV);
}