/**
*
* @file		CDepthStencilState.cpp
* @brief	深度ステンシルステートクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	実装開始
*
*/

/** インクルード部 */
#include <System/Graphics/CDepthStencilState.h>
#include <System/Graphics/CGraphics.h>

/**
* @brief	コンストラクタ
*/
CDepthStencilState::CDepthStencilState()
	: m_pState(nullptr)
{

}


/**
* @brief	デストラクタ
*/
CDepthStencilState::~CDepthStencilState()
{
	SAFE_RELEASE(m_pState);
}


/**
* @brief	作成
*/
HRESULT CDepthStencilState::Create(bool depthEnable, bool stencilEnable)
{
	D3D11_DEPTH_STENCIL_DESC desc;
	// 深度値
	desc.DepthEnable = depthEnable;
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	// ステンシル
	desc.StencilEnable = stencilEnable;
	desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL;
	desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	desc.BackFace.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL;

	// 生成
	return GetDevice()->CreateDepthStencilState(&desc, &m_pState);
}


/**
* @brief	割り当て
*/
void CDepthStencilState::Bind()
{
	GetDeviceContext()->OMSetDepthStencilState(m_pState, 0);
	GRAPHICS->SetDepthStencilState(this);
}
