#pragma once
/**
*
* @file		Main.h
* @brief	メイン関数
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
* @date		2022/01/15	構成変更
*
*/

/** インクルード部 */
#include <Windows.h>

HRESULT Init(HWND hWnd);
void	Uninit();
void	Update();
void	Draw();
int		GetFPSCount();
