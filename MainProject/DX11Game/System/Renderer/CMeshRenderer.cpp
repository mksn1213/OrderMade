/**
*
* @file		CMeshRenderer.cpp
* @brief	���b�V�������_���[�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/05	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Renderer/CMeshRenderer.h>
#include <System/Component/CTransform.h>
#include <Scene/CSceneManager.h>
#include <System/Resource/CTextureManager.h>
#include <System/Graphics/CGraphics.h>
#include <System/Graphics/ShaderList.h>
#include <System/Camera/CCameraManager.h>
#include <System/Systems/CMeshRendererSystem.h>
#include <Scene/CSceneManager.h>

/** �}�N����` */
namespace
{
	const XMFLOAT4	DIFFUSE		= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	const XMFLOAT4	SPECULAR	= XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	const XMFLOAT4	AMBIENT		= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	const XMFLOAT4	EMISSIVE	= XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	const float		POWER		= 1.0f;
}
static const D3D11_PRIMITIVE_TOPOLOGY pt[] = {
	D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,	// 0�Ȃ�O�p�`�X�g���b�v
	D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
	D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
	D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
};

/** �v���g�^�C�v�錾 */
XMFLOAT4 CalcTangent(XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3 v3,
	XMFLOAT2 uv1, XMFLOAT2 uv2, XMFLOAT2 uv3, XMFLOAT3 normal);


/** �ÓI�����o */
CMeshMaterial				CMeshRenderer::m_material;				// �}�e���A��
const EComponentType CMeshRenderer::comID = EComponentType::MeshRenderer;

/**
* @brief	�R���X�g���N�^
*/
CMeshMaterial::CMeshMaterial()
	: m_diffuse(DIFFUSE)
	, m_ambient(AMBIENT)
	, m_specular(SPECULAR)
	, m_emissive(EMISSIVE)
	, m_power(POWER)
{

}

/**
* @brief	�R���X�g���N�^
*/
CMesh::CMesh()
	: m_pVertexBuffer(nullptr)
	, m_pIndexBuffer(nullptr)
	, m_nNumVertex(0)
	, m_nNumIndex(0)
	, m_pBaseTexture(nullptr)
	, m_pNormalTexture(nullptr)
	, m_pMaterial(nullptr)
	, m_ePrimitiveType(PT_TRIANGLESTRIP)
	, m_eTranslucentType(TT_NOAFFECT)
	, m_fAlpha(0.0f)
{
	XMStoreFloat4x4(&m_mtxTexture, XMMatrixIdentity());
}


/**
* @brief	�f�X�g���N�^
*/
CMesh::~CMesh()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	if (m_pMaterial != nullptr)
	{
		delete m_pMaterial;
		m_pMaterial = nullptr;
	}
}


/**
* @brief	�R���X�g���N�^
*/
CMeshRenderer::CMeshRenderer()
	: m_pMesh(nullptr)
	, m_bBillboard(false)
{
	SetID(MeshRenderer);
}


/**
* @brief	�f�X�g���N�^
*/
CMeshRenderer::~CMeshRenderer()
{
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
}


/**
* @brief	������
*/
void CMeshRenderer::OnCreate()
{
	CRenderer::OnCreate();
	// �V�X�e���Ɋi�[
	CMeshRendererSystem* pSystem = SCENE_MANAGER->GetSystem<CMeshRendererSystem>(EComponentType::MeshRenderer);
	if (pSystem != nullptr)	pSystem->AddList(this);
	m_spGameObject.lock()->SetShader(SimpleVS, SimplePS);
}


/**
* @brief	�j����
*/
void CMeshRenderer::OnDestroy()
{
	// �V�X�e�����珜�O
	CMeshRendererSystem* pSystem = SCENE_MANAGER->GetSystem<CMeshRendererSystem>(EComponentType::MeshRenderer);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	�X�V����
*/
void CMeshRenderer::Update()
{
}


/**
* @brief	�`�揈��
*/
void CMeshRenderer::Draw(ID3D11DeviceContext* pDC)
{
	SetBlendState(BS_ALPHABLEND);
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_ON);

	// �r���{�[�h�̏ꍇ�X�V
	if (m_bBillboard)	BillboardUpdateMatrix();

	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_spTransform.lock()->GetWorldMatrix());
	SetSimpleShader(m_pMesh,mtxWorld,m_bBillboard);

	// ���_�E�C���f�b�N�X�o�b�t�@�Z�b�g
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	pDC->IASetVertexBuffers(0, 1, &m_pMesh->m_pVertexBuffer, &stride, &offset);
	pDC->IASetIndexBuffer(m_pMesh->m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// �v���~�e�B�u�`����Z�b�g
	pDC->IASetPrimitiveTopology(pt[m_pMesh->m_ePrimitiveType]);

	// �|���S���̕`��	
	pDC->DrawIndexed(m_pMesh->m_nNumIndex, 0, 0);
}


/**
* @brief	�r���{�[�h�X�V
*/
void CMeshRenderer::BillboardUpdateMatrix()
{
	XMMATRIX mtxWorld, mtxScale, mtxTranslate;

	// �r���[�}�g���b�N�X���擾
	XMFLOAT4X4 mtxView = CAMERA->Get(0)->GetLookAt();

	// ���[���h�ϊ��s��擾
	XMFLOAT4X4 mW = m_spTransform.lock()->GetWorldMatrix();

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();
	XMStoreFloat4x4(&mW, mtxWorld);

	mW._11 = mtxView._11;
	mW._12 = mtxView._21;
	mW._13 = mtxView._31;
	mW._21 = mtxView._12;
	mW._22 = mtxView._22;
	mW._23 = mtxView._32;
	mW._31 = mtxView._13;
	mW._32 = mtxView._23;
	mW._33 = mtxView._33;
	mtxWorld = XMLoadFloat4x4(&mW);

	auto scale = m_spTransform.lock()->GetScale();
	auto pos = m_spTransform.lock()->GetPosition();

	// �X�P�[���𔽉f
	mtxScale = XMMatrixScaling(scale->x, scale->y, 1.0f);
	mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(pos->x, pos->y, pos->z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ���[���h�ϊ��s��Z�b�g
	XMStoreFloat4x4(&mW, mtxWorld);
	m_spTransform.lock()->SetWorld(mW);
}


/**
* @brief	�x�[�X�e�N�X�`���Z�b�g
* @param	texture		�Z�b�g����e�N�X�`���^�C�v
*/
void CMeshRenderer::SetBaseTexture(ETexture type)
{
	m_pMesh->m_pBaseTexture = TEXTURE_MANAGER->GetTexture(type);
}


/**
* @brief	�m�[�}���e�N�X�`���Z�b�g
*/
void CMeshRenderer::SetNormalTexture(const char* filename)
{
	if (m_pMesh != nullptr)
	{
		ID3D11Device* pDevice = GetDevice();
		CreateTextureFromFile(pDevice, filename, &m_pMesh->m_pNormalTexture);
	}
}


/**
* @brief	Plane�̍쐬
*/
HRESULT CMeshRenderer::MakePlane(float texPos)
{
	ID3D11Device* pDevice = GetDevice();

	VERTEX_3D vertexWk[4];	// ���_���i�[���[�N
	int indexWk[4];			// �C���f�b�N�X�i�[���[�N

	// ���b�V������
	m_pMesh = new CMesh();
	m_pMesh->m_pMaterial = new CMeshMaterial();

	// ���_���W�̐ݒ�
	m_pMesh->m_nNumVertex = 4;
	vertexWk[0].vtx = XMFLOAT3(-1.0f, 0.0f, 1.0f);
	vertexWk[1].vtx = XMFLOAT3(1.0f, 0.0f, 1.0f);
	vertexWk[2].vtx = XMFLOAT3(-1.0f, 0.0f, -1.0f);
	vertexWk[3].vtx = XMFLOAT3(1.0f, 0.0f, -1.0f);

	// �@���x�N�g���̐ݒ�
	vertexWk[0].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[1].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[2].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[3].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);

	// �g�U���ˌ��̐ݒ�
	vertexWk[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
	vertexWk[1].tex = XMFLOAT2(texPos, 0.0f);
	vertexWk[2].tex = XMFLOAT2(0.0f, texPos);
	vertexWk[3].tex = XMFLOAT2(texPos, texPos);
	
	// �ڐ����v�Z
	XMFLOAT4 vTangent = CalcTangent(
		vertexWk[0].vtx, vertexWk[1].vtx, vertexWk[2].vtx, 
		vertexWk[0].tex, vertexWk[1].tex, vertexWk[2].tex, 
		vertexWk[0].nor);

	vertexWk[0].vTanget = vTangent;
	vertexWk[1].vTanget = vTangent;
	vertexWk[2].vTanget = vTangent;
	vertexWk[3].vTanget = vTangent;

	// �C���f�b�N�X�z��̐ݒ�
	m_pMesh->m_nNumIndex = 4;
	indexWk[0] = 0;
	indexWk[1] = 1;
	indexWk[2] = 2;
	indexWk[3] = 3;

	// ���_���̍쐬
	HRESULT hr = MakeMeshVertex(pDevice, vertexWk, indexWk);
	return hr;
}


/**
* @brief	Billboard�̍쐬
*/
HRESULT CMeshRenderer::MakeBillboard()
{
	m_bBillboard = true;

	ID3D11Device* pDevice = GetDevice();

	VERTEX_3D vertexWk[4];	// ���_���i�[���[�N
	int indexWk[4];			// �C���f�b�N�X�i�[���[�N

	// ���b�V������
	m_pMesh = new CMesh();
	m_pMesh->m_pMaterial = new CMeshMaterial();

	// ���_���W�̐ݒ�
	m_pMesh->m_nNumVertex = 4;
	vertexWk[0].vtx = XMFLOAT3(-1.0f,  1.0f, 0.0f);
	vertexWk[1].vtx = XMFLOAT3( 1.0f,  1.0f, 0.0f);
	vertexWk[2].vtx = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertexWk[3].vtx = XMFLOAT3( 1.0f, -1.0f, 0.0f);

	// �@���x�N�g���̐ݒ�
	vertexWk[0].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[1].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[2].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[3].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);

	// �g�U���ˌ��̐ݒ�
	vertexWk[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexWk[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
	vertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
	vertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
	vertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);

	// �C���f�b�N�X�z��̐ݒ�
	m_pMesh->m_nNumIndex = 4;
	indexWk[0] = 0;
	indexWk[1] = 1;
	indexWk[2] = 2;
	indexWk[3] = 3;

	// ���_���̍쐬
	HRESULT hr = MakeMeshVertex(pDevice, vertexWk, indexWk);
	return hr;
}


/**
* @brief	Box�̍쐬
* @param	size	�{�b�N�X�T�C�Y
* @param	center	���S
*/
HRESULT CMeshRenderer::MakeBox(Vector3 size, Vector3 center)
{
	ID3D11Device* pDevice = GetDevice();

	HRESULT hr = S_OK;
	const static float vtx[] = {
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
	};
	const static float nor[] = {
		 0.0f,  0.0f, -1.0f,
		 1.0f,  0.0f,  0.0f,
		 0.0f,  0.0f,  1.0f,
		-1.0f,  0.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
	};
	const static int face[] = {
		4, 0, 5, 1, 5, 0,
		5, 1, 7, 3, 7, 1,
		7, 3, 6, 2, 6, 3,
		6, 2, 4, 0, 4, 2,
		0, 2, 1, 3, 1, 2,
		6, 4, 7, 5, 7, 4,
	};
	const static float uv[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	// ���b�V������
	m_pMesh = new CMesh();
	m_pMesh->m_pMaterial = new CMeshMaterial();

	// ���_���W�̐ݒ�
	m_pMesh->m_nNumVertex = 24;
	m_pMesh->m_nNumIndex = 36;
	size /= 2;

	VERTEX_3D* pVertexWk = new VERTEX_3D[24];
	int* pIndexWk = new int[36];
	VERTEX_3D* pVtx = pVertexWk;
	int nIdx = 0;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 4; ++j) {
			pVtx->vtx.x = vtx[face[i * 6 + j] * 3 + 0] * size->x + center->x;
			pVtx->vtx.y = vtx[face[i * 6 + j] * 3 + 1] * size->y + center->y;
			pVtx->vtx.z = vtx[face[i * 6 + j] * 3 + 2] * size->z + center->z;
			pVtx->nor.x = nor[i * 3 + 0];
			pVtx->nor.y = nor[i * 3 + 1];
			pVtx->nor.z = nor[i * 3 + 2];
			pVtx->tex.x = uv[j * 2 + 0];
			pVtx->tex.y = uv[j * 2 + 1];
			pVtx->diffuse = XMFLOAT4(1, 1, 1, 1);
			++pVtx;
			pIndexWk[i * 6 + j] = nIdx;
			++nIdx;
		}
		pIndexWk[i * 6 + 4] = pIndexWk[i * 6 + 2];
		pIndexWk[i * 6 + 5] = pIndexWk[i * 6 + 1];
	}
	hr = MakeMeshVertex(pDevice, pVertexWk, pIndexWk);

	delete[] pIndexWk;
	delete[] pVertexWk;
	return hr;
}


/**
* @brief	Sphere�̍쐬
* @param	size	���̃T�C�Y
* @detail	x:���a	y:sline  z:stack
* @param	center	���S
*/
HRESULT CMeshRenderer::MakeSphere(Vector3 size, Vector3 center)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();

	// ���b�V������
	m_pMesh = new CMesh();
	m_pMesh->m_pMaterial = new CMeshMaterial();

	int nVertex = (size->y + 1) * (size->z + 1);
	m_pMesh->m_nNumVertex = nVertex;
	VERTEX_3D* pVertexWk = new VERTEX_3D[nVertex];
	// ���_�A�@���x�N�g���A�e�N�X�`�����W�̈ʒu
	VERTEX_3D* pVtx = pVertexWk;
	for (int j = 0; j <= size->z; ++j) {
		float v = (float)j / (float)size->z;
		float ph = XM_PI * v;
		float y = cosf(ph);
		float r = sinf(ph);
		for (int i = 0; i <= size->y; ++i) {
			float u = (float)i / (float)size->y;
			float th = XM_2PI * u;
			float x = r * cosf(th);
			float z = r * sinf(th);
			pVtx->vtx.x = x * size->x + center->x;
			pVtx->vtx.y = y * size->x + center->y;
			pVtx->vtx.z = z * size->x + center->z;
			pVtx->nor.x = x;
			pVtx->nor.y = y;
			pVtx->nor.z = z;
			pVtx->tex.x = u;
			pVtx->tex.y = v;
			pVtx->diffuse = XMFLOAT4(1, 1, 1, 1);
			++pVtx;
		}
	}
	// �ʂ̃C���f�b�N�X
	int nFace = size->y * size->z * 2;
	int* pIndexWk = new int[nFace * 3];
	int* pIdx = pIndexWk;
	m_pMesh->m_nNumIndex = nFace * 3;
	for (int j = 0; j < size->z; ++j) {
		for (int i = 0; i < size->y; ++i) {
			int nIndex = (size->y + 1) * j + i;
			// ��������
			*pIdx++ = nIndex + (size->y + 1);
			*pIdx++ = nIndex;
			*pIdx++ = nIndex + (size->y + 1) + 1;
			// �E�㔼��
			*pIdx++ = nIndex + 1;
			*pIdx++ = nIndex + (size->y + 1) + 1;
			*pIdx++ = nIndex;
		}
	}
	hr = MakeMeshVertex(pDevice, pVertexWk, pIndexWk);

	delete[] pIndexWk;
	delete[] pVertexWk;
	return hr;
}


/**
* @brief	���b�V��������
* @return	HRESULT		�����̐���
*/
HRESULT CMeshRenderer::InitMesh()
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr = S_OK;

	// �}�e���A���̏����ݒ�
	m_material.m_diffuse = DIFFUSE;
	m_material.m_ambient = AMBIENT;
	m_material.m_specular = SPECULAR;
	m_material.m_emissive = EMISSIVE;
	m_material.m_power = POWER;

	return hr;
}


/**
* @brief	���b�V���I��
*/
void CMeshRenderer::UninitMesh()
{
}


/**
* @brief	���_�쐬
* @param	pDevice		�f�o�C�X
* @param	vertexWk[]	���_���
* @param	indexWk[]	�z����
* @return	HRESULT		�����̐���
*/
HRESULT CMeshRenderer::MakeMeshVertex(ID3D11Device* pDevice, VERTEX_3D vertexWk[], int indexWk[])
{
	m_pMesh->m_fAlpha = 1.0f;
	for (int i = 0; i < m_pMesh->m_nNumVertex; ++i) {
		if (m_pMesh->m_fAlpha > vertexWk[i].diffuse.w) {
			m_pMesh->m_fAlpha = vertexWk[i].diffuse.w;
		}
	}

	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(VERTEX_3D) * m_pMesh->m_nNumVertex;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertexWk;
	HRESULT hr = pDevice->CreateBuffer(&vbd, &initData, &m_pMesh->m_pVertexBuffer);
	if (FAILED(hr)) {
		return hr;
	}

	CD3D11_BUFFER_DESC ibd(m_pMesh->m_nNumIndex * sizeof(int), D3D11_BIND_INDEX_BUFFER);
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = indexWk;
	hr = pDevice->CreateBuffer(&ibd, &initData, &m_pMesh->m_pIndexBuffer);

	return hr;
}


XMFLOAT4 CalcTangent(XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3 v3,
	XMFLOAT2 uv1, XMFLOAT2 uv2, XMFLOAT2 uv3, XMFLOAT3 normal)
{
	XMFLOAT3 tangent;
	XMFLOAT3 bitangent;

	XMFLOAT3 edge1 = XMFLOAT3(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
	XMFLOAT3 edge2 = XMFLOAT3(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
	XMFLOAT3 edge1v;
	XMStoreFloat3(&edge1v, XMVector3Normalize(XMLoadFloat3(&edge1)));
	XMFLOAT3 edge2v;
	XMStoreFloat3(&edge2v, XMVector3Normalize(XMLoadFloat3(&edge2)));

	XMFLOAT2 uvEdge1 = XMFLOAT2(uv2.x - uv1.x, uv2.y - uv1.y);
	XMFLOAT2 uvEdge2 = XMFLOAT2(uv3.x - uv1.x, uv3.y - uv1.y);
	XMFLOAT2 uvEdge1v;
	XMStoreFloat2(&uvEdge1v, XMVector2Normalize(XMLoadFloat2(&uvEdge1)));
	XMFLOAT2 uvEdge2v;
	XMStoreFloat2(&uvEdge2v, XMVector2Normalize(XMLoadFloat2(&uvEdge2)));

	float det = (uvEdge1v.x*uvEdge2v.y) - (uvEdge1v.y*uvEdge2v.x);
	det = 1.0f / det;

	tangent.x = (uvEdge2v.y*edge1v.x - uvEdge1v.y*edge2v.x)*det;
	tangent.y = (uvEdge2v.y*edge1v.y - uvEdge1v.y*edge2v.y)*det;
	tangent.z = (uvEdge2v.y*edge1v.z - uvEdge1v.y*edge2v.z)*det;

	bitangent.x = (-uvEdge2v.x*edge1v.x + uvEdge1v.x*edge2v.x)*det;
	bitangent.y = (-uvEdge2v.x*edge1v.y + uvEdge1v.x*edge2v.y)*det;
	bitangent.z = (-uvEdge2v.x*edge1v.z + uvEdge1v.x*edge2v.z)*det;

	XMFLOAT3 tangentV;
	XMStoreFloat3(&tangentV, XMVector3Normalize(XMLoadFloat3(&tangent)));
	XMFLOAT3 bitangentV;
	XMStoreFloat3(&bitangentV, XMVector3Normalize(XMLoadFloat3(&bitangent)));

	XMFLOAT3 BiNormal;
	XMStoreFloat3(&BiNormal, XMVector3Cross(XMLoadFloat3(&normal), XMLoadFloat3(&tangentV)));

	XMVECTOR BiNormalV = XMLoadFloat3(&BiNormal);
	XMVECTOR bitangentVV = XMLoadFloat3(&bitangentV);
	XMVECTOR dotV = XMVector3Dot(BiNormalV, bitangentVV);
	XMFLOAT3 dot;
	XMStoreFloat3(&dot, dotV);
	
	float w = (dot.x >= 0.0f) ? 1.0f : -1.0f;

	return XMFLOAT4(tangent.x, tangent.y, tangent.z, w);
}