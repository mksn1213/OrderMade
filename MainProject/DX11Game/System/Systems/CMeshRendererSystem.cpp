/**
*
* @file		CMeshRendererSystem.cpp
* @brief	メッシュ描画システムクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CMeshRendererSystem.h>
#include <System/Renderer/CMeshRenderer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Graphics/CGraphics.h>
#include <algorithm>

/**
* @brief	コンストラクタ
*/
CMeshRendererSystem::CMeshRendererSystem()
{

}


/**
* @brief	デストラクタ
*/
CMeshRendererSystem::~CMeshRendererSystem()
{

}


/**
* @brief	生成時処理
*/
void CMeshRendererSystem::OnCreate()
{

}


/**
* @brief	削除時処理
*/
void CMeshRendererSystem::OnDestroy()
{

}


/**
* @brief	描画処理
*/
void CMeshRendererSystem::OnDraw(ID3D11DeviceContext* pDC)
{
	std::for_each(m_pComponentList.begin(), m_pComponentList.end(),
		[&pDC](CMeshRenderer* renderer)
		{
			if(renderer->m_spGameObject.lock()->IsActive())	renderer->Draw(pDC);
		});
}