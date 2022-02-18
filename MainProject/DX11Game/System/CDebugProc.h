#pragma once
/**
*
* @file		CDebugProc.h
* @brief	�f�o�b�O�\���N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Defines.h>

class CDebugProc
{
private:
	static ID3D11ShaderResourceView* m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	static char m_szDebug[8192];					// �f�o�b�O���
	static bool m_bHiragana;						// �������t���O

public:
	static HRESULT Init();
	static void Uninit();
	static void Draw();

	static void Start(bool hiragana = false);
	static int Print(const char *fmt, ...);
	static bool SetHiragana(bool hiragana = true);
};
