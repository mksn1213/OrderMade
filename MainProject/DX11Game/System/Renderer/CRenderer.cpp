/**
*
* @file		CRenderer.cpp
* @brief	描画クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	実装開始
*
*/

/** インクルード部 */
#include <System/Renderer/CRenderer.h>
#include <System/GameObject/CGameObject.h>

/**
* @brief	コンストラクタ
*/
CRenderer::CRenderer()
{
}


/**
* @brief	デストラクタ
*/
CRenderer::~CRenderer()
{

}


/**
* @brief	生成時
*/
void CRenderer::OnCreate()
{
	// トランスフォームを取得
	m_spTransform = m_spGameObject.lock()->GetComponent<CTransform>();
}


/**
* @brief	破棄時
*/
void CRenderer::OnDestroy()
{

}


/**
* @brief	更新処理
*/
void CRenderer::Update()
{

}
