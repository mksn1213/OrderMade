/**
*
* @file		CWall.cpp
* @brief	壁クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/10	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Wall/CWall.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>


/**
* @brief	コンストラクタ
*/
CWall::CWall()
{

}


/**
* @brief	デストラクタ
*/
CWall::~CWall()
{

}


/**
* @brief	生成時
*/
void CWall::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Stationary");

	// 名前設定
	obj->SetName("Wall");

	// コンポーネントID設定
	SetID(Script);

	// コンポーネント追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(20.0f, 20.0f, 20.0f));
	collider->m_pMainScript = this;

	// モデルのセット
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Wall);
}


/**
* @brief	破棄時
*/
void CWall::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CWall::Update()
{

}


/**
* @brief	当たり判定
* @param	collider		相手のコライダー
*/
void CWall::OnCollision(std::weak_ptr<CCollider> collider)
{

}