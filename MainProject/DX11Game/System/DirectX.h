#pragma once
/**
*
* @file		DirectX.h
* @brief	DirectX�w�b�_�[
* @author	SHONOSUKE MAKITA
* @date		2021/01/15	�����J�n
*
*/

/** �C���N���[�h�� */
#include <d3d11.h>
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib, "d3d11")

ID3D11Device*		 GetDevice();
ID3D11DeviceContext* GetDeviceContext();
IDXGISwapChain*		 GetSwapChain();
HINSTANCE			 GetInstance();
HWND				 GetMainWnd();


HRESULT InitDX(HWND hWnd, bool bWindows);
void UninitDX();
