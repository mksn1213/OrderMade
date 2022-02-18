/**
*
* @file		CSpriteRendererSystem.cpp
* @brief	スプライト描画システムクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CSpriteRendererSystem.h>
#include <System/Renderer/CSpriteRenderer.h>
#include <System/GameObject/CGameObject.h>
#include <algorithm>

/**
* @brief	コンストラクタ
*/
CSpriteRendererSystem::CSpriteRendererSystem()
{

}


/**
* @brief	デストラクタ
*/
CSpriteRendererSystem::~CSpriteRendererSystem()
{

}


/**
* @brief	生成時処理
*/
void CSpriteRendererSystem::OnCreate()
{

}


/**
* @brief	削除時処理
*/
void CSpriteRendererSystem::OnDestroy()
{

}


/**
* @brief	描画処理
*/
void CSpriteRendererSystem::OnDraw(ID3D11DeviceContext* pDC)
{
	std::for_each(m_pComponentList.begin(), m_pComponentList.end(),
		[&pDC](CSpriteRenderer* renderer)
		{
			if (renderer->m_spGameObject.lock()->IsActive())	renderer->Draw(pDC);
		});
}