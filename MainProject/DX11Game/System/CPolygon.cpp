/**
*
* @file		CPolyton.cpp
* @brief	�|���S���N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/CPolygon.h>
#include <System/Graphics/ShaderList.h>
#include <System/Graphics/CGraphics.h>
#include <System/GameObject/CGameObject.h>
#include <System/Graphics/ShaderList.h>

/** �\���̐錾 */

/**
* @brief	�R���X�g���N�^
*/
CPolygon::CPolygon()
	: m_pTexture(nullptr)
	, m_pEffectTexture(nullptr)
	, m_pMultiTexture(nullptr)
	, m_pMultiTexture2(nullptr)
	, m_fParam(0.0f)
	, m_vPos(0.0f, 0.0f, 0.0f)
	, m_vAngle(0.0f, 0.0f, 0.0f)
	, m_vScale(1.0f, 1.0f, 1.0f)
	, m_vColor(1.0f, 1.0f, 1.0f, 1.0f)
	, m_bInvalidate(false)
	, m_vPosTexFrame(0.0f, 0.0f)
	, m_vSizeTexFrame(1.0f, 1.0f)
	, m_pVertexBuffer(nullptr)
{

}


/**
* @brief	�f�X�g���N�^
*/
CPolygon::~CPolygon()
{

}


/**
* @brief	����������
*/
HRESULT CPolygon::Init()
{
	HRESULT hr = S_OK;
	auto pDevice = GetDevice();

	// �ϊ��s�񏉊���
	XMStoreFloat4x4(&m_mWorld, XMMatrixIdentity());
	XMStoreFloat4x4(&m_mView, XMMatrixLookAtLH(XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	XMStoreFloat4x4(&m_mProj,
		XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 100.0f));
	XMStoreFloat4x4(&m_mTex, XMMatrixIdentity());
	m_mTex._44 = 0.0f;

	// ���_���̍쐬
	hr = MakeVertex(pDevice);

	return hr;
}


/**
* @brief	�I������
*/
void CPolygon::Uninit()
{
	// ���_�o�b�t�@�̉��
	SAFE_RELEASE(m_pVertexBuffer);
}


/**
* @brief	�`�揈��
*/
void CPolygon::Draw(ID3D11DeviceContext* pDeviceContext, std::weak_ptr<CGameObject> spObj)
{
	// �g�k
	XMMATRIX mWorld = XMMatrixScaling(m_vScale.x, m_vScale.y, m_vScale.z);
	// ��]
	mWorld *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_vAngle.x),
		XMConvertToRadians(m_vAngle.y), XMConvertToRadians(m_vAngle.z));
	// �ړ�
	mWorld *= XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z);
	// ���[���h �}�g���b�N�X�ɐݒ�
	XMStoreFloat4x4(&m_mWorld, mWorld);

	if (m_pTexture) 
	{
		// �g�k
		mWorld = XMMatrixScaling(m_vSizeTexFrame.x, m_vSizeTexFrame.y, 1.0f);
		// �ړ�
		mWorld *= XMMatrixTranslation(m_vPosTexFrame.x, m_vPosTexFrame.y, 0.0f);
		// �e�N�X�`�� �}�g���b�N�X�ɐݒ�
		XMStoreFloat4x4(&m_mTex, mWorld);
	}
	else {
		// �e�N�X�`������
		m_mTex._44 = 0.0f;
	}

	// ���_�o�b�t�@�X�V
	SetVertex();
	
	const auto& obj = spObj.lock();
	if (obj)
	{
		// �ʏ�`��
		auto psKind = obj->GetPSKind();
		if (psKind == EPixelShaderKind::Simple2DPS)
		{
			SetSimple2DShader(m_pTexture, m_mProj, m_mView, m_mWorld, m_mTex);
		}
		// �f�B�]���u
		else if (psKind == EPixelShaderKind::DissolvePS)
		{
			SetDissolveShader(m_pTexture, m_pEffectTexture, m_mProj, m_mView, m_mWorld, m_mTex);
		}
		// �}���`�e�N�X�`�� + �f�B�]���u
		else if (psKind == EPixelShaderKind::MultiTexturePS)
		{
			SetMultiTextureShader(m_pTexture, m_pEffectTexture, m_pMultiTexture, m_pMultiTexture2, m_fParam, m_mProj, m_mView, m_mWorld, m_mTex);
		}
	}
	else
	{
		SetSimple2DShader(m_pTexture, m_mProj, m_mView, m_mWorld, m_mTex);
	}

	UINT stride = sizeof(VERTEX_2D);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�`����Z�b�g
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���̕`��
	pDeviceContext->Draw(NUM_VERTEX, 0);
}


/**
* @brief	���_�̍쐬
*/
HRESULT CPolygon::MakeVertex(ID3D11Device* pDevice)
{
	// ���_���W�̐ݒ�
	m_vertexWk[0].vtx = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	m_vertexWk[1].vtx = XMFLOAT3(0.5f, 0.5f, 0.0f);
	m_vertexWk[2].vtx = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	m_vertexWk[3].vtx = XMFLOAT3(0.5f, -0.5f, 0.0f);

	// �g�U���ˌ��̐ݒ�
	m_vertexWk[0].diffuse = m_vColor;
	m_vertexWk[1].diffuse = m_vColor;
	m_vertexWk[2].diffuse = m_vColor;
	m_vertexWk[3].diffuse = m_vColor;

	// �e�N�X�`�����W�̐ݒ�
	m_vertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
	m_vertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
	m_vertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
	m_vertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(m_vertexWk);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = &m_vertexWk[0];

	HRESULT hr = pDevice->CreateBuffer(&vbd, &initData, &m_pVertexBuffer);

	return hr;
}


/**
* @brief	���_���W�̐ݒ�
*/
void CPolygon::SetVertex()
{
	if (m_bInvalidate) 
	{
		//���_�o�b�t�@�̒��g�𖄂߂�
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
		HRESULT hr = S_OK;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		hr = pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		if (SUCCEEDED(hr)) {
			// �g�U���ˌ��̐ݒ�
			m_vertexWk[0].diffuse = m_vColor;
			m_vertexWk[1].diffuse = m_vColor;
			m_vertexWk[2].diffuse = m_vColor;
			m_vertexWk[3].diffuse = m_vColor;
			// ���_�f�[�^���㏑��
			memcpy_s(msr.pData, sizeof(m_vertexWk), m_vertexWk, sizeof(m_vertexWk));
			// ���_�f�[�^���A�����b�N����
			pDeviceContext->Unmap(m_pVertexBuffer, 0);
			// �t���O���N���A
			m_bInvalidate = false;
		}
	}
}


/**
* @brief	�e�N�X�`���̐ݒ�
* @param	pTexture	�e�N�X�`��
*/
void CPolygon::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	m_pTexture = pTexture;
	m_mTex._44 = (m_pTexture) ? 1.0f : 0.0f;
}


/**
* @brief	���ʃe�N�X�`���̐ݒ�
* @param	pTexture	�e�N�X�`��
*/
void CPolygon::SetEffectTexture(ID3D11ShaderResourceView* pTexture)
{
	m_pEffectTexture = pTexture;
}


/**
* @brief	�}���`�e�N�X�`���̐ݒ�
* @param	pTexture	�e�N�X�`��
*/
void CPolygon::SetMultiTexture(ID3D11ShaderResourceView* pTexture)
{
	m_pMultiTexture = pTexture;
}


/**
* @brief	�}���`�e�N�X�`���̐ݒ�
* @param	pTexture	�e�N�X�`��
* @param	pTexture2	�e�N�X�`��2
*/
void CPolygon::SetMultiTexture(ID3D11ShaderResourceView* pTexture, ID3D11ShaderResourceView* pTexture2)
{
	m_pMultiTexture = pTexture;
	m_pMultiTexture2 = pTexture2;
}


/**
* @brief	���W�Z�b�g
* @param	fX	X���W
* @param	fY	Y���W
*/
void CPolygon::SetPos(float fX, float fY)
{
	m_vPos.x = fX;
	m_vPos.y = fY;
}


/**
* @brief	�T�C�Y�Z�b�g
* @param	fScaleX		X�T�C�Y
* @param	fScaleY		Y�T�C�Y
*/
void CPolygon::SetSize(float fScaleX, float fScaleY)
{
	m_vScale.x = fScaleX;
	m_vScale.y = fScaleY;
}


/**
* @brief	�p�x�Z�b�g(�P��:�x)
* @param	fAngleZ		Z���p�x
*/
void CPolygon::SetAngle(float fAngleZ)
{
	m_vAngle.z = fAngleZ;
}


/**
* @brief	����e�N�X�`�����W�Z�b�g
* @param	fU	u���W
* @param	fV	v���W
*/
void CPolygon::SetUV(float fU, float fV)
{
	m_vPosTexFrame.x = fU;
	m_vPosTexFrame.y = fV;
}


/**
* @brief	�e�N�X�`���t���[���T�C�Y�Z�b�g
* @param	fWidth		���T�C�Y
* @param	fHeight		�c�T�C�Y
*/
void CPolygon::SetFrameSize(float fWidth, float fHeight)
{
	m_vSizeTexFrame.x = fWidth;
	m_vSizeTexFrame.y = fHeight;
}


/**
* @brief	���_�J���[�̃Z�b�g
* @param	fRed	��
* @param	fGreen	��
* @param	fBlue	��
*/
void CPolygon::SetColor(float fRed, float fGreen, float fBlue)
{
	SetColor(XMFLOAT3(fRed, fGreen, fBlue));
}


/**
* @brief	���_�J���[�̃Z�b�g
* @param	vColor	�F���
*/
void CPolygon::SetColor(XMFLOAT3 vColor)
{
	if (vColor.x != m_vColor.x || vColor.y != m_vColor.y || vColor.z != m_vColor.z) {
		m_vColor.x = vColor.x;
		m_vColor.y = vColor.y;
		m_vColor.z = vColor.z;
		m_bInvalidate = true;
	}
}

/**
* @brief	���_�J���[�̃Z�b�g
* @param	fRed	��
* @param	fGreen	��
* @param	fBlue	��
* @param	fAlpha	�s�����x
*/
void CPolygon::SetColor(float fRed, float fGreen, float fBlue, float fAlpha)
{
	SetColor(XMFLOAT4(fRed, fGreen, fBlue, fAlpha));
}


/**
* @brief	���_�J���[�̃Z�b�g
* @param	vColor	�F���
*/
void CPolygon::SetColor(XMFLOAT4 vColor)
{
	if (vColor.x != m_vColor.x || vColor.y != m_vColor.y || vColor.z != m_vColor.z || vColor.w != m_vColor.w) {
		m_vColor = vColor;
		m_bInvalidate = true;
	}
}


/**
* @brief	�s�����x�̃Z�b�g
* @param	fAlpha	�s�����x
*/
void CPolygon::SetAlpha(float fAlpha)
{
	if (fAlpha != m_vColor.w) {
		m_vColor.w = fAlpha;
		m_bInvalidate = true;
	}
}