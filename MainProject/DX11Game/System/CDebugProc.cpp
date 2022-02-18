/**
*
* @file		CDebugProc.cpp
* @brief	�f�o�b�O�\���N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <stdarg.h>
#include <string.h>
#include <System/CDebugProc.h>
#include <System/CPolygon.h>
//#include <System/Texture.h>
#include <System/Resource/CTextureManager.h>
#include <System/Graphics/CGraphics.h>

// �}�N����`
#define	TEXTURE_FILENAME	L"data/texture/PressStart2Ph_e.tga"
#define FONT_WIDTH			16
#define FONT_HEIGHT			16

// �ÓI�����o
ID3D11ShaderResourceView* CDebugProc::m_pTexture;	// �e�N�X�`���ւ̃|�C���^
char CDebugProc::m_szDebug[8192];					// �f�o�b�O���
bool CDebugProc::m_bHiragana = false;				// �������t���O

// ������
HRESULT CDebugProc::Init()
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr = S_OK;

	// �e�N�X�`���̓ǂݍ���
	hr = CreateTextureFromFile(pDevice, TEXTURE_FILENAME, &m_pTexture);

	return hr;
}

// �I������
void CDebugProc::Uninit()
{
	// �e�N�X�`����@
	SAFE_RELEASE(m_pTexture);
}

// �`��
void CDebugProc::Draw()
{
	//SetZBuffer(false);
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_OFF);
	SetBlendState(BS_ALPHABLEND);

	auto polygon = POLYGON;
	polygon->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	XMFLOAT2 vPos(SCREEN_WIDTH * -0.5f + FONT_WIDTH * 0.5f,
		SCREEN_HEIGHT * 0.5f - FONT_HEIGHT * 0.5f);
	polygon->SetTexture(m_pTexture);
	polygon->SetFrameSize(8.0f / 128.0f, 8.0f / 128.0f);
	polygon->SetSize(FONT_WIDTH, FONT_HEIGHT);
	for (char* pChr = &m_szDebug[0]; *pChr; ++pChr) {
		if (*pChr == '\n') {
			vPos.x = SCREEN_WIDTH * -0.5f + FONT_WIDTH * 0.5f;
			vPos.y -= FONT_HEIGHT;
			continue;
		}
		int nChr = (BYTE)*pChr;
		if (nChr == 0x0084) {
			nChr = (BYTE)*(pChr + 1);
			if (nChr >= 0x00c0 && nChr <= 0x00cf) {
				const XMFLOAT4 vColor[] = {
					XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f),
					XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f),
					XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f),
					XMFLOAT4(0.0f, 0.5f, 0.5f, 1.0f),
					XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f),
					XMFLOAT4(0.5f, 0.0f, 0.5f, 1.0f),
					XMFLOAT4(0.5f, 0.5f, 0.0f, 1.0f),
					XMFLOAT4(0.752941f, 0.752941f, 0.752941f, 1.0f),
					XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),
					XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
					XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
					XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f),
					XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
					XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f),
					XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),
					XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
				};
				polygon->SetColor(vColor[nChr & 0x0f]);
				++pChr;
				continue;
			}
		}
		polygon->SetPos(vPos.x, vPos.y);
		if (m_bHiragana &&
			(nChr >= 0xa6 && nChr <= 0xaf || nChr >= 0xb1 && nChr <= 0xdd))
			nChr ^= 0x20;
		polygon->SetUV((nChr & 15) / 16.0f, (nChr >> 4) / 16.0f);
		std::weak_ptr<CGameObject> obj;
		polygon->Draw(pDeviceContext, obj);
		vPos.x += FONT_WIDTH;
	}
	// �e�N�X�`���ݒ�����ɖ߂�
	polygon->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	polygon->SetUV(0.0f, 0.0f);
	polygon->SetFrameSize(1.0f, 1.0f);

	SetBlendState(BS_NONE);
	//SetZBuffer(true);
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_ON);
}

// �o�^�J�n
void CDebugProc::Start(bool hiragana)
{
	SetHiragana(hiragana);
	m_szDebug[0] = '\0';
}

// �o�^
int CDebugProc::Print(const char *fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	char aBuf[256];
	int nLen = _vsprintf_p(aBuf, sizeof(aBuf), fmt, list);
	va_end(list);

	// �A��
	if ((strlen(m_szDebug) + strlen(aBuf)) < sizeof(m_szDebug) - 1) {
		strcat_s(m_szDebug, sizeof(m_szDebug), aBuf);
	}

	return nLen;
}

// �������ݒ�
bool CDebugProc::SetHiragana(bool hiragana)
{
	bool prev = m_bHiragana;
	m_bHiragana = hiragana;
	return prev;
}
