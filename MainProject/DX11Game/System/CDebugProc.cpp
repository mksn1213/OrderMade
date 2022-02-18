/**
*
* @file		CDebugProc.cpp
* @brief	デバッグ表示クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
*
*/

/** インクルード部 */
#include <stdarg.h>
#include <string.h>
#include <System/CDebugProc.h>
#include <System/CPolygon.h>
//#include <System/Texture.h>
#include <System/Resource/CTextureManager.h>
#include <System/Graphics/CGraphics.h>

// マクロ定義
#define	TEXTURE_FILENAME	L"data/texture/PressStart2Ph_e.tga"
#define FONT_WIDTH			16
#define FONT_HEIGHT			16

// 静的メンバ
ID3D11ShaderResourceView* CDebugProc::m_pTexture;	// テクスチャへのポインタ
char CDebugProc::m_szDebug[8192];					// デバッグ情報
bool CDebugProc::m_bHiragana = false;				// 平仮名フラグ

// 初期化
HRESULT CDebugProc::Init()
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr = S_OK;

	// テクスチャの読み込み
	hr = CreateTextureFromFile(pDevice, TEXTURE_FILENAME, &m_pTexture);

	return hr;
}

// 終了処理
void CDebugProc::Uninit()
{
	// テクスチャ解法
	SAFE_RELEASE(m_pTexture);
}

// 描画
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
	// テクスチャ設定を元に戻す
	polygon->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	polygon->SetUV(0.0f, 0.0f);
	polygon->SetFrameSize(1.0f, 1.0f);

	SetBlendState(BS_NONE);
	//SetZBuffer(true);
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_ON);
}

// 登録開始
void CDebugProc::Start(bool hiragana)
{
	SetHiragana(hiragana);
	m_szDebug[0] = '\0';
}

// 登録
int CDebugProc::Print(const char *fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	char aBuf[256];
	int nLen = _vsprintf_p(aBuf, sizeof(aBuf), fmt, list);
	va_end(list);

	// 連結
	if ((strlen(m_szDebug) + strlen(aBuf)) < sizeof(m_szDebug) - 1) {
		strcat_s(m_szDebug, sizeof(m_szDebug), aBuf);
	}

	return nLen;
}

// 平仮名設定
bool CDebugProc::SetHiragana(bool hiragana)
{
	bool prev = m_bHiragana;
	m_bHiragana = hiragana;
	return prev;
}
