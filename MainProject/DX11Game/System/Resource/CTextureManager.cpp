/**
*
* @file		CTextureManager.cpp
* @brief	�e�N�X�`���Ǘ��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	�����J�n
* @date		2022/01/16	�V���O���g���p��
* @date		2022/01/19	�e�N�X�`���ǂݍ��ݏ�����ǉ�
*
*/

/** �C���N���[�h�� */
#include <System/Resource/CTextureManager.h>
#include <System/Utility/CSVLoader.h>
#include <System/Defines.h>

//#include <memory.h>
//#include <stdlib.h>
#pragma comment(lib, "DirectXTex")

using namespace DirectX;

/**
* @brief	�R���X�g���N�^
*/
CTextureManager::CTextureManager()
{

}


/**
* @brief	�f�X�g���N�^
*/
CTextureManager::~CTextureManager()
{

}


/**
* @brief	����������
*/
HRESULT CTextureManager::Init()
{
	// �e�N�X�`���ǂݍ���
	return LoadTextureAll();
}


/**
* @brief	�I������
*/
void CTextureManager::Uninit()
{
	// �e�N�X�`�����
	ReleaseTextureAll();
}


/**
* @brief	�S�e�N�X�`���ǂݍ���
* @return	HRESULT		�ǂݍ��݂̐���
*/
HRESULT CTextureManager::LoadTextureAll()
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// �S�e�N�X�`���̃t�@�C���p�X�ǂݍ���
	std::vector<std::string> pathData = LoadStrDataFromCSV("data/csv/path/TexturePath.csv", 1, 1);

	// �S�e�N�X�`���ǂݍ���
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
* @brief	�S�e�N�X�`�����
*/
void CTextureManager::ReleaseTextureAll()
{
	ID3D11Device* pDevice = GetDevice();
	// �e�N�X�`���̉��
	int max = static_cast<int>(ETexture::MaxTexture);
	for (int i = 0; i < max; ++i)
	{
		SAFE_RELEASE(m_pTextures[i]);
	}
}


/**
* @brief	���������琶��
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
* @brief	�t�@�C�����琶��
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
* @brief	�t�@�C�����琶��
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
