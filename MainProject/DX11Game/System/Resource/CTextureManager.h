#pragma once
/**
*
* @file		CTextureManager.h
* @brief	�e�N�X�`���Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	�����J�n
* @date		2022/01/16	�V���O���g���p��
* @date		2022/01/19	�e�N�X�`���ǂݍ��ݏ�����ǉ�
*
*/

/** �C���N���[�h�� */
#include <System/Resource/TextureID.h>
#include <System/Utility/Singleton.h>

#include <DirectXTex.h>
#pragma warning(push)
#pragma warning(disable : 4005)
#include <stdint.h>
#pragma warning(pop)

/** �}�N����` */
#define TEXTURE_MANAGER (CTextureManager::GetInstance())

/** �e�N�X�`���Ǘ��N���X */
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
	* @brief	�e�N�X�`���̎擾
	* @param	type	�e�N�X�`���^�C�v
	* @return	ID3D11ShaderResourceView	�e�N�X�`��
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
