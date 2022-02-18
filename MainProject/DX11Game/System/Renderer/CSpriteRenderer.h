#pragma once
/**
*
* @file		CSpriteRenderer.h
* @brief	スプライトレンダラークラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	実装開始
*
*/

/** インクルード部 */
#include <System/Renderer/CRenderer.h>
#include <System/Defines.h>
#include <System/Utility/Vector3.h>
#include <System/Resource/TextureID.h>

/** スプライトレンダラークラス */
class CSpriteRenderer final : public CRenderer
{
public:
	CSpriteRenderer();
	virtual ~CSpriteRenderer();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
	void Draw(ID3D11DeviceContext* pDC)	override;

	void SetTexture(ETexture texture);
	void SetTexture(ID3D11ShaderResourceView* texture);
	void SetEffectTexture(ETexture texture);
	void SetEffectTexture(ID3D11ShaderResourceView* texture);
	void SetMultiTexture(ETexture texture, int nNo = 0);
	void SetMultiTexture(ID3D11ShaderResourceView* texture, int nN = 0);
	void SetMultiTexture(ETexture texture, ETexture texture2);
	void SetMultiTexture(ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* texture2);

	/**
	* @brief	色変更
	* @param	color	変更後の色
	*/
	void SetColor(Vector3 color) { m_color = color; }

	/**
	* @brief	色変更
	* @param	color	変更後の色
	* @param	fAlpha	アルファ値
	*/
	void SetColor(Vector3 color, float fAlpha)
	{
		m_color = color;
		m_fAlpha = fAlpha;
	}

	/**
	* @brief	色変更
	* @param	r	赤
	* @param	g	緑
	* @param	b	青
	*/
	void SetColor(float r, float g, float b)
	{
		m_color->x = r;
		m_color->y = g;
		m_color->z = b;
	}

	/**
	* @brief	色変更
	* @param	r	赤
	* @param	g	緑
	* @param	b	青
	* @param	a	アルファ値
	*/
	void SetColor(float r, float g, float b, float fAlpha)
	{
		m_color->x = r;
		m_color->y = g;
		m_color->z = b;
		m_fAlpha = fAlpha;
	}

	/**
	* @brief	透明度変更
	* @param	fAlpha		透明度
	*/
	void SetAlpha(float fAlpha) 
	{ 
		m_fAlpha = fAlpha; 
	}

	/**
	* @brief	描画サイズセット
	* @param	size	セットする描画サイズ
	*/
	void SetDrawSize(Vector3 size) { m_size = size; }

	/**
	* @brief	描画サイズ取得
	* @param	Vector3		描画サイズ
	*/
	Vector3 GetDrawSize() { return m_size; }

	/**
	* @brief	ローカル座標セット
	* @param	localPos	ローカル座標
	*/
	void SetLocalPos(Vector3 localPos) { m_localPos = localPos; }

	/**
	* @brief	テクスチャサイズセット
	* @param	texSize		テクスチャサイズ
	*/
	void SetTexSize(Vector3 texSize) { m_texSize = texSize; }

	/**
	* @brief	テクスチャ座標セット
	* @param	texPos		テクスチャ座標
	*/
	void SetTexPos(Vector3 texPos) { m_texPos = texPos; }

	/**
	* @brief	シェーダーパラメータセット
	* @param	fParam	パラメータ
	*/
	void SetParam(float fParam) { m_fParam = fParam; }

private:
	// テクスチャ
	ID3D11ShaderResourceView*	m_pTexture;
	// 効果テクスチャ
	ID3D11ShaderResourceView*	m_pEffectTexture;
	// マルチテクスチャ
	ID3D11ShaderResourceView*	m_pMultiTexture;
	// マルチテクスチャ2
	ID3D11ShaderResourceView*	m_pMultiTexture2;;
	// 色情報
	Vector3						m_color;
	// アルファ値
	float						m_fAlpha;
	// テクスチャ座標
	Vector3						m_texPos;
	// テクスチャサイズ
	Vector3						m_texSize;
	// 描画サイズ
	Vector3						m_size;
	// ローカル座標
	Vector3						m_localPos;
	// シェーダー用パラメータ
	float						m_fParam;

public:
	static const EComponentType comID;
};