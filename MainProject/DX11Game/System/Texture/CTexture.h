#pragma once
/**
*
* @file		CTexture.h
* @brief	�e�N�X�`���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	�����J�n
*
*/

/** �C���N���[�h�� */
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
	// �e�N�X�`������
	UINT m_width;
	// �e�N�X�`���c��
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
		// �摜���擾
		D3D11_TEXTURE2D_DESC texDesc;
		m_pTex->GetDesc(&texDesc);

		// �t�B���^�[���K�p�ł���t�H�[�}�b�g���`�F�b�N
		if (filter.CheckFormat(texDesc.Format))
		{
			// �t�B���^�[��K�p
			filter.Apply(pData, dataSize, texDesc.Width, texDesc.Height);
			// �ȑO�̃��\�[�X��j��
			Release();
			// �t�B���^�[�K�p�ς݃f�[�^�ō쐬
			CreateResource(texDesc, pData);
		}
	}
	);
}
