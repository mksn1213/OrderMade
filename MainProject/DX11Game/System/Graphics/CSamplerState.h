#pragma once
/**
*
* @file		CSamplerState.h
* @brief	サンプラーステートクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	実装開始
*
*/

/** インクルード部 */
#include <System/DirectX.h>

/** サンプラーステートクラス */
class CSamplerState
{
public:
	CSamplerState();
	virtual ~CSamplerState();

	HRESULT Create(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address);
	void Bind();

private:
	ID3D11SamplerState* m_pState;
};
