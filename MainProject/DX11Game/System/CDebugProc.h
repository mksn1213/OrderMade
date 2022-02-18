#pragma once
/**
*
* @file		CDebugProc.h
* @brief	デバッグ表示クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
*
*/

/** インクルード部 */
#include <System/Defines.h>

class CDebugProc
{
private:
	static ID3D11ShaderResourceView* m_pTexture;	// テクスチャへのポインタ
	static char m_szDebug[8192];					// デバッグ情報
	static bool m_bHiragana;						// 平仮名フラグ

public:
	static HRESULT Init();
	static void Uninit();
	static void Draw();

	static void Start(bool hiragana = false);
	static int Print(const char *fmt, ...);
	static bool SetHiragana(bool hiragana = true);
};
