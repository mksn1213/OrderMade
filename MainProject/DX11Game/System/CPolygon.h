#pragma once
/**
*
* @file		CPolyton.h
* @brief	ポリゴンクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
* @date		2022/01/15	シングルトン継承
* @date		2022/01/21	シェーダーをリストで管理
*
*/

/** インクルード部 */
#include <System/DirectX.h>
#include <System/Utility/Singleton.h>
#include <System/Defines.h>
#include <iostream>

#define POLYGON	(CPolygon::GetInstance())

class CGameObject;
/** ポリゴンクラス */
class CPolygon :public Singleton<CPolygon>
{
	//SINGLETON_CONSTRACTOR(CPolygon);
public:
	CPolygon();
	virtual ~CPolygon();

	HRESULT Init()		final;
	void	Uninit()	final;
	void Draw(ID3D11DeviceContext* pDeviceContext, std::weak_ptr<CGameObject> spObj);
	void SetTexture(ID3D11ShaderResourceView* pTexture);
	void SetEffectTexture(ID3D11ShaderResourceView* pTexture);
	void SetMultiTexture(ID3D11ShaderResourceView* pTexture);
	void SetMultiTexture(ID3D11ShaderResourceView* pTexture, ID3D11ShaderResourceView* pTexture2);
	void SetParam(float fParam) { m_fParam = fParam; }
	void SetPos(float fX, float fY);
	void SetSize(float fScaleX, float fScaleY);
	void SetAngle(float fAngle);
	void SetUV(float fU, float fV);
	void SetFrameSize(float fWidth, float fHeight);
	void SetColor(float fRed, float fGreen, float fBlue);
	void SetColor(XMFLOAT3 vColor);
	void SetAlpha(float fAlpha);
	void SetColor(float fRed, float fGreen, float fBlue, float fAlpha);
	void SetColor(XMFLOAT4 vColor);

private:
	ID3D11ShaderResourceView*	m_pTexture;			// テクスチャ
	ID3D11ShaderResourceView*	m_pEffectTexture;	// 効果テクスチャ
	ID3D11ShaderResourceView*	m_pMultiTexture;	// マルチテクスチャ
	ID3D11ShaderResourceView*	m_pMultiTexture2;	// マルチテクスチャ2
	float						m_fParam;			// シェーダー用パラメータ

	VERTEX_2D m_vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	XMFLOAT3 m_vPos;						// ポリゴンの移動量
	XMFLOAT3 m_vAngle;						// ポリゴンの回転量
	XMFLOAT3 m_vScale;						// ポリゴンのサイズ
	XMFLOAT4 m_vColor;						// ポリゴンの頂点カラー
	bool m_bInvalidate;						// 頂点データ更新フラグ

	XMFLOAT2 m_vPosTexFrame;				// UV座標
	XMFLOAT2 m_vSizeTexFrame;				// テクスチャ抽出サイズ

	// 更新後変数
	ID3D11Buffer*		m_pVertexBuffer;	// 頂点バッファ

	XMFLOAT4X4 m_mProj;						// 射影変換行列
	XMFLOAT4X4 m_mView;						// ビュー変換行列
	XMFLOAT4X4 m_mWorld;					// ワールド変換行列
	XMFLOAT4X4 m_mTex;						// テクスチャ変換行列

private:
	HRESULT MakeVertex(ID3D11Device* pDevice);
	void SetVertex(void);
};
