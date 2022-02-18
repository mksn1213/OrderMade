/**
*
* @file		ShaderList.cpp
* @brief	�V�F�[�_�[���X�g����
* @author	SHONOSUKE MAKITA
* @date		2022/01/18	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Graphics/ShaderList.h>
#include <System/Texture/CTexture.h>
#include <System/Graphics/ConstantBufferType.h>
#include <System/Graphics/CGraphics.h>
#include <System/Camera/CCameraManager.h>
#include <System/Light/CLightManager.h>
#include <System/Camera/CLightCamera.h>
#include <System/Camera/CCamera2D.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Scene/CSceneManager.h>

/** �}�N����` */
namespace
{
	// ���_�V�F�[�_�[�t�@�C����
	const char* VertexShaderFile[MaxVertexShader] =
	{
		"data/shader/AssimpVS.cso",
		"data/shader/SimpleVS.cso",
		"data/shader/Simple2DVS.cso",
		"data/shader/DepthWriteVS.cso",
	};
	// �s�N�Z���V�F�[�_�[�t�@�C����
	const char* PixelShaderFile[MaxPixelShader] =
	{
		"data/shader/AssimpPS.cso",
		"data/shader/SimplePS.cso", 
		"data/shader/Simple2DPS.cso",
		"data/shader/DepthWritePS.cso",
		"data/shader/DissolvePS.cso",
		"data/shader/AssimpTargetPS.cso",
		"data/shader/MultiTexturePS.cso"
	};
}

/** �O���[�o���ϐ� */
ConstantBuffer*	g_pMatrix;
ConstantBuffer* g_pShadowVPS;

// Assimp���f��
ConstantBuffer* g_pAssimpBuffer1;
ConstantBuffer* g_pAssimpBuffer2;
ConstantBuffer* g_pAssimpBone;

// ���b�V��
ConstantBuffer* g_pMeshBuffer1;
ConstantBuffer* g_pMeshBuffer2;

// �|���S��
ConstantBuffer* g_pPolygonBuffer1;

// �f�B�]���u
ConstantBuffer*	g_pDissolveBuffer;

Shader* g_pVertexShaderList[MaxVertexShader];
Shader* g_pPixelShaderList[MaxPixelShader];

/**
* @brief	�V�F�[�_�[����������
*/
HRESULT InitShaderResource()
{
	HRESULT hr = S_OK;
	for (int i = 0; i < MaxVertexShader; ++i)
	{
		g_pVertexShaderList[i] = new VertexShader;
		hr = g_pVertexShaderList[i]->Load(VertexShaderFile[i]);
		if (FAILED(hr))	return hr;
	}
	for (int i = 0; i < MaxPixelShader; ++i)
	{
		g_pPixelShaderList[i] = new PixelShader;
		hr = g_pPixelShaderList[i]->Load(PixelShaderFile[i]);
		if (FAILED(hr))	return hr;
	}

	// �萔�o�b�t�@�쐬
	g_pMatrix = new ConstantBuffer;
	g_pMatrix->Create(sizeof(XMFLOAT4X4) * 3);
	g_pShadowVPS = new ConstantBuffer;
	g_pShadowVPS->Create(sizeof(XMFLOAT4X4));

	g_pAssimpBuffer1 = new ConstantBuffer;
	g_pAssimpBuffer1->Create(sizeof(SHADER_GLOBAL));
	g_pAssimpBuffer2 = new ConstantBuffer;
	g_pAssimpBuffer2->Create(sizeof(SHADER_MATERIAL));
	g_pAssimpBone = new ConstantBuffer;
	g_pAssimpBone->Create(sizeof(SHADER_BONE));

	g_pMeshBuffer1 = new ConstantBuffer;
	g_pMeshBuffer1->Create(sizeof(SHADER_GLOBAL_MESH));
	g_pMeshBuffer2 = new ConstantBuffer;
	g_pMeshBuffer2->Create(sizeof(SHADER_GLOBAL2_MESH));

	g_pPolygonBuffer1 = new ConstantBuffer;
	g_pPolygonBuffer1->Create(sizeof(SHADER_GLOBAL_POLYGON));

	g_pDissolveBuffer = new ConstantBuffer;
	g_pDissolveBuffer->Create(sizeof(XMFLOAT4));

	return hr;
}


/**
* @brief	�V�F�[�_�[�I������
*/
void UninitShaderResource()
{
	for (int i = 0; i < MaxPixelShader; ++i)
	{
		SAFE_DELETE(g_pPixelShaderList[i]);
	}
	for (int i = 0; i < MaxVertexShader; ++i)
	{
		SAFE_DELETE(g_pVertexShaderList[i]);
	}

	// �萔�o�b�t�@�폜
	SAFE_DELETE(g_pMatrix);
	SAFE_DELETE(g_pShadowVPS);
	SAFE_DELETE(g_pAssimpBuffer1);
	SAFE_DELETE(g_pAssimpBuffer2);
	SAFE_DELETE(g_pAssimpBone);
	SAFE_DELETE(g_pMeshBuffer1);
	SAFE_DELETE(g_pMeshBuffer2);
	SAFE_DELETE(g_pPolygonBuffer1);
	SAFE_DELETE(g_pDissolveBuffer);
}


/**
* @brief	���_�V�F�[�_�[�擾
* @return	Shader* ���_�V�F�[�_�[
*/
Shader* GetVertexShader(EVertexShaderKind kind)
{
	return g_pVertexShaderList[kind];
}


/**
* @brief	�s�N�Z���V�F�[�_�[�擾
* @return	Shader* �s�N�Z���V�F�[�_�[
*/
Shader* GetPixelShader(EPixelShaderKind kind)
{
	return g_pPixelShaderList[kind];
}


void SetAssimpShader(XMFLOAT4X4 world, XMFLOAT4X4 mtxTexture, TAssimpMaterial* pMaterial, XMUINT4 flags,SHADER_BONE bone)
{
	auto pDC = GetDeviceContext();
	auto pCamera = CAMERA->Get(0);
	auto pLight = LIGHT->Get(0);

	// �g�p����V�F�[�_�[�̓o�^
	GetVertexShader(EVertexShaderKind::AssimpVS)->Bind();
	GetPixelShader(EPixelShaderKind::AssimpPS)->Bind();

	// �e�N�X�`���T���v�����Z�b�g
	GRAPHICS->SetSamplerState(CGraphics::SAMPLER_LINEAR);
	
	// �萔�o�b�t�@�X�V
	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&world);
	XMMATRIX mtxView = pCamera->GetLookAtMatrix();
	XMMATRIX mtxProj = pCamera->GetProjectionMatrix();
	XMMATRIX mtxTex = XMLoadFloat4x4(&mtxTexture);
	cb.mWorld = XMMatrixTranspose(mtxWorld);
	cb.mView = XMMatrixTranspose(mtxView);
	cb.mProj = XMMatrixTranspose(mtxProj);
	cb.mTex = XMMatrixTranspose(mtxTex);
	cb.vEye = XMLoadFloat3(&pCamera->GetPos().m_vector);
	cb.vLightDir = XMLoadFloat3(&pLight->GetDirection());
	cb.vLd = XMLoadFloat4(&pLight->GetDiffuse());
	cb.vLa = XMLoadFloat4(&pLight->GetAmbient());
	cb.vLs = XMLoadFloat4(&pLight->GetSpecular());
	g_pAssimpBuffer1->Write(&cb);

	SHADER_MATERIAL cb2;
	cb2.vAmbient = XMLoadFloat4(&pMaterial->Ka);
	cb2.vDiffuse = XMLoadFloat4(&pMaterial->Kd);
	cb2.vSpecular = XMLoadFloat4(&pMaterial->Ks);
	cb2.vEmissive = XMLoadFloat4(&pMaterial->Ke);
	cb2.vFlags = XMLoadUInt4(&flags);
	g_pAssimpBuffer2->Write(&cb2);

	g_pAssimpBone->Write(&bone);

	// �e�N�X�`��
	if (pMaterial->pTexture)
	{
		pDC->PSSetShaderResources(0, 1, &pMaterial->pTexture);
		if (pMaterial->pTexEmmisive)
			pDC->PSSetShaderResources(1, 1, &pMaterial->pTexEmmisive);
		if (pMaterial->pTexTransparent)
			pDC->PSSetShaderResources(2, 1, &pMaterial->pTexTransparent);
		if (pMaterial->pTexSpecular)
			pDC->PSSetShaderResources(3, 1, &pMaterial->pTexSpecular);
	}

	// �萔�o�b�t�@���V�F�[�_�[�X�e�[�W�ɃZ�b�g
	g_pAssimpBuffer1->BindVS(0);
	g_pShadowVPS->BindVS(1);
	g_pAssimpBone->BindVS(2);
	g_pAssimpBuffer1->BindPS(0);
	g_pAssimpBuffer2->BindPS(1);

	// �e�N�X�`���Z�b�g
	SetTexturePS(GRAPHICS->GetShadowTexture()->GetResource(), 4);
}


void SetSimple2DShader(ID3D11ShaderResourceView* texture,XMFLOAT4X4 proj, XMFLOAT4X4 view, XMFLOAT4X4 world, XMFLOAT4X4 tex)
{
	// �g�p����V�F�[�_�[�̓o�^
	GetVertexShader(EVertexShaderKind::Simple2DVS)->Bind();
	GetPixelShader(EPixelShaderKind::Simple2DPS)->Bind();

	// �T���v���[�Z�b�g
	GRAPHICS->SetSamplerState(CGraphics::SAMPLER_POINT);

	// �萔�o�b�t�@�X�V
	SHADER_GLOBAL_POLYGON cb;
	cb.mProj = XMMatrixTranspose(XMLoadFloat4x4(&proj));
	cb.mView = XMMatrixTranspose(XMLoadFloat4x4(&view));
	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&world));
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&tex));
	g_pPolygonBuffer1->Write(&cb);

	// �e�N�X�`��
	SetTexturePS(texture);

	// �V�F�[�_�[�X�e�[�W�ɃZ�b�g
	g_pPolygonBuffer1->BindVS(0);
}


void SetSimpleShader(CMesh* pMesh,XMMATRIX mtxWorld,bool bBillboard)
{
	auto pCamera = CAMERA->Get(0);
	auto pLight = LIGHT->Get(0);
	auto pLight2 = LIGHT->Get(1);

	// �g�p����V�F�[�_�[�̓o�^
	GetVertexShader(EVertexShaderKind::SimpleVS)->Bind();
	GetPixelShader(EPixelShaderKind::SimplePS)->Bind();

	// �T���v���[�Z�b�g
	GRAPHICS->SetSamplerState(CGraphics::SAMPLER_LINEAR);

	// �萔�o�b�t�@�X�V
	SHADER_GLOBAL_MESH cb;
	XMMATRIX mtxView = pCamera->GetLookAtMatrix();
	XMMATRIX mtxProj = pCamera->GetProjectionMatrix();
	cb.mWorld = XMMatrixTranspose(mtxWorld);
	cb.mView = XMMatrixTranspose(mtxView);
	cb.mProj = XMMatrixTranspose(mtxProj);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&pMesh->m_mtxTexture));
	g_pMeshBuffer1->Write(&cb);

	SHADER_GLOBAL2_MESH cb2;
	cb2.vEye = XMLoadFloat3(&pCamera->GetPos().m_vector);
	if (bBillboard)	cb2.vLightDir = XMLoadFloat3(&pLight2->GetDirection());
	else			cb2.vLightDir = XMLoadFloat3(&pLight->GetDirection());
	cb2.vLa = XMLoadFloat4(&pLight->GetAmbient());
	cb2.vLd = XMLoadFloat4(&pLight->GetDiffuse());
	cb2.vLs = XMLoadFloat4(&pLight->GetSpecular());
	cb2.vDiffuse = XMLoadFloat4(&pMesh->m_pMaterial->m_diffuse);
	cb2.vAmbient = XMVectorSet(pMesh->m_pMaterial->m_ambient.x, pMesh->m_pMaterial->m_ambient.y, pMesh->m_pMaterial->m_ambient.z, (pMesh->m_pBaseTexture != nullptr) ? 1.f : 0.f);
	cb2.vSpecular = XMVectorSet(pMesh->m_pMaterial->m_specular.x, pMesh->m_pMaterial->m_specular.y, pMesh->m_pMaterial->m_specular.z, pMesh->m_pMaterial->m_power);
	cb2.vEmissive = XMLoadFloat4(&pMesh->m_pMaterial->m_emissive);
	g_pMeshBuffer2->Write(&cb2);

	// �e�N�X�`��
	SetTexturePS(pMesh->m_pBaseTexture);

	// �V�F�[�_�[�X�e�[�W�ɃZ�b�g
	g_pMeshBuffer1->BindVS(0);
	g_pMeshBuffer2->BindPS(1);
	g_pShadowVPS->BindVS(1);

	// �e�N�X�`���Z�b�g
	SetTexturePS(GRAPHICS->GetShadowTexture()->GetResource(), 1);
}


void SetDepthWrite(XMFLOAT4X4 world,SHADER_BONE bone,Vector3 pos)
{
	auto pDC = GetDeviceContext();
	auto pLightCamera = CAMERA->Get<CLightCamera>();
	XMFLOAT4X4 mat[3];

	// �g�p����V�F�[�_�[�̓o�^
	GetVertexShader(EVertexShaderKind::DepthWriteVS)->Bind();
	GetPixelShader(EPixelShaderKind::DepthWritePS)->Bind();

	// �e�N�X�`���T���v�����Z�b�g
	GRAPHICS->SetSamplerState(CGraphics::SAMPLER_LINEAR);

	// �萔�o�b�t�@�X�V
	g_pAssimpBone->Write(&bone);

	XMStoreFloat4x4(&mat[0], XMMatrixTranspose(XMLoadFloat4x4(&world)));
	XMStoreFloat4x4(&mat[1], XMMatrixTranspose(pLightCamera->GetLookAtMatrix()));
	XMStoreFloat4x4(&mat[2], XMMatrixTranspose(pLightCamera->GetProjectionMatrix()));
	g_pMatrix->Write(mat);

	XMMATRIX screenMat = XMMatrixSet(
		0.5f,  0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 1.0f
	);
	XMFLOAT4X4 vps;
	XMStoreFloat4x4(&vps, XMMatrixTranspose(pLightCamera->GetLookAtMatrix() * pLightCamera->GetProjectionMatrix() * screenMat));
	g_pShadowVPS->Write(&vps);

	// �萔�o�b�t�@���V�F�[�_�[�X�e�[�W�ɃZ�b�g
	g_pMatrix->BindVS(1);
	g_pAssimpBone->BindVS(2);
}


void SetDissolveShader(ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* dissolve, XMFLOAT4X4 proj, XMFLOAT4X4 view, XMFLOAT4X4 world, XMFLOAT4X4 tex)
{
	// �g�p����V�F�[�_�[�̓o�^
	GetVertexShader(EVertexShaderKind::Simple2DVS)->Bind();
	GetPixelShader(EPixelShaderKind::DissolvePS)->Bind();

	// �e�N�X�`���T���v�����Z�b�g
	GRAPHICS->SetSamplerState(CGraphics::SAMPLER_POINT);

	// �萔�o�b�t�@�X�V
	SHADER_GLOBAL_POLYGON cb;
	cb.mProj = XMMatrixTranspose(XMLoadFloat4x4(&proj));
	cb.mView = XMMatrixTranspose(XMLoadFloat4x4(&view));
	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&world));
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&tex));
	g_pPolygonBuffer1->Write(&cb);

	XMFLOAT4 cb2 = XMFLOAT4(0, 0, 0, 0);
	cb2.x = SCENE_MANAGER->GetFadeScript().lock()->GetParam();
	g_pDissolveBuffer->Write(&cb2);

	// �x�[�X�e�N�X�`��
	SetTexturePS(texture);

	// �f�B�]���u�e�N�X�`��
	SetTexturePS(dissolve, 1);

	// �V�F�[�_�[�X�e�[�W�ɃZ�b�g
	g_pPolygonBuffer1->BindVS(0);
	g_pDissolveBuffer->BindPS(0);
}


void SetAssimpTargetShader(XMFLOAT4X4 world, XMFLOAT4X4 mtxTexture, TAssimpMaterial* pMaterial, XMUINT4 flags, SHADER_BONE bone)
{
	auto pDC = GetDeviceContext();
	auto pCamera = CAMERA->Get(0);
	auto pLight = LIGHT->Get(0);

	// �g�p����V�F�[�_�[�̓o�^
	GetVertexShader(EVertexShaderKind::AssimpVS)->Bind();
	GetPixelShader(EPixelShaderKind::AssimpTargetPS)->Bind();

	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_ON);

	// �e�N�X�`���T���v�����Z�b�g
	GRAPHICS->SetSamplerState(CGraphics::SAMPLER_LINEAR);

	// �萔�o�b�t�@�X�V
	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&world);
	XMMATRIX mtxView = pCamera->GetLookAtMatrix();
	XMMATRIX mtxProj = pCamera->GetProjectionMatrix();
	XMMATRIX mtxTex = XMLoadFloat4x4(&mtxTexture);
	cb.mWorld = XMMatrixTranspose(mtxWorld);
	cb.mView = XMMatrixTranspose(mtxView);
	cb.mProj = XMMatrixTranspose(mtxProj);
	cb.mTex = XMMatrixTranspose(mtxTex);
	cb.vEye = XMLoadFloat3(&pCamera->GetPos().m_vector);
	cb.vLightDir = XMLoadFloat3(&pLight->GetDirection());
	cb.vLd = XMLoadFloat4(&pLight->GetDiffuse());
	cb.vLa = XMLoadFloat4(&pLight->GetAmbient());
	cb.vLs = XMLoadFloat4(&pLight->GetSpecular());
	g_pAssimpBuffer1->Write(&cb);

	SHADER_MATERIAL cb2;
	cb2.vAmbient = XMLoadFloat4(&pMaterial->Ka);
	cb2.vDiffuse = XMLoadFloat4(&pMaterial->Kd);
	cb2.vSpecular = XMLoadFloat4(&pMaterial->Ks);
	cb2.vEmissive = XMLoadFloat4(&pMaterial->Ke);
	cb2.vFlags = XMLoadUInt4(&flags);
	g_pAssimpBuffer2->Write(&cb2);

	g_pAssimpBone->Write(&bone);

	// �e�N�X�`��
	if (pMaterial->pTexture)
	{
		pDC->PSSetShaderResources(0, 1, &pMaterial->pTexture);
		if (pMaterial->pTexEmmisive)
			pDC->PSSetShaderResources(1, 1, &pMaterial->pTexEmmisive);
		if (pMaterial->pTexTransparent)
			pDC->PSSetShaderResources(2, 1, &pMaterial->pTexTransparent);
		if (pMaterial->pTexSpecular)
			pDC->PSSetShaderResources(3, 1, &pMaterial->pTexSpecular);
	}

	// �萔�o�b�t�@���V�F�[�_�[�X�e�[�W�ɃZ�b�g
	g_pAssimpBuffer1->BindVS(0);
	g_pShadowVPS->BindVS(1);
	g_pAssimpBone->BindVS(2);
	g_pAssimpBuffer1->BindPS(0);
	g_pAssimpBuffer2->BindPS(1);

	// �e�N�X�`���Z�b�g
	SetTexturePS(GRAPHICS->GetShadowTexture()->GetResource(), 4);
}


void SetMultiTextureShader(ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* dissolve, ID3D11ShaderResourceView* multiTexture, ID3D11ShaderResourceView* multiTexture2, float fParam, XMFLOAT4X4 proj, XMFLOAT4X4 view, XMFLOAT4X4 world, XMFLOAT4X4 tex)
{
	// �g�p����V�F�[�_�[�̓o�^
	GetVertexShader(EVertexShaderKind::Simple2DVS)->Bind();
	GetPixelShader(EPixelShaderKind::MultiTexturePS)->Bind();

	// �e�N�X�`���T���v�����Z�b�g
	GRAPHICS->SetSamplerState(CGraphics::SAMPLER_POINT);

	// �萔�o�b�t�@�X�V
	SHADER_GLOBAL_POLYGON cb;
	cb.mProj = XMMatrixTranspose(XMLoadFloat4x4(&proj));
	cb.mView = XMMatrixTranspose(XMLoadFloat4x4(&view));
	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&world));
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&tex));
	g_pPolygonBuffer1->Write(&cb);

	XMFLOAT4 cb2 = XMFLOAT4(0, 0, 0, 0);
	cb2.x = fParam;
	g_pDissolveBuffer->Write(&cb2);

	// �x�[�X�e�N�X�`��
	SetTexturePS(texture);

	// �f�B�]���u�e�N�X�`��
	SetTexturePS(dissolve, 1);

	// ���荇�킹��e�N�X�`��
	SetTexturePS(multiTexture, 2);
	SetTexturePS(multiTexture2, 3);

	// �V�F�[�_�[�X�e�[�W�ɃZ�b�g
	g_pPolygonBuffer1->BindVS(0);
	g_pDissolveBuffer->BindPS(0);
}
