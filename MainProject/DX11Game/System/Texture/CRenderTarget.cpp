/**
*
* @file		CRenderTarget.cpp
* @brief	レンダーターゲットクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	実装開始
*
*/

/** インクルード部 */
#include <System/Texture/CRenderTarget.h>

/**
* @brief	コンストラクタ
*/
CRenderTarget::CRenderTarget()
	: m_pRTV(nullptr)
{

}


/**
* @brief	デストラクタ
*/
CRenderTarget::~CRenderTarget()
{
	//CTexture::Release();
	//SAFE_RELEASE(m_pRTV);
}


/**
* @brief	解放
*/
void CRenderTarget::Release()
{
	CTexture::Release();
	SAFE_RELEASE(m_pRTV);
}


/**
* @brief	リソース生成
*/
HRESULT CRenderTarget::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// テクスチャリソース作成
	HRESULT hr = CTexture::CreateResource(desc, nullptr);
	if (FAILED(hr)) { return hr; }

	// 設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = desc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// 生成
	return GetDevice()->CreateRenderTargetView(m_pTex, &rtvDesc, &m_pRTV);
}