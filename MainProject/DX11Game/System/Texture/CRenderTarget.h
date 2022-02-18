#pragma once
/**
*
* @file		CRenderTarget.h
* @brief	�����_�[�^�[�Q�b�g�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Texture/CTexture.h>

/** �����_�[�^�[�Q�b�g�N���X */
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