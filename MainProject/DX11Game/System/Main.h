#pragma once
/**
*
* @file		Main.h
* @brief	���C���֐�
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
* @date		2022/01/15	�\���ύX
*
*/

/** �C���N���[�h�� */
#include <Windows.h>

HRESULT Init(HWND hWnd);
void	Uninit();
void	Update();
void	Draw();
int		GetFPSCount();
