#pragma once
/**
*
* @file		CTexture.h
* @brief	テクスチャクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	実装開始
*
*/

/** インクルード部 */
#include <System/Defines.h>
#include <functional>

class CTexture
{
public:
	friend class TextureFactory;

public:
	CTexture();
	virtual ~CTexture();
	virtual void Release();

	template <class T>
	void Filter(T filter);

	UINT GetWidth()		const { return m_width; }
	UINT GetHeight()	const { return m_height; }
	ID3D11ShaderResourceView* GetResource() const { return m_pSRV; }

private:
	void Clone(std::function<void(void* pData, UINT dataSize, UINT width, UINT height)>);
	BYTE GetPixelSize(DXGI_FORMAT format);

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC &desc, const void* pData = nullptr);

private:
	// テクスチャ横幅
	UINT m_width;
	// テクスチャ縦幅
	UINT m_height;

	ID3D11ShaderResourceView *m_pSRV;

protected:
	ID3D11Texture2D* m_pTex;
};

template <class T>
void CTexture::Filter(T filter)
{
	Clone([this, &filter](void* pData, UINT dataSize, UINT width, UINT height)->void
	{
		// 画像情報取得
		D3D11_TEXTURE2D_DESC texDesc;
		m_pTex->GetDesc(&texDesc);

		// フィルターが適用できるフォーマットかチェック
		if (filter.CheckFormat(texDesc.Format))
		{
			// フィルターを適用
			filter.Apply(pData, dataSize, texDesc.Width, texDesc.Height);
			// 以前のリソースを破棄
			Release();
			// フィルター適用済みデータで作成
			CreateResource(texDesc, pData);
		}
	}
	);
}
