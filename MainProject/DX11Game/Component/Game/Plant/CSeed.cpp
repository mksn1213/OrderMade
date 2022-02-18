/**
*
* @file		CSeed.cpp
* @brief	種クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/17  実装開始
* @date		2021/12/14	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Plant/CSeed.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/CPlayer.h>
#include <System/Component/CRigidbody.h>
#include <Component/Game/Player/CPlayerTarget.h>

/**
* @brief	コンストラクタ
*/
CSeed::CSeed()
{

}


/**
* @brief	デストラクタ
*/
CSeed::~CSeed()
{

}


/**
* @brief	生成時
*/
void CSeed::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Item");

	// 名前設定
	obj->SetName("Seed");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Seed);

	// リジッドボディ追加
	const auto& rigidbody = obj->AddComponent<CRigidbody>().lock();
	rigidbody->SetUseGravity(true);
	rigidbody->SetUsePhysics(true);

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(5.0f, 10.0f, 10.0f));
	collider->m_pMainScript = this;
}


/**
* @brief	破棄時
*/
void CSeed::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CSeed::Update()
{

}


/**
* @brief	当たった際の処理
* @param	collider		当たり相手のコライダー
*/
void CSeed::OnCollision(std::weak_ptr<CCollider> collider)
{
	// ターゲットに選択されている場合描画を変える
	if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)
	{
		// ターゲットが既に存在していた場合終了
		const auto& taget = collider.lock()->m_spGameObject.lock()->GetComponent<CPlayerTarget>().lock();
		if (taget->IsTarget())	return;
		const auto& obj = m_spGameObject.lock();
		// 親が存在していた場合終了
		if (obj->m_spTransform.lock()->GetParent().lock())	return;
		// ターゲットの決定
		taget->TargetON();
		// シェーダー変更
		obj->SetShader(EVertexShaderKind::AssimpVS, EPixelShaderKind::AssimpTargetPS);
	}
}


/**
* @brief	行う処理があるかどうか ⇒ あれば処理を実行する
* @param	collider		相手のコライダー
* @return	bool			アクション有無
*/
bool CSeed::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// 相手オブジェクトによって処理が変わる
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----プレイヤーターゲット
	{
		// プレイヤー取得
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();

		// 親子関係を作る
		m_spTransform.lock()->GetParent().reset();
		CTransform::SetParentChildRelation(playerObj, m_spGameObject, EDirection::Front, 15.0f);
		
		// アイテムセット
		const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>();
		playerCom.lock()->SetItem(m_spGameObject);

		// プレイヤーにアクション追加
		playerObj.lock()->AddComponent<CTakeAction>();
		return true;
	}
	default:	break;
	}

	return false;
}