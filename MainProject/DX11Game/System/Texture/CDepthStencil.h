#pragma once
/**
*
* @file		CRenderTarget.h
* @brief	深度ステンシルクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	実装開始
*
*/

/** インクルード部 */
#include <System/Texture/CTexture.h>

/** 深度ステンシルクラス */
class CDepthStencil :public CTexture
{
public:
	friend class TextureFactory;

public:
	CDepthStencil();
	virtual ~CDepthStencil();

	virtual void Release();

	ID3D11DepthStencilView* GetView() const { return m_pDSV; }

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11DepthStencilView* m_pDSV;
};