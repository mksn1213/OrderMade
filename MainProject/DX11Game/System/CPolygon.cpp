/**
*
* @file		CPolyton.cpp
* @brief	ポリゴンクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
*
*/

/** インクルード部 */
#include <System/CPolygon.h>
#include <System/Graphics/ShaderList.h>
#include <System/Graphics/CGraphics.h>
#include <System/GameObject/CGameObject.h>
#include <System/Graphics/ShaderList.h>

/** 構造体宣言 */

/**
* @brief	コンストラクタ
*/
CPolygon::CPolygon()
	: m_pTexture(nullptr)
	, m_pEffectTexture(nullptr)
	, m_pMultiTexture(nullptr)
	, m_pMultiTexture2(nullptr)
	, m_fParam(0.0f)
	, m_vPos(0.0f, 0.0f, 0.0f)
	, m_vAngle(0.0f, 0.0f, 0.0f)
	, m_vScale(1.0f, 1.0f, 1.0f)
	, m_vColor(1.0f, 1.0f, 1.0f, 1.0f)
	, m_bInvalidate(false)
	, m_vPosTexFrame(0.0f, 0.0f)
	, m_vSizeTexFrame(1.0f, 1.0f)
	, m_pVertexBuffer(nullptr)
{

}


/**
* @brief	デストラクタ
*/
CPolygon::~CPolygon()
{

}


/**
* @brief	初期化処理
*/
HRESULT CPolygon::Init()
{
	HRESULT hr = S_OK;
	auto pDevice = GetDevice();

	// 変換行列初期化
	XMStoreFloat4x4(&m_mWorld, XMMatrixIdentity());
	XMStoreFloat4x4(&m_mView, XMMatrixLookAtLH(XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	XMStoreFloat4x4(&m_mProj,
		XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 100.0f));
	XMStoreFloat4x4(&m_mTex, XMMatrixIdentity());
	m_mTex._44 = 0.0f;

	// 頂点情報の作成
	hr = MakeVertex(pDevice);

	return hr;
}


/**
* @brief	終了処理
*/
void CPolygon::Uninit()
{
	// 頂点バッファの解放
	SAFE_RELEASE(m_pVertexBuffer);
}


/**
* @brief	描画処理
*/
void CPolygon::Draw(ID3D11DeviceContext* pDeviceContext, std::weak_ptr<CGameObject> spObj)
{
	// 拡縮
	XMMATRIX mWorld = XMMatrixScaling(m_vScale.x, m_vScale.y, m_vScale.z);
	// 回転
	mWorld *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_vAngle.x),
		XMConvertToRadians(m_vAngle.y), XMConvertToRadians(m_vAngle.z));
	// 移動
	mWorld *= XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z);
	// ワールド マトリックスに設定
	XMStoreFloat4x4(&m_mWorld, mWorld);

	if (m_pTexture) 
	{
		// 拡縮
		mWorld = XMMatrixScaling(m_vSizeTexFrame.x, m_vSizeTexFrame.y, 1.0f);
		// 移動
		mWorld *= XMMatrixTranslation(m_vPosTexFrame.x, m_vPosTexFrame.y, 0.0f);
		// テクスチャ マトリックスに設定
		XMStoreFloat4x4(&m_mTex, mWorld);
	}
	else {
		// テクスチャ無し
		m_mTex._44 = 0.0f;
	}

	// 頂点バッファ更新
	SetVertex();
	
	const auto& obj = spObj.lock();
	if (obj)
	{
		// 通常描画
		auto psKind = obj->GetPSKind();
		if (psKind == EPixelShaderKind::Simple2DPS)
		{
			SetSimple2DShader(m_pTexture, m_mProj, m_mView, m_mWorld, m_mTex);
		}
		// ディゾルブ
		else if (psKind == EPixelShaderKind::DissolvePS)
		{
			SetDissolveShader(m_pTexture, m_pEffectTexture, m_mProj, m_mView, m_mWorld, m_mTex);
		}
		// マルチテクスチャ + ディゾルブ
		else if (psKind == EPixelShaderKind::MultiTexturePS)
		{
			SetMultiTextureShader(m_pTexture, m_pEffectTexture, m_pMultiTexture, m_pMultiTexture2, m_fParam, m_mProj, m_mView, m_mWorld, m_mTex);
		}
	}
	else
	{
		SetSimple2DShader(m_pTexture, m_mProj, m_mView, m_mWorld, m_mTex);
	}

	UINT stride = sizeof(VERTEX_2D);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// プリミティブ形状をセット
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴンの描画
	pDeviceContext->Draw(NUM_VERTEX, 0);
}


/**
* @brief	頂点の作成
*/
HRESULT CPolygon::MakeVertex(ID3D11Device* pDevice)
{
	// 頂点座標の設定
	m_vertexWk[0].vtx = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	m_vertexWk[1].vtx = XMFLOAT3(0.5f, 0.5f, 0.0f);
	m_vertexWk[2].vtx = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	m_vertexWk[3].vtx = XMFLOAT3(0.5f, -0.5f, 0.0f);

	// 拡散反射光の設定
	m_vertexWk[0].diffuse = m_vColor;
	m_vertexWk[1].diffuse = m_vColor;
	m_vertexWk[2].diffuse = m_vColor;
	m_vertexWk[3].diffuse = m_vColor;

	// テクスチャ座標の設定
	m_vertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
	m_vertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
	m_vertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
	m_vertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(m_vertexWk);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = &m_vertexWk[0];

	HRESULT hr = pDevice->CreateBuffer(&vbd, &initData, &m_pVertexBuffer);

	return hr;
}


/**
* @brief	頂点座標の設定
*/
void CPolygon::SetVertex()
{
	if (m_bInvalidate) 
	{
		//頂点バッファの中身を埋める
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
		HRESULT hr = S_OK;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		hr = pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		if (SUCCEEDED(hr)) {
			// 拡散反射光の設定
			m_vertexWk[0].diffuse = m_vColor;
			m_vertexWk[1].diffuse = m_vColor;
			m_vertexWk[2].diffuse = m_vColor;
			m_vertexWk[3].diffuse = m_vColor;
			// 頂点データを上書き
			memcpy_s(msr.pData, sizeof(m_vertexWk), m_vertexWk, sizeof(m_vertexWk));
			// 頂点データをアンロックする
			pDeviceContext->Unmap(m_pVertexBuffer, 0);
			// フラグをクリア
			m_bInvalidate = false;
		}
	}
}


/**
* @brief	テクスチャの設定
* @param	pTexture	テクスチャ
*/
void CPolygon::SetTexture(ID3D11ShaderResourceView* pTexture)
{
	m_pTexture = pTexture;
	m_mTex._44 = (m_pTexture) ? 1.0f : 0.0f;
}


/**
* @brief	効果テクスチャの設定
* @param	pTexture	テクスチャ
*/
void CPolygon::SetEffectTexture(ID3D11ShaderResourceView* pTexture)
{
	m_pEffectTexture = pTexture;
}


/**
* @brief	マルチテクスチャの設定
* @param	pTexture	テクスチャ
*/
void CPolygon::SetMultiTexture(ID3D11ShaderResourceView* pTexture)
{
	m_pMultiTexture = pTexture;
}


/**
* @brief	マルチテクスチャの設定
* @param	pTexture	テクスチャ
* @param	pTexture2	テクスチャ2
*/
void CPolygon::SetMultiTexture(ID3D11ShaderResourceView* pTexture, ID3D11ShaderResourceView* pTexture2)
{
	m_pMultiTexture = pTexture;
	m_pMultiTexture2 = pTexture2;
}


/**
* @brief	座標セット
* @param	fX	X座標
* @param	fY	Y座標
*/
void CPolygon::SetPos(float fX, float fY)
{
	m_vPos.x = fX;
	m_vPos.y = fY;
}


/**
* @brief	サイズセット
* @param	fScaleX		Xサイズ
* @param	fScaleY		Yサイズ
*/
void CPolygon::SetSize(float fScaleX, float fScaleY)
{
	m_vScale.x = fScaleX;
	m_vScale.y = fScaleY;
}


/**
* @brief	角度セット(単位:度)
* @param	fAngleZ		Z軸角度
*/
void CPolygon::SetAngle(float fAngleZ)
{
	m_vAngle.z = fAngleZ;
}


/**
* @brief	左上テクスチャ座標セット
* @param	fU	u座標
* @param	fV	v座標
*/
void CPolygon::SetUV(float fU, float fV)
{
	m_vPosTexFrame.x = fU;
	m_vPosTexFrame.y = fV;
}


/**
* @brief	テクスチャフレームサイズセット
* @param	fWidth		横サイズ
* @param	fHeight		縦サイズ
*/
void CPolygon::SetFrameSize(float fWidth, float fHeight)
{
	m_vSizeTexFrame.x = fWidth;
	m_vSizeTexFrame.y = fHeight;
}


/**
* @brief	頂点カラーのセット
* @param	fRed	赤
* @param	fGreen	緑
* @param	fBlue	青
*/
void CPolygon::SetColor(float fRed, float fGreen, float fBlue)
{
	SetColor(XMFLOAT3(fRed, fGreen, fBlue));
}


/**
* @brief	頂点カラーのセット
* @param	vColor	色情報
*/
void CPolygon::SetColor(XMFLOAT3 vColor)
{
	if (vColor.x != m_vColor.x || vColor.y != m_vColor.y || vColor.z != m_vColor.z) {
		m_vColor.x = vColor.x;
		m_vColor.y = vColor.y;
		m_vColor.z = vColor.z;
		m_bInvalidate = true;
	}
}

/**
* @brief	頂点カラーのセット
* @param	fRed	赤
* @param	fGreen	緑
* @param	fBlue	青
* @param	fAlpha	不透明度
*/
void CPolygon::SetColor(float fRed, float fGreen, float fBlue, float fAlpha)
{
	SetColor(XMFLOAT4(fRed, fGreen, fBlue, fAlpha));
}


/**
* @brief	頂点カラーのセット
* @param	vColor	色情報
*/
void CPolygon::SetColor(XMFLOAT4 vColor)
{
	if (vColor.x != m_vColor.x || vColor.y != m_vColor.y || vColor.z != m_vColor.z || vColor.w != m_vColor.w) {
		m_vColor = vColor;
		m_bInvalidate = true;
	}
}


/**
* @brief	不透明度のセット
* @param	fAlpha	不透明度
*/
void CPolygon::SetAlpha(float fAlpha)
{
	if (fAlpha != m_vColor.w) {
		m_vColor.w = fAlpha;
		m_bInvalidate = true;
	}
}