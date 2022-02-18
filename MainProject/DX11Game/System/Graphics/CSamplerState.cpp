/**
*
* @file		CSamplerState.cpp
* @brief	サンプラーステートクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	実装開始
*
*/

/** インクルード部 */
#include <System/Graphics/CSamplerState.h>
#include <System/Graphics/CGraphics.h>

/**
* @brief	コンストラクタ
*/
CSamplerState::CSamplerState()
	: m_pState(nullptr)
{

}


/**
* @brief	デストラクタ
*/
CSamplerState::~CSamplerState()
{

}


/**
* @brief	作成
*/
HRESULT CSamplerState::Create(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address)
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = filter;
	desc.AddressU = address;
	desc.AddressV = address;
	desc.AddressW = address;
	return GetDevice()->CreateSamplerState(&desc, &m_pState);
}


/**
* @brief	割り当て
*/
void CSamplerState::Bind()
{
	GetDeviceContext()->PSSetSamplers(0, 1, &m_pState);
	GRAPHICS->SetSamplerState(this);
}