#pragma once
/**
*
* @file		CDepthStencilState.h
* @brief	深度ステンシルステートクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	実装開始
*
*/

/** インクルード部 */
#include <System/DirectX.h>

/** 深度ステンシルステートクラス */
class CDepthStencilState
{
public:
	CDepthStencilState();
	~CDepthStencilState();

	HRESULT Create(bool dipthEnable, bool stensilEnable);
	void Bind();

private:
	ID3D11DepthStencilState* m_pState;
};