#pragma once
/**
*
* @file		CDepthStencilState.h
* @brief	�[�x�X�e���V���X�e�[�g�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/19	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/DirectX.h>

/** �[�x�X�e���V���X�e�[�g�N���X */
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