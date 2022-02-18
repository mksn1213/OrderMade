/**
*
* @file		CGraphics.cpp
* @brief	�O���t�B�b�N�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/15	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Graphics/CGraphics.h>
#include <System/Defines.h>
#include <System/Texture/TextureFactory.h>
#include <System/Texture/CRenderTarget.h>
#include <System/Texture/CDepthStencil.h>

/** �O���[�o���ϐ� */
ID3D11Device*			 g_pDevice;
ID3D11DeviceContext*	 g_pDeviceContext;
IDXGISwapChain*			 g_pSwapChain;

ID3D11BlendState*		 g_pBlendState[MAX_BLENDSTATE];
ID3D11RasterizerState*	 g_pRasterizer[MAX_CULLMODE];

/**
* @brief	����������
*/
HRESULT InitDX(HWND hWnd, bool bWindow)
{
	HRESULT hr = S_OK;

	// �X���b�v�`�F�C���̍쐬
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Width = SCREEN_WIDTH;
	scd.BufferDesc.Height = SCREEN_HEIGHT;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = bWindow;

	// �h���C�o�̎��
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// GPU�ŕ`��
		D3D_DRIVER_TYPE_WARP,		// �����x(�ᑬ
		D3D_DRIVER_TYPE_REFERENCE,	// CPU�ŕ`��
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);
	UINT createDeviceFlags = 0;

	// �@�\���x��
	D3D_FEATURE_LEVEL featureLevels[] = {
	D3D_FEATURE_LEVEL_11_1,
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0,
	D3D_FEATURE_LEVEL_9_3,
	D3D_FEATURE_LEVEL_9_2,
	D3D_FEATURE_LEVEL_9_1,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,					// �f�B�X�v���C�f�o�C�X�̃A�_�v�^�iNULL�̏ꍇ�ŏ��Ɍ��������A�_�v�^�j
			driverType,				// �f�o�C�X�h���C�o�̃^�C�v
			NULL,					// �\�t�g�E�F�A���X�^���C�U���g�p����ꍇ�Ɏw�肷��
			createDeviceFlags,		// �f�o�C�X�t���O
			featureLevels,			// �@�\���x��
			numFeatureLevels,		// �@�\���x����
			D3D11_SDK_VERSION,		// 
			&scd,					// �X���b�v�`�F�C���̐ݒ�
			&g_pSwapChain,			// IDXGIDwapChain�C���^�t�F�[�X	
			&g_pDevice,				// ID3D11Device�C���^�t�F�[�X
			&featureLevel,			// �T�|�[�g����Ă���@�\���x��
			&g_pDeviceContext);		// �f�o�C�X�R���e�L�X�g
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		return hr;
	}

	// ���X�^���C�Y�ݒ�
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;	// �J�����O����(���ʕ`��)
	g_pDevice->CreateRasterizerState(&rd, &g_pRasterizer[0]);
	rd.CullMode = D3D11_CULL_FRONT;	// �O�ʃJ�����O(���ʕ`��)
	g_pDevice->CreateRasterizerState(&rd, &g_pRasterizer[1]);
	rd.CullMode = D3D11_CULL_BACK;	// �w�ʃJ�����O(�\�ʕ`��)
	g_pDevice->CreateRasterizerState(&rd, &g_pRasterizer[2]);
	g_pDeviceContext->RSSetState(g_pRasterizer[2]);
	SetCullMode(CULL_NONE);

	// �u�����h �X�e�[�g����
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[0]);
	// �u�����h �X�e�[�g���� (�A���t�@ �u�����h�p)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[1]);
	// �u�����h �X�e�[�g���� (���Z�����p)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[2]);
	// �u�����h �X�e�[�g���� (���Z�����p)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[3]);
	SetBlendState(BS_ALPHABLEND);

	return hr;
}


/**
* @brief	�I������
*/
void UninitDX()
{
	// �u�����h�X�e�[�g���
	for (int i = 0; i < MAX_BLENDSTATE; ++i)
	{
		SAFE_RELEASE(g_pBlendState[i]);
	}

	// ���X�^���C�U�X�e�[�g���
	for (int i = 0; i < MAX_CULLMODE; ++i)
	{
		SAFE_RELEASE(g_pRasterizer[i]);
	}

	// �X���b�v�`�F�[�����
	SAFE_RELEASE(g_pSwapChain);

	// �f�o�C�X�R���e�L�X�g�̉��
	SAFE_RELEASE(g_pDeviceContext);

	// �f�o�C�X�̉��
	SAFE_RELEASE(g_pDevice);
	
}


/**
* @brief	����������
*/
HRESULT CGraphics::Init()
{
	HRESULT hr;

	// �����_�[�^�[�Q�b�g
	m_pDefRenderTarget = TextureFactory::CreateRenderTargetFromScreen();
	UINT width  = m_pDefRenderTarget->GetWidth();
	UINT height = m_pDefRenderTarget->GetHeight();
	m_pDefDepthStencil = TextureFactory::CreateDepthStencil(width, height, false);

	// �T���v���[������
	m_pDefSamplerState[SAMPLER_POINT] = new CSamplerState;
	m_pDefSamplerState[SAMPLER_POINT]->Create(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);
	m_pDefSamplerState[SAMPLER_LINEAR] = new CSamplerState;
	m_pDefSamplerState[SAMPLER_LINEAR]->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);

	// �f�v�X�X�e���V��������
	m_pDefDepthStencilState[DEPTHSTENCIL_OFF] = new CDepthStencilState;
	m_pDefDepthStencilState[DEPTHSTENCIL_OFF]->Create(false, false);
	m_pDefDepthStencilState[DEPTHSTENCIL_ON] = new CDepthStencilState;
	m_pDefDepthStencilState[DEPTHSTENCIL_ON]->Create(true, false);

	// �����l�ݒ�
	m_pDepthStencilView = m_pDefDepthStencil;
	SetRenderTargetDefault();
	SetDepthStencilViewDefault();
	SetSamplerState(SAMPLER_LINEAR);
	SetDepthStencilState(DEPTHSTENCIL_ON);

	// �V���h�[�}�b�v�p�����_�[�^�[�Q�b�g
	m_pShadowRenderTarget = TextureFactory::CreateRenderTarget(DXGI_FORMAT_R32_FLOAT, 1024, 1024);
	m_pShadowDepthStencil = TextureFactory::CreateDepthStencil(1024, 1024);

	return S_OK;
}


/**
* @brief	�I������
*/
void CGraphics::Uninit()
{
	SAFE_DELETE(m_pShadowRenderTarget);
	SAFE_DELETE(m_pShadowDepthStencil);
	SAFE_DELETE(m_pDefDepthStencilState[DEPTHSTENCIL_OFF]);
	SAFE_DELETE(m_pDefDepthStencilState[DEPTHSTENCIL_ON]);
	SAFE_DELETE(m_pDefSamplerState[SAMPLER_LINEAR]);
	SAFE_DELETE(m_pDefSamplerState[SAMPLER_POINT]);
	SAFE_DELETE(m_pDefDepthStencil);
	SAFE_DELETE(m_pDefRenderTarget);
}


/**
* @brief	�����`��
*/
void CGraphics::BeginDraw()
{
	float color[4] = { 0.117647f, 0.254902f, 0.352941f, 1.0f };
	ID3D11RenderTargetView* pRTV = reinterpret_cast<CRenderTarget*>(m_pDefRenderTarget)->GetView();
	ID3D11DepthStencilView* pDSV = reinterpret_cast<CDepthStencil*>(m_pDefDepthStencil)->GetView();
	g_pDeviceContext->ClearRenderTargetView(pRTV, color);
	g_pDeviceContext->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	SetDepthStencilState(DEPTHSTENCIL_ON);
	SetBlendState(BS_NONE);
}


/**
* @brief	�o�b�N�ƃt�����g�̓���ւ�
*/
void CGraphics::EndDraw()
{
	g_pSwapChain->Present(0, 0);
}


/**
* @brief	�����_�[�^�[�Q�b�g�Z�b�g
*/
void CGraphics::SetRenderTarget(CTexture** ppRenderTarget, UINT nNumView, float* pClearColor)
{
	// �X�V�`�F�b�N
	if (!ppRenderTarget || !ppRenderTarget[0])
	{
		return;
	}

	// �����_�[�^�[�Q�b�g�X�V
	m_renderTargetNum = min(nNumView, 4);
	for (UINT i = 0; i < m_renderTargetNum; ++i)
	{
		m_pRenderTarget[i] = ppRenderTarget[i];
	}
	UpdateTargetView();

	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = static_cast<FLOAT>(m_pRenderTarget[0]->GetWidth());
	vp.Height = static_cast<FLOAT>(m_pRenderTarget[0]->GetHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	g_pDeviceContext->RSSetViewports(1, &vp);

	// �N���A
	if (pClearColor)
	{
		for (UINT i = 0; i < m_renderTargetNum; ++i)
		{
			ID3D11RenderTargetView* pRTV = reinterpret_cast<CRenderTarget*>(m_pRenderTarget[i])->GetView();
			g_pDeviceContext->ClearRenderTargetView(pRTV, pClearColor);
		}
	}
}


/**
* @brief	�f�t�H���g�����_�[�^�[�Q�b�g�Z�b�g
*/
void CGraphics::SetRenderTargetDefault(float* pClearColor)
{
	SetRenderTarget(&m_pDefRenderTarget, 1, pClearColor);
}


/**
* @brief	�V���h�[�}�b�v�p�����_�[�^�[�Q�b�g�Z�b�g
*/
void CGraphics::SetShadowRenderTarget(float* pClearColor)
{
	SetRenderTarget(&m_pShadowRenderTarget, 1, pClearColor);
}


/**
* @brief	�[�x�X�e���V���r���[�Z�b�g
*/
void CGraphics::SetDepthStencilView(CTexture* pDepthStencilView, bool isClear)
{
	// �X�V�`�F�b�N
	if (!pDepthStencilView || m_pDepthStencilView == pDepthStencilView)
	{
		return;
	}

	// �[�x�o�b�t�@�ݒ�
	m_pDepthStencilView = pDepthStencilView;
	UpdateTargetView();

	// �o�b�t�@�N���A
	if (isClear)
	{
		CDepthStencil* pDSV = reinterpret_cast<CDepthStencil*>(m_pDepthStencilView);
		g_pDeviceContext->ClearDepthStencilView(
			pDSV->GetView(),
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f,
			0);
	}
}


/**
* @brief	�[�x�X�e���V���r���[�f�t�H���g�ݒ�Z�b�g
*/
void CGraphics::SetDepthStencilViewDefault(bool isClear)
{
	SetDepthStencilView(m_pDefDepthStencil, isClear);
}


/**
* @brief	�V���h�[�}�b�v�p�[�x�X�e���V���r���[�f�t�H���g�ݒ�Z�b�g
*/
void CGraphics::SetShadowDepthStencilView(bool isClear)
{
	SetDepthStencilView(m_pShadowDepthStencil, isClear);
}


/**
* @brief	�T���v���[�X�e�[�g�Z�b�g
*/
void CGraphics::SetSamplerState(ESamplerStateKind kind)
{
	m_pDefSamplerState[kind]->Bind();
}


/**
* @brief	�T���v���[�X�e�[�g�Z�b�g
*/
void CGraphics::SetSamplerState(CSamplerState* pState)
{
	m_pSamplerState = pState;
}


/**
* @brief	�T���v���[�X�e�[�g�擾
*/
CSamplerState* CGraphics::GetSamplerState()
{
	return m_pSamplerState;
}


/**
* @brief	�[�x�X�e���V���X�e�[�g�Z�b�g
*/
void CGraphics::SetDepthStencilState(EDepthStencilKind kind)
{
	m_pDefDepthStencilState[kind]->Bind();
}


/**
* @brief	�[�x�X�e���V���r���[�Z�b�g
*/
void CGraphics::SetDepthStencilState(CDepthStencilState* pState)
{
	m_pDepthStencilState = pState;
}


/**
* @brief	�^�[�Q�b�g�r���[�X�V
*/
void CGraphics::UpdateTargetView()
{
	// �����_�[�^�[�Q�b�g�擾
	ID3D11RenderTargetView* pRTV[4] = {};
	for (UINT i = 0; i < m_renderTargetNum&&i < 4; ++i)
	{
		pRTV[i] = reinterpret_cast<CRenderTarget*>(m_pRenderTarget[i])->GetView();
	}
	// �[�x�X�e���V���擾
	CDepthStencil* pDSV = reinterpret_cast<CDepthStencil*>(m_pDepthStencilView);
	// �ݒ�
	g_pDeviceContext->OMSetRenderTargets(m_renderTargetNum, pRTV, pDSV->GetView());
}



/**
* @brief	�u�����h�X�e�[�g�Z�b�g
*/
void SetBlendState(EBlendState blend)
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	g_pDeviceContext->OMSetBlendState(g_pBlendState[blend], blendFactor, 0xffffffff);
}


/**
* @brief	�J�����O���[�h�Z�b�g
*/
void SetCullMode(ECullMode cull)
{
	g_pDeviceContext->RSSetState(g_pRasterizer[cull]);
}


/**
* @brief	�f�o�C�X�擾
*/
ID3D11Device* GetDevice()
{
	return g_pDevice;
}


/**
* @brief	�f�o�C�X�R���e�L�X�g�擾
*/
ID3D11DeviceContext* GetDeviceContext()
{
	return g_pDeviceContext;
}


/**
* @brief	�X���b�v�`�F�C���擾
*/
IDXGISwapChain* GetSwapChain()
{
	return g_pSwapChain;
}

