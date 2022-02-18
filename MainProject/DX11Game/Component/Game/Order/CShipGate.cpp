/**
*
* @file		CShipGate.cpp
* @brief	出荷ゲートクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Order/CShipGate.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Order/COrderManager.h>
#include <System/Utility/Search.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Effect/CEffectManager.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CPutAction.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Order/CShipTruck.h>
#include <Component/Game/Player/CPlayerTarget.h>

/**
* @brief	コンストラクタ
*/
CShipGate::CShipGate()
{

}


/**
* @brief	デストラクタ
*/
CShipGate::~CShipGate()
{

}


/**
* @brief	生成時
*/
void CShipGate::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Stationary");

	// 名前の設定
	obj->SetName("ShipGate");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ShipGate);

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(40.0f, 40.0f, 10.0f), Vector3(0.0f, 20.0f, 0.0f));
	collider->m_pMainScript = this;

	// 出荷トラックの生成
	const auto& truckObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	truckObj->AddComponent<CShipTruck>();
	truckObj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3(0.0f, 0.0f, 30.0f));
	truckObj->m_spTransform.lock()->SetRotation(Vector3(0.0f, 270.0f, 0.0f));
	m_spTruckList.push_back(truckObj);
}


/**
* @brief	破棄時
*/
void CShipGate::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CShipGate::Update()
{
	if (m_spTruckList.begin()->lock()->GetComponent<CShipTruck>().lock()->IsFin())
	{
		auto obj = m_spTruckList.begin()->lock();
		m_spTruckList.erase(m_spTruckList.begin());
		obj->Destroy();
	}
}


/**
* @brief	当たり判定
* @param	collider		相手のコライダー
*/
void CShipGate::OnCollision(std::weak_ptr<CCollider> collider)
{
	// ターゲットに選択されている場合描画を変える
	if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)
	{
		// ターゲットが既に存在していた場合終了
		const auto& target = collider.lock()->m_spGameObject.lock()->GetComponent<CPlayerTarget>().lock();
		if (target->IsTarget())	return;
		// ターゲットの決定
		target->TargetON();
		const auto& obj = m_spGameObject.lock();
		// シェーダー変更
		obj->SetShader(EVertexShaderKind::AssimpVS, EPixelShaderKind::AssimpTargetPS);
	}
}


/**
* @brief	行う処理があるかどうか ⇒ あれば処理を実行する
* @details	相手がアイテムを持っている場合の処理
* @param	collider		相手のコライダー
* @param	item			アイテムのゲームオブジェクト
* @return	bool			処理の有無
*/
bool CShipGate::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	// 持っているアイテムによって処理を変える
	switch (itemObj.lock()->GetObjectID())
	{
	case EObjectType::Sprout:	//-----芽
	case EObjectType::Flower:	//-----花
	{
		// 注文の照合
		// 一致しなければ終了
		if (!ORDER_MANAGER->CheckOrder(itemObj))	return false;
		// エフェクト再生
		EFFECT_MANAGER->Play(EEffectType::Ship, m_spTransform.lock()->GetPosition() + Vector3::up() * 20.0f);
		// プレイヤーにアクション追加
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		playerObj.lock()->AddComponent<CPutAction>();
		// アイテムのリリース
		playerObj.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();
		// 親子関係の解除
		playerObj.lock()->m_spTransform.lock()->ReleaseRelationship(itemObj);
		// 親子関係を作る
		CTransform::SetParentChildRelation(m_spTruckList.back().lock(), itemObj, EDirection::Up, 10.0f, EDirection::Back, 10.0f);
		// アイコンUI削除
		auto childList = itemObj.lock()->m_spTransform.lock()->GetChildList();
		for (auto it = childList.begin(); it != childList.end();)
		{
			auto obj = it->lock();
			it = childList.erase(it);
			obj->Destroy();
		}
		// 出荷フラグを立てる
		const auto& com = m_spTruckList.back().lock()->GetComponent<CShipTruck>().lock();
		com->SetShipFlag();
		// 新しく出荷トラックを生成
		const auto& truckObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
		const auto& truckCom = truckObj->AddComponent<CShipTruck>().lock();
		truckObj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3(-300.0f, 0.0f, 30.0f));
		truckObj->m_spTransform.lock()->SetRotation(Vector3(0.0f, -90.0f, 0.0f));
		m_spTruckList.push_back(truckObj);
		truckCom->SetMoveFlag(m_spTransform.lock()->GetPosition());

		return true;
	}
	case EObjectType::Potted:	//-----鉢植え
	{
		// 鉢植えに何も入っていなければ終了
		auto childList = itemObj.lock()->m_spTransform.lock()->GetChildList();
		const auto& plantObj = SearchExistsList(childList, "Item").lock();
		if (!plantObj)	return false;

		// 注文の照合
		// 一致しなければ終了
		if (!ORDER_MANAGER->CheckOrder(itemObj))	return false;
		// エフェクト再生
		EFFECT_MANAGER->Play(EEffectType::Ship, m_spTransform.lock()->GetPosition() + Vector3::up() * 20.0f);
		// プレイヤーにアクション追加
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		playerObj.lock()->AddComponent<CPutAction>();
		// アイテムのリリース
		playerObj.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();
		// 親子関係の解除
		playerObj.lock()->m_spTransform.lock()->ReleaseRelationship(itemObj);
		// 親子関係を作る
		CTransform::SetParentChildRelation(m_spTruckList.back().lock(), itemObj, EDirection::Up, 10.0f, EDirection::Back, 10.0f);
		// アイコンUI削除
		for (auto it = childList.begin(); it != childList.end();)
		{
			if (it->lock()->GetTag() == "Billboard")
			{
				auto obj = it->lock();
				it = childList.erase(it);
				obj->Destroy();
			}
			else
			{
				++it;
			}
		}

		// 出荷フラグを立てる
		const auto& com = m_spTruckList.back().lock()->GetComponent<CShipTruck>().lock();
		com->SetShipFlag();
		// 新しく出荷トラックを生成
		const auto& truckObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
		const auto& truckCom = truckObj->AddComponent<CShipTruck>().lock();
		truckObj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3(-300.0f, 0.0f, 30.0f));
		truckObj->m_spTransform.lock()->SetRotation(Vector3(0.0f, -90.0f, 0.0f));
		m_spTruckList.push_back(truckObj);
		truckCom->SetMoveFlag(m_spTransform.lock()->GetPosition());

		return true;
	}
	default:break;
	}

	return false;
}
