#pragma once
/**
*
* @file		CGraphics.h
* @brief	グラフィッククラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/15	実装開始
*
*/

/** インクルード部 */
#include <System/DirectX.h>
#include <System/Utility/Singleton.h>
#include <System/Texture/CTexture.h>
#include <System/Graphics/CSamplerState.h>
#include <System/Graphics/CDepthStencilState.h>

#define GRAPHICS (CGraphics::GetInstance())

/**
* @enum		ブレンドモード
*/
enum EBlendState
{
	BS_NONE = 0,	// 半透明合成無し
	BS_ALPHABLEND,	// 半透明合成
	BS_ADDITIVE,	// 加算合成
	BS_SUBTRACTION,	// 減算合成

	MAX_BLENDSTATE
};

/**
* @enum		カリングモード
*/
enum ECullMode
{
	CULL_NONE = 0,	// カリングしない
	CULL_FRONT,		// 前面カリング
	CULL_BACK,		// 背面カリング

	MAX_CULLMODE
};

/** グラフィッククラス */
class CGraphics final : public Singleton<CGraphics>
{
public:
	/**
	* @enum		ESamplerStateKind
	* @brief	サンプラーステートタイプ
	*/
	enum ESamplerStateKind
	{
		SAMPLER_POINT,
		SAMPLER_LINEAR,

		MAX_SAMPLER
	};

	/**
	* @enum		EDepthStencilKind
	* @brief	深度ステンシルタイプ
	*/
	enum EDepthStencilKind
	{
		DEPTHSTENCIL_OFF,
		DEPTHSTENCIL_ON,

		MAX_DEPTHSTENCIL
	};

public:
	HRESULT Init()		final;
	void	Uninit()	final;
	void	BeginDraw();
	void	EndDraw();

	// レンダーターゲット
	void SetRenderTarget(CTexture** ppRenderTarget, UINT numView, float* pClearColor = nullptr);
	void SetRenderTargetDefault(float* pClearColor = nullptr);
	void SetShadowRenderTarget(float* pClearColor = nullptr);
	void SetDepthStencilView(CTexture* pDepthStencilView, bool isClear = false);
	void SetDepthStencilViewDefault(bool isClear = false);
	void SetShadowDepthStencilView(bool isClear = false);

	// サンプラー
	void SetSamplerState(ESamplerStateKind kind);
	void SetSamplerState(CSamplerState *pState);
	CSamplerState* GetSamplerState();

	// 深度ステンシル
	void SetDepthStencilState(EDepthStencilKind kind);
	void SetDepthStencilState(CDepthStencilState* pState);

	CTexture* GetShadowTexture() { return m_pShadowRenderTarget; }
	CTexture* GetDefaulTexture() { return m_pDefRenderTarget; }

private:
	void UpdateTargetView();

	CTexture*			m_pDefRenderTarget;
	CTexture*			m_pDefDepthStencil;
	CTexture*			m_pRenderTarget[4];
	UINT				m_renderTargetNum;
	CTexture*			m_pDepthStencilView;
	CSamplerState*		m_pDefSamplerState[MAX_SAMPLER];
	CSamplerState*		m_pSamplerState;
	CDepthStencilState* m_pDefDepthStencilState[MAX_DEPTHSTENCIL];
	CDepthStencilState* m_pDepthStencilState;

	// シャドーマップ用
	CTexture*			m_pShadowRenderTarget;
	CTexture*			m_pShadowDepthStencil;
};

ID3D11Device* GetDevice();
ID3D11DeviceContext* GetDeviceContext();
void SetBlendState(EBlendState nBlendState);
void SetCullMode(ECullMode nCullMode);
