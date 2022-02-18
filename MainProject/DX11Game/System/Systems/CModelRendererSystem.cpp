/**
*
* @file		CModelRendererSystem.cpp
* @brief	モデル描画システムクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CModelRendererSystem.h>
#include <System/Renderer/CModelRenderer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Graphics/CGraphics.h>
#include <algorithm>

/**
* @brief	コンストラクタ
*/
CModelRendererSystem::CModelRendererSystem()
{

}


/**
* @brief	デストラクタ
*/
CModelRendererSystem::~CModelRendererSystem()
{

}


/**
* @brief	生成時処理
*/
void CModelRendererSystem::OnCreate()
{
}


/**
* @brief	削除時処理
*/
void CModelRendererSystem::OnDestroy()
{
}


/**
* @brief	描画処理
*/
void CModelRendererSystem::OnDraw(ID3D11DeviceContext* pDC)
{
	// シャドウマップ
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_OFF);
	float color[] = { 1,1,1,1 };
	GRAPHICS->SetShadowRenderTarget(color);
	GRAPHICS->SetShadowDepthStencilView();

	// テクスチャへ書き込み
	std::for_each(m_pComponentList.begin(), m_pComponentList.end(),
		[&pDC](CModelRenderer* renderer)
	{
		const auto& obj = renderer->m_spGameObject.lock();
		obj->SaveShaderKind();
		obj->SetShader(DepthWriteVS, DepthWritePS);
		if (obj->IsActive())	renderer->Draw(pDC);
	});

	// 通常描画
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_ON);
	GRAPHICS->SetRenderTargetDefault();
	GRAPHICS->SetDepthStencilViewDefault();

	std::for_each(m_pComponentList.begin(),m_pComponentList.end(),
		[&pDC](CModelRenderer* renderer)
		{
			const auto& obj = renderer->m_spGameObject.lock();
			obj->SetShader(obj->GetVSKindBuffer(), obj->GetPSKindBuffer());
			if (obj->IsActive())	renderer->Draw(pDC);
			obj->SetShader(AssimpVS, AssimpPS);
		});
}