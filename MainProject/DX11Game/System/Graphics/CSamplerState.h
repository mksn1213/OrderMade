#pragma once
/**
*
* @file		CSamplerState.h
* @brief	�T���v���[�X�e�[�g�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/DirectX.h>

/** �T���v���[�X�e�[�g�N���X */
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
