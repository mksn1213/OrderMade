#pragma once
/**
*
* @file		ShaderList.h
* @brief	�V�F�[�_�[���X�g
* @author	SHONOSUKE MAKITA
* @date		2022/01/18	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Graphics/Shader.h>
#include <System/Renderer/AssimpModel.h>
#include <System/Renderer/CMeshRenderer.h>

/**
* @enum		EVertexShaderKind
* @brief	���_�V�F�[�_�[���
*/
enum EVertexShaderKind
{
	AssimpVS,
	SimpleVS,
	Simple2DVS,
	DepthWriteVS,

	MaxVertexShader
};

/**
* @enum		EPixelShaderKind
* @brief	�s�N�Z���V�F�[�_�[���
*/
enum EPixelShaderKind
{
	AssimpPS,
	SimplePS,
	Simple2DPS,
	DepthWritePS,
	DissolvePS,
	AssimpTargetPS,
	MultiTexturePS,

	MaxPixelShader
};

HRESULT InitShaderResource();
void	UninitShaderResource();
Shader* GetVertexShader(EVertexShaderKind kind);
Shader* GetPixelShader(EPixelShaderKind kind);

// �e�V�F�[�_�[�̃Z�b�g�֐�
void SetAssimpShader(XMFLOAT4X4 mtxWorld, XMFLOAT4X4 mtxTexture, TAssimpMaterial* pMaterial, XMUINT4 flags, SHADER_BONE bone);
void SetSimple2DShader(ID3D11ShaderResourceView* texture, XMFLOAT4X4 proj, XMFLOAT4X4 view, XMFLOAT4X4 world, XMFLOAT4X4 tex);
void SetSimpleShader(CMesh* pMesh, XMMATRIX mtxWorld, bool bBillboard);
void SetDepthWrite(XMFLOAT4X4 world,SHADER_BONE bone, Vector3 pos);
void SetDissolveShader(ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* dissolve, XMFLOAT4X4 proj, XMFLOAT4X4 view, XMFLOAT4X4 world, XMFLOAT4X4 tex);
void SetAssimpTargetShader(XMFLOAT4X4 mtxWorld, XMFLOAT4X4 mtxTexture, TAssimpMaterial* pMaterial, XMUINT4 flags, SHADER_BONE bone);
void SetMultiTextureShader(ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* dissolve,ID3D11ShaderResourceView* multiTexture, ID3D11ShaderResourceView* multiTexture2,float fParam, XMFLOAT4X4 proj, XMFLOAT4X4 view, XMFLOAT4X4 world, XMFLOAT4X4 tex);
