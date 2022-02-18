/**
*
* @file		CSpriteRenderer.cpp
* @brief	スプライトレンダラークラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	実装開始
*
*/

/** インクルード部 */
#include <System/Renderer/CSpriteRenderer.h>
#include <System/Resource/CTextureManager.h>
#include <System/Component/CTransform.h>
#include <System/CPolygon.h>
#include <System/Graphics/CGraphics.h>
#include <System/GameObject/CGameObject.h>
#include <System/Systems/CSpriteRendererSystem.h>
#include <Scene/CSceneManager.h>

/** 静的メンバ */
const EComponentType CSpriteRenderer::comID = EComponentType::SpriteRenderer;

/**
* @brief	コンストラクタ
*/
CSpriteRenderer::CSpriteRenderer()
	: m_pTexture(nullptr)
	, m_pEffectTexture(nullptr)
	, m_color(Vector3::one())
	, m_fAlpha(1.0f)
	, m_texPos(Vector3::zero())
	, m_texSize(Vector3::one())
	, m_size(Vector3::one())
	, m_localPos(Vector3::zero())
	, m_fParam(0.0f)
{
	SetID(SpriteRenderer);
}


/**
* @brief	デストラクタ
*/
CSpriteRenderer::~CSpriteRenderer()
{

}


/**
* @brief	生成時
*/
void CSpriteRenderer::OnCreate()
{
	// レンダラー初期化
	CRenderer::OnCreate();
	// シェーダーセット
	m_spGameObject.lock()->SetShader(Simple2DVS, Simple2DPS);
	// システムリストに格納
	CSpriteRendererSystem* pSystem = SCENE_MANAGER->GetSystem<CSpriteRendererSystem>(EComponentType::SpriteRenderer);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	破棄時
*/
void CSpriteRenderer::OnDestroy()
{
	// システムから除外
	CSpriteRendererSystem* pSystem = SCENE_MANAGER->GetSystem<CSpriteRendererSystem>(EComponentType::SpriteRenderer);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	更新処理
*/
void CSpriteRenderer::Update()
{

}


/**
* @brief	描画処理
*/
void CSpriteRenderer::Draw(ID3D11DeviceContext* pDC)
{
	// Zバッファ無効
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_OFF);
	// ブレンドステート
	SetBlendState(BS_ALPHABLEND);

	const auto& transform = m_spTransform.lock();

	// 座標
	auto polygon = POLYGON;
	auto pos = transform->GetPosition() + m_localPos;
	polygon->SetPos(pos->x, pos->y);
	// 角度
	polygon->SetAngle(transform->GetRotation()->z);
	// サイズ
	polygon->SetSize(m_size->x, m_size->y);
	// 色
	polygon->SetColor(m_color.m_vector);
	// アルファ値
	polygon->SetAlpha(m_fAlpha);
	// テクスチャ
	polygon->SetTexture(m_pTexture);
	// 効果テクスチャ
	polygon->SetEffectTexture(m_pEffectTexture);
	// マルチテクスチャ
	if (m_spGameObject.lock()->GetPSKind() == EPixelShaderKind::MultiTexturePS)
	{
		polygon->SetParam(m_fParam);
		polygon->SetMultiTexture(m_pMultiTexture, m_pMultiTexture2);
	}
	// テクスチャ座標
	polygon->SetUV(m_texPos->x, m_texPos->y);
	// テクスチャサイズ
	polygon->SetFrameSize(m_texSize->x, m_texSize->y);

	// 描画処理
	polygon->Draw(pDC,m_spGameObject);

	// ブレンドステート
	SetBlendState(BS_NONE);
	// Zバッファ有効
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_ON);
}


/**
* @brief	テクスチャセット
* @param	texture		セットするテクスチャタイプ
*/
void CSpriteRenderer::SetTexture(ETexture texture)
{
	if (m_pTexture != nullptr)	m_pTexture = nullptr;
	m_pTexture = TEXTURE_MANAGER->GetTexture(texture);
}


/**
* @brief	テクスチャセット
* @param	texture		セットするテクスチャリソース
*/
void CSpriteRenderer::SetTexture(ID3D11ShaderResourceView* texture)
{
	m_pTexture = texture;
}


/**
* @brief	効果テクスチャセット
* @param	texture		セットするテクスチャタイプ
*/
void CSpriteRenderer::SetEffectTexture(ETexture texture)
{
	if (m_pEffectTexture != nullptr)	m_pEffectTexture= nullptr;
	m_pEffectTexture = TEXTURE_MANAGER->GetTexture(texture);
}


/**
* @brief	効果テクスチャセット
* @param	texture		セットするテクスチャリソース
*/
void CSpriteRenderer::SetEffectTexture(ID3D11ShaderResourceView* texture)
{
	m_pEffectTexture = texture;
}


/**
* @brief	マルチテクスチャセット
* @param	texture		セットするテクスチャタイプ
* @param	nNo			割り当て番号
*/
void CSpriteRenderer::SetMultiTexture(ETexture texture, int nNo)
{
	if (nNo == 0)
	{
		if (m_pMultiTexture != nullptr)		m_pMultiTexture = nullptr;
		m_pMultiTexture = TEXTURE_MANAGER->GetTexture(texture);
	}
	else if (nNo == 1)
	{
		if (m_pMultiTexture2 != nullptr)	m_pMultiTexture2 = nullptr;
		m_pMultiTexture2 = TEXTURE_MANAGER->GetTexture(texture);
	}
}


/**
* @brief	マルチテクスチャセット
* @param	texture		セットするテクスチャリソース
* @param	nNo			割り当て番号
*/
void CSpriteRenderer::SetMultiTexture(ID3D11ShaderResourceView* texture, int nNo)
{
	if (nNo == 0)		m_pMultiTexture = texture;
	else if (nNo == 1)	m_pMultiTexture2 = texture;
}


/**
* @brief	マルチテクスチャセット
* @param	texture		セットするテクスチャタイプ
* @param	texture2	セットするテクスチャタイプ2
*/
void CSpriteRenderer::SetMultiTexture(ETexture texture, ETexture texture2)
{
	if (m_pMultiTexture != nullptr)		m_pMultiTexture = nullptr;
	m_pMultiTexture = TEXTURE_MANAGER->GetTexture(texture);
	if (m_pMultiTexture2 != nullptr)	m_pMultiTexture2 = nullptr;
	m_pMultiTexture2 = TEXTURE_MANAGER->GetTexture(texture2);
}


/**
* @brief	マルチテクスチャセット
* @param	texture		セットするテクスチャリソース
* @param	texture2	セットするテクスチャリソース2
*/
void CSpriteRenderer::SetMultiTexture(ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* texture2)
{
	m_pMultiTexture = texture;
	m_pMultiTexture2 = texture2;
}
