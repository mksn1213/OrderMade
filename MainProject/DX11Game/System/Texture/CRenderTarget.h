#pragma once
/**
*
* @file		CRenderTarget.h
* @brief	レンダーターゲットクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	実装開始
*
*/

/** インクルード部 */
#include <System/Texture/CTexture.h>

/** レンダーターゲットクラス */
class CRenderTarget :public CTexture
{
public:
	friend class TextureFactory;

public:
	CRenderTarget();
	virtual ~CRenderTarget();

	virtual void Release();

	ID3D11RenderTargetView* GetView() const { return m_pRTV; }

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11RenderTargetView* m_pRTV;
};