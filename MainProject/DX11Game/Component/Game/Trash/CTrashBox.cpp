/**
*
* @file		CTrashBox.cpp
* @brief	ごみ箱クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/30	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/Trash/CTrashBox.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CPutAction.h>
#include <Component/Game/Player/CPlayer.h>

/**
* @brief	コンストラクタ
*/
CTrashBox::CTrashBox()
{

}


/**
* @brief	デストラクタ
*/
CTrashBox::~CTrashBox()
{

}


/**
* @brief	生成時
*/
void CTrashBox::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Stationary");

	// 名前設定
	obj->SetName("TrashBox");

	// コンポーネントID設定
	SetID(Script);

	// コンポーネント追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(20.0f, 20.0f, 20.0f));
	collider->m_pMainScript = this;

	// モデルのセット
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::TrashBox);
}


/**
* @brief	破棄時
*/
void CTrashBox::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CTrashBox::Update()
{

}


/**
* @brief	当たり判定
* @param	collider		相手のコライダー
*/
void CTrashBox::OnCollision(std::weak_ptr<CCollider> collider)
{

}


/**
* @brief	行う処理があるかどうか ⇒ あれば処理を実行する
* @details	相手がアイテムを持っている場合の処理
* @param	collider		相手のコライダー
* @param	item			アイテムのゲームオブジェクト
* @return	bool			処理の有無
*/
bool CTrashBox::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	// バケツだった場合終了
	if (itemObj.lock()->GetObjectID() == EObjectType::Bucket)	return false;

	// アイテムのリリース
	const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent().lock();
	playerObj->GetComponent<CPlayer>().lock()->ReleaseItem();

	itemObj.lock()->Destroy();

	return false;
}
