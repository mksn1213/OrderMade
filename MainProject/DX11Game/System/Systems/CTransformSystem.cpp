/**
*
* @file		CTransformSystem.cpp
* @brief	トランスフォームシステムクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CTransformSystem.h>
#include <System/Component/CTransform.h>
#include <System/GameObject/CGameObject.h>
#include <algorithm>

/**
* @brief	コンストラクタ
*/
CTransformSystem::CTransformSystem()
{

}


/**
* @brief	デストラクタ
*/
CTransformSystem::~CTransformSystem()
{

}


/**
* @brief	生成時処理
*/
void CTransformSystem::OnCreate()
{

}


/**
* @brief	削除時処理
*/
void CTransformSystem::OnDestroy()
{

}


/**
* @brief	更新時処理
*/
void CTransformSystem::OnUpdate()
{
	std::for_each(m_pComponentList.begin(), m_pComponentList.end(),
		[](CTransform* transform)
		{
			// アクティブ状態かつ親オブジェクトが存在しない場合更新
			if (transform->m_spGameObject.lock()->IsActive() && !transform->GetParent().lock())	transform->Update();
		});
}