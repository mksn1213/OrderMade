#pragma once

/** インクルード部 */
#include <System/Texture/CTexture.h>

class TextureFactory
{
public:
	static CTexture* CreateFromFile(const char* fileName);
	static CTexture* CreateFromData(DXGI_FORMAT format, UINT width, UINT height, const void* pData);
	static CTexture* CreateRenderTarget(DXGI_FORMAT format, UINT width, UINT height);
	static CTexture* CreateRenderTargetFromScreen();
	static CTexture* CreateDepthStencil(UINT width, UINT height, bool useStencil = false);
};