/**
*
* @file		CPlayerTarget.cpp
* @brief	プレイヤーターゲットクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/20	実装開始
* @date		2021/12/03	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/CPlayerTarget.h>
#include <System/GameObject/CGameObject.h>
#include <System/CInput.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/CPlayer.h>
#include <System/Component/CRigidbody.h>

/** マクロ定義 */
namespace
{
	const float SUBTRACT = 0.6f;
}

/**
* @brief	コンストラクタ
*/
CPlayerTarget::CPlayerTarget()
	: m_bIsTarget(false)
{

}


/**
* @brief	デストラクタ
*/
CPlayerTarget::~CPlayerTarget()
{

}



/**
* @brief	生成時
*/
void CPlayerTarget::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Target");
	// 名前設定
	obj->SetName("PlayerTarget");
	// コンポーネントID設定
	SetID(Script);
	// オブジェクトID設定
	obj->SetObjectID(EObjectType::PlayerTarget);
	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(8.0f, 5.0f, 6.0f));
	collider->m_pMainScript = this;
	// 当たり判定元フラグON
	collider->SetCollisionFlag(true);
}


/**
* @brief	破棄時
*/
void CPlayerTarget::OnDestroy()
{
	CScriptBase::OnDestroy();
}



/**
* @brief	更新処理
*/
void CPlayerTarget::Update()
{
	// アイテムを持っている場合
	if (m_spPlayer.lock()->GetItemFlag())
	{
		if (CInput::GetKeyTrigger(VK_L))
		{
			// オブジェクトを手放す
			const auto& playerTrans = m_spTransform.lock()->GetParent().lock()->m_spTransform.lock();
			playerTrans->ReleaseRelationship(m_spPlayer.lock()->GetItem());
			// アイテムのリリース
			m_spPlayer.lock()->ReleaseItem();
		}
	}

	// ターゲットをリセット
	m_bIsTarget = false;
}


/**
* @brief	当たった時の処理
* @param	collider		相手のコライダー
*/
void CPlayerTarget::OnCollision(std::weak_ptr<CCollider> collider)
{
	// プレイヤーがアクション中の場合終了
	if (m_spPlayer.lock()->IsAction())	return;

	// ボタンが押されたときのみ処理を行う
	if (CInput::GetKeyTrigger(VK_J))
	{
		// 相手オブジェクトに親がいた場合は判定を取らない
		if (collider.lock()->m_spTransform.lock()->GetParent().lock())	return;

		// アイテムを持っていた場合
		if (m_spPlayer.lock()->GetItemFlag())
		{
			// 実行する処理があるか判断
			if (collider.lock()->m_pMainScript->ExistsProcess(m_spGameObject.lock()->GetComponent<CCollider>(), m_spPlayer.lock()->GetItem()))
			{
				// アクションON
				m_spPlayer.lock()->SetActionFlag(true);
				// プレイヤーを減速
				const auto& rb = m_spPlayer.lock()->m_spGameObject.lock()->GetComponent<CRigidbody>().lock();
				rb->SubForce(SUBTRACT);
			}
		}
		// アイテムを持っていなかった場合
		else
		{
			// 実行する処理があるか判断
			if (collider.lock()->m_pMainScript->ExistsProcess(m_spGameObject.lock()->GetComponent<CCollider>()))
			{
				// アクションON
				m_spPlayer.lock()->SetActionFlag(true);
				// プレイヤーの減速
				const auto& rb = m_spPlayer.lock()->m_spGameObject.lock()->GetComponent<CRigidbody>().lock();
				rb->SubForce(SUBTRACT);
			}
		}
	}
}