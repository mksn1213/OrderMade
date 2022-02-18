/**
*
* @file		CGraphics.cpp
* @brief	グラフィッククラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/15	実装開始
*
*/

/** インクルード部 */
#include <System/Graphics/CGraphics.h>
#include <System/Defines.h>
#include <System/Texture/TextureFactory.h>
#include <System/Texture/CRenderTarget.h>
#include <System/Texture/CDepthStencil.h>

/** グローバル変数 */
ID3D11Device*			 g_pDevice;
ID3D11DeviceContext*	 g_pDeviceContext;
IDXGISwapChain*			 g_pSwapChain;

ID3D11BlendState*		 g_pBlendState[MAX_BLENDSTATE];
ID3D11RasterizerState*	 g_pRasterizer[MAX_CULLMODE];

/**
* @brief	初期化処理
*/
HRESULT InitDX(HWND hWnd, bool bWindow)
{
	HRESULT hr = S_OK;

	// スワップチェインの作成
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

	// ドライバの種類
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// GPUで描画
		D3D_DRIVER_TYPE_WARP,		// 高精度(低速
		D3D_DRIVER_TYPE_REFERENCE,	// CPUで描画
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);
	UINT createDeviceFlags = 0;

	// 機能レベル
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
			NULL,					// ディスプレイデバイスのアダプタ（NULLの場合最初に見つかったアダプタ）
			driverType,				// デバイスドライバのタイプ
			NULL,					// ソフトウェアラスタライザを使用する場合に指定する
			createDeviceFlags,		// デバイスフラグ
			featureLevels,			// 機能レベル
			numFeatureLevels,		// 機能レベル数
			D3D11_SDK_VERSION,		// 
			&scd,					// スワップチェインの設定
			&g_pSwapChain,			// IDXGIDwapChainインタフェース	
			&g_pDevice,				// ID3D11Deviceインタフェース
			&featureLevel,			// サポートされている機能レベル
			&g_pDeviceContext);		// デバイスコンテキスト
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		return hr;
	}

	// ラスタライズ設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;	// カリング無し(両面描画)
	g_pDevice->CreateRasterizerState(&rd, &g_pRasterizer[0]);
	rd.CullMode = D3D11_CULL_FRONT;	// 前面カリング(裏面描画)
	g_pDevice->CreateRasterizerState(&rd, &g_pRasterizer[1]);
	rd.CullMode = D3D11_CULL_BACK;	// 背面カリング(表面描画)
	g_pDevice->CreateRasterizerState(&rd, &g_pRasterizer[2]);
	g_pDeviceContext->RSSetState(g_pRasterizer[2]);
	SetCullMode(CULL_NONE);

	// ブレンド ステート生成
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
	// ブレンド ステート生成 (アルファ ブレンド用)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[1]);
	// ブレンド ステート生成 (加算合成用)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[2]);
	// ブレンド ステート生成 (減算合成用)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	g_pDevice->CreateBlendState(&BlendDesc, &g_pBlendState[3]);
	SetBlendState(BS_ALPHABLEND);

	return hr;
}


/**
* @brief	終了処理
*/
void UninitDX()
{
	// ブレンドステート解放
	for (int i = 0; i < MAX_BLENDSTATE; ++i)
	{
		SAFE_RELEASE(g_pBlendState[i]);
	}

	// ラスタライザステート解放
	for (int i = 0; i < MAX_CULLMODE; ++i)
	{
		SAFE_RELEASE(g_pRasterizer[i]);
	}

	// スワップチェーン解放
	SAFE_RELEASE(g_pSwapChain);

	// デバイスコンテキストの解放
	SAFE_RELEASE(g_pDeviceContext);

	// デバイスの解放
	SAFE_RELEASE(g_pDevice);
	
}


/**
* @brief	初期化処理
*/
HRESULT CGraphics::Init()
{
	HRESULT hr;

	// レンダーターゲット
	m_pDefRenderTarget = TextureFactory::CreateRenderTargetFromScreen();
	UINT width  = m_pDefRenderTarget->GetWidth();
	UINT height = m_pDefRenderTarget->GetHeight();
	m_pDefDepthStencil = TextureFactory::CreateDepthStencil(width, height, false);

	// サンプラー初期化
	m_pDefSamplerState[SAMPLER_POINT] = new CSamplerState;
	m_pDefSamplerState[SAMPLER_POINT]->Create(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);
	m_pDefSamplerState[SAMPLER_LINEAR] = new CSamplerState;
	m_pDefSamplerState[SAMPLER_LINEAR]->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);

	// デプスステンシル初期化
	m_pDefDepthStencilState[DEPTHSTENCIL_OFF] = new CDepthStencilState;
	m_pDefDepthStencilState[DEPTHSTENCIL_OFF]->Create(false, false);
	m_pDefDepthStencilState[DEPTHSTENCIL_ON] = new CDepthStencilState;
	m_pDefDepthStencilState[DEPTHSTENCIL_ON]->Create(true, false);

	// 初期値設定
	m_pDepthStencilView = m_pDefDepthStencil;
	SetRenderTargetDefault();
	SetDepthStencilViewDefault();
	SetSamplerState(SAMPLER_LINEAR);
	SetDepthStencilState(DEPTHSTENCIL_ON);

	// シャドーマップ用レンダーターゲット
	m_pShadowRenderTarget = TextureFactory::CreateRenderTarget(DXGI_FORMAT_R32_FLOAT, 1024, 1024);
	m_pShadowDepthStencil = TextureFactory::CreateDepthStencil(1024, 1024);

	return S_OK;
}


/**
* @brief	終了処理
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
* @brief	初期描画
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
* @brief	バックとフロントの入れ替え
*/
void CGraphics::EndDraw()
{
	g_pSwapChain->Present(0, 0);
}


/**
* @brief	レンダーターゲットセット
*/
void CGraphics::SetRenderTarget(CTexture** ppRenderTarget, UINT nNumView, float* pClearColor)
{
	// 更新チェック
	if (!ppRenderTarget || !ppRenderTarget[0])
	{
		return;
	}

	// レンダーターゲット更新
	m_renderTargetNum = min(nNumView, 4);
	for (UINT i = 0; i < m_renderTargetNum; ++i)
	{
		m_pRenderTarget[i] = ppRenderTarget[i];
	}
	UpdateTargetView();

	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = static_cast<FLOAT>(m_pRenderTarget[0]->GetWidth());
	vp.Height = static_cast<FLOAT>(m_pRenderTarget[0]->GetHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	g_pDeviceContext->RSSetViewports(1, &vp);

	// クリア
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
* @brief	デフォルトレンダーターゲットセット
*/
void CGraphics::SetRenderTargetDefault(float* pClearColor)
{
	SetRenderTarget(&m_pDefRenderTarget, 1, pClearColor);
}


/**
* @brief	シャドーマップ用レンダーターゲットセット
*/
void CGraphics::SetShadowRenderTarget(float* pClearColor)
{
	SetRenderTarget(&m_pShadowRenderTarget, 1, pClearColor);
}


/**
* @brief	深度ステンシルビューセット
*/
void CGraphics::SetDepthStencilView(CTexture* pDepthStencilView, bool isClear)
{
	// 更新チェック
	if (!pDepthStencilView || m_pDepthStencilView == pDepthStencilView)
	{
		return;
	}

	// 深度バッファ設定
	m_pDepthStencilView = pDepthStencilView;
	UpdateTargetView();

	// バッファクリア
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
* @brief	深度ステンシルビューデフォルト設定セット
*/
void CGraphics::SetDepthStencilViewDefault(bool isClear)
{
	SetDepthStencilView(m_pDefDepthStencil, isClear);
}


/**
* @brief	シャドーマップ用深度ステンシルビューデフォルト設定セット
*/
void CGraphics::SetShadowDepthStencilView(bool isClear)
{
	SetDepthStencilView(m_pShadowDepthStencil, isClear);
}


/**
* @brief	サンプラーステートセット
*/
void CGraphics::SetSamplerState(ESamplerStateKind kind)
{
	m_pDefSamplerState[kind]->Bind();
}


/**
* @brief	サンプラーステートセット
*/
void CGraphics::SetSamplerState(CSamplerState* pState)
{
	m_pSamplerState = pState;
}


/**
* @brief	サンプラーステート取得
*/
CSamplerState* CGraphics::GetSamplerState()
{
	return m_pSamplerState;
}


/**
* @brief	深度ステンシルステートセット
*/
void CGraphics::SetDepthStencilState(EDepthStencilKind kind)
{
	m_pDefDepthStencilState[kind]->Bind();
}


/**
* @brief	深度ステンシルビューセット
*/
void CGraphics::SetDepthStencilState(CDepthStencilState* pState)
{
	m_pDepthStencilState = pState;
}


/**
* @brief	ターゲットビュー更新
*/
void CGraphics::UpdateTargetView()
{
	// レンダーターゲット取得
	ID3D11RenderTargetView* pRTV[4] = {};
	for (UINT i = 0; i < m_renderTargetNum&&i < 4; ++i)
	{
		pRTV[i] = reinterpret_cast<CRenderTarget*>(m_pRenderTarget[i])->GetView();
	}
	// 深度ステンシル取得
	CDepthStencil* pDSV = reinterpret_cast<CDepthStencil*>(m_pDepthStencilView);
	// 設定
	g_pDeviceContext->OMSetRenderTargets(m_renderTargetNum, pRTV, pDSV->GetView());
}



/**
* @brief	ブレンドステートセット
*/
void SetBlendState(EBlendState blend)
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	g_pDeviceContext->OMSetBlendState(g_pBlendState[blend], blendFactor, 0xffffffff);
}


/**
* @brief	カリングモードセット
*/
void SetCullMode(ECullMode cull)
{
	g_pDeviceContext->RSSetState(g_pRasterizer[cull]);
}


/**
* @brief	デバイス取得
*/
ID3D11Device* GetDevice()
{
	return g_pDevice;
}


/**
* @brief	デバイスコンテキスト取得
*/
ID3D11DeviceContext* GetDeviceContext()
{
	return g_pDeviceContext;
}


/**
* @brief	スワップチェイン取得
*/
IDXGISwapChain* GetSwapChain()
{
	return g_pSwapChain;
}

