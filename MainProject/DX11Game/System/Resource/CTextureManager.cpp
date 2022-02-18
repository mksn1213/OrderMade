/**
*
* @file		CTextureManager.cpp
* @brief	テクスチャ管理クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	実装開始
* @date		2022/01/16	シングルトン継承
* @date		2022/01/19	テクスチャ読み込み処理を追加
*
*/

/** インクルード部 */
#include <System/Resource/CTextureManager.h>
#include <System/Utility/CSVLoader.h>
#include <System/Defines.h>

//#include <memory.h>
//#include <stdlib.h>
#pragma comment(lib, "DirectXTex")

using namespace DirectX;

/**
* @brief	コンストラクタ
*/
CTextureManager::CTextureManager()
{

}


/**
* @brief	デストラクタ
*/
CTextureManager::~CTextureManager()
{

}


/**
* @brief	初期化処理
*/
HRESULT CTextureManager::Init()
{
	// テクスチャ読み込み
	return LoadTextureAll();
}


/**
* @brief	終了処理
*/
void CTextureManager::Uninit()
{
	// テクスチャ解放
	ReleaseTextureAll();
}


/**
* @brief	全テクスチャ読み込み
* @return	HRESULT		読み込みの成否
*/
HRESULT CTextureManager::LoadTextureAll()
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// 全テクスチャのファイルパス読み込み
	std::vector<std::string> pathData = LoadStrDataFromCSV("data/csv/path/TexturePath.csv", 1, 1);

	// 全テクスチャ読み込み
	HRESULT hr = S_OK;
	int max = static_cast<int>(ETexture::MaxTexture);
	for (int i = 0; i < max; ++i)
	{
		//SAFE_RELEASE(m_pTextures[i]);
		if (CreateTextureFromFile(pDevice, pathData.at(i).c_str(), &m_pTextures[i]))
		{
			hr = E_FAIL;
			break;
		}
	}
	return hr;
}


/**
* @brief	全テクスチャ解放
*/
void CTextureManager::ReleaseTextureAll()
{
	ID3D11Device* pDevice = GetDevice();
	// テクスチャの解放
	int max = static_cast<int>(ETexture::MaxTexture);
	for (int i = 0; i < max; ++i)
	{
		SAFE_RELEASE(m_pTextures[i]);
	}
}


/**
* @brief	メモリから生成
*/
HRESULT CreateTextureFromMemory(_In_ ID3D11Device* d3dDevice,
	_In_bytecount_(wicDataSize) const uint8_t* wicData,
	_In_ size_t wicDataSize,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ TexMetadata* pTexInfo)
{
	*textureView = nullptr;
	TexMetadata meta;
	ScratchImage image;
	HRESULT hr;
	if (wicDataSize >= 18 && memcmp(&wicData[wicDataSize - 18], "TRUEVISION-XFILE.", 18) == 0) {
		hr = LoadFromTGAMemory(wicData, wicDataSize, &meta, image);
	}
	else if (wicDataSize >= 4 && memcmp(wicData, "DDS ", 4) == 0) {
		hr = LoadFromDDSMemory(wicData, wicDataSize, DDS_FLAGS_FORCE_RGB, &meta, image);
	}
	else {
		hr = LoadFromWICMemory(wicData, wicDataSize, WIC_FLAGS_FORCE_RGB, &meta, image);
	}
	if (FAILED(hr)) return hr;
	if (pTexInfo) *pTexInfo = meta;
	return CreateShaderResourceView(d3dDevice, image.GetImages(), image.GetImageCount(), meta, textureView);
}


/**
* @brief	ファイルから生成
*/
HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const wchar_t* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ TexMetadata* pTexInfo)
{
	*textureView = nullptr;
	TexMetadata meta;
	ScratchImage image;
	WCHAR wszExt[_MAX_EXT];
	_wsplitpath(szFileName, nullptr, nullptr, nullptr, wszExt);
	HRESULT hr;
	if (_wcsicmp(wszExt, L".tga") == 0)
		hr = LoadFromTGAFile(szFileName, &meta, image);
	else if (_wcsicmp(wszExt, L".dds") == 0)
		hr = LoadFromDDSFile(szFileName, DDS_FLAGS_FORCE_RGB, &meta, image);
	else
		hr = LoadFromWICFile(szFileName, WIC_FLAGS_FORCE_RGB, &meta, image);
	if (FAILED(hr)) return hr;
	if (pTexInfo) *pTexInfo = meta;
	return CreateShaderResourceView(d3dDevice, image.GetImages(), image.GetImageCount(), meta, textureView);
}


/**
* @brief	ファイルから生成
*/
HRESULT CreateTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const char* szFileName,
	_Out_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ TexMetadata* pTexInfo)
{
	WCHAR wszTexFName[_MAX_PATH];
	int nLen = MultiByteToWideChar(CP_ACP, 0, szFileName, lstrlenA(szFileName), wszTexFName, _countof(wszTexFName));
	if (nLen <= 0) return E_FAIL;
	wszTexFName[nLen] = L'\0';
	return CreateTextureFromFile(d3dDevice, wszTexFName, textureView, pTexInfo);
}
