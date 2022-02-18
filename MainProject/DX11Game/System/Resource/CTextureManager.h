#pragma once
/**
*
* @file		CTextureManager.h
* @brief	テクスチャ管理クラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	実装開始
* @date		2022/01/16	シングルトン継承
* @date		2022/01/19	テクスチャ読み込み処理を追加
*
*/

/** インクルード部 */
#include <System/Resource/TextureID.h>
#include <System/Utility/Singleton.h>

#include <DirectXTex.h>
#pragma warning(push)
#pragma warning(disable : 4005)
#include <stdint.h>
#pragma warning(pop)

/** マクロ定義 */
#define TEXTURE_MANAGER (CTextureManager::GetInstance())

/** テクスチャ管理クラス */
class CTextureManager : public Singleton<CTextureManager>
{
public:
	CTextureManager();
	virtual ~CTextureManager();

	HRESULT Init()		final;
	void	Uninit()	final;

	HRESULT LoadTextureAll();
	void ReleaseTextureAll();

	/**
	* @brief	テクスチャの取得
	* @param	type	テクスチャタイプ
	* @return	ID3D11ShaderResourceView	テクスチャ
	*/
	ID3D11ShaderResourceView* GetTexture(ETexture type) { return m_pTextures[static_cast<int>(type)]; }

private:
	ID3D11ShaderResourceView* m_pTextures[static_cast<int>(ETexture::MaxTexture)];
};

HRESULT CreateTextureFromMemory(_In_ ID3D11Device* d3dDevice,
	_In_bytecount_(wicDataSize) const uint8_t* wicData,
	_In_ size_t wicDataSize,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
);

HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const wchar_t* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
);

HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const char* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DirectX::TexMetadata* pTexInfo = nullptr
);
