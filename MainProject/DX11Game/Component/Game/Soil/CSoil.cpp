/**
*
* @file		CSoil.cpp
* @brief	土クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Soil/CSoil.h>
#include <System/GameObject/CGameObject.h>
#include <System/Utility/Search.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CPlantAction.h>
#include <Component/Game/Player/Action/CGiveWaterAction.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/Action/CPutAction.h>
#include <Component/Game/Water/CBucket.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <Component/Game/Player/CPlayerTarget.h>

/** マクロ定義 */
namespace
{
	// モデルサイズ
	const Vector3 MODEL_SCALE = Vector3(18.0f, 5.0f, 18.0f);
}

/**
* @brief	コンストラクタ
*/
CSoil::CSoil()
	: m_bIsAction(false)
	, m_bOldIsAction(false)
{

}


/**
* @brief	デストラクタ
*/
CSoil::~CSoil()
{

}


/**
* @brief	生成時
*/
void CSoil::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Stationary");

	// 名前設定
	obj->SetName("Soil");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Soil);

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, MODEL_SCALE);
	collider->m_pMainScript = this;
}


/**
* @brief	破棄時
*/
void CSoil::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CSoil::Update()
{
	if (m_bOldIsAction && !m_bIsAction)
	{
		m_spGameObject.lock()->RemoveComponent<CAction>();
		m_bOldIsAction = m_bIsAction;
	}

	if (m_bIsAction)
	{
		m_bOldIsAction = m_bIsAction;
	}
}


/**
* @brief	当たり判定
* @param	collider		相手のコライダー
*/
void CSoil::OnCollision(std::weak_ptr<CCollider> collider)
{
	// ターゲットに選択されている場合描画を変える
	if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)
	{
		// ターゲットが既に存在していた場合終了
		const auto& taget = collider.lock()->m_spGameObject.lock()->GetComponent<CPlayerTarget>().lock();
		if (taget->IsTarget())	return;
		// ターゲットの決定
		taget->TargetON();
		const auto& obj = m_spGameObject.lock();
		// シェーダー変更
		obj->SetShader(EVertexShaderKind::AssimpVS, EPixelShaderKind::AssimpTargetPS);
	}
}


/**
* @brief	行う処理があるかどうか ⇒ あれば処理を実行する
* @details	相手がアイテムを持っていなかった場合の処理
* @param	collider		相手のコライダー
* @return	bool			アクションの有無
*/
bool CSoil::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// アクション中だった場合終了
	if (m_bIsAction)	return false;

	// 当たっている相手によって処理を変える
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----プレイヤーターゲット
	{
		const auto& childList = m_spTransform.lock()->GetChildList();

		// 子オブジェクトにアイテムが存在しない場合終了
		const auto& itemObj = SearchExistsList(childList, "Item");
		if (childList.size() == 0 || !itemObj.lock())	return false;

		// 子オブジェクトに肥料が存在している場合アイコン移動
		const auto& fertilizerObj = SearchExistsList(childList, "SupportItem").lock();
		if (fertilizerObj)
		{
			itemObj.lock()->m_spTransform.lock()->ReplaceChild(fertilizerObj, false);
		}

		// プレイヤー取得
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();

		// 親子関係の解除
		m_spTransform.lock()->ReleaseRelationship(itemObj);

		// 親子関係を作る
		CTransform::SetParentChildRelation(playerObj, itemObj, EDirection::Front, 15.0f);

		// アイテムセット
		const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>().lock();
		playerCom->SetItem(itemObj);

		// プレイヤーにアクション追加
		playerObj.lock()->AddComponent<CTakeAction>();
		return true;
	}
	default:	break;
	}
	return false;
}


/**
* @brief	行う処理があるかどうか ⇒ あれば処理を実行する
* @details	相手がアイテムを持っている場合の処理
* @param	collider		相手のコライダー
* @param	item			アイテムのゲームオブジェクト
* @return	bool			処理の有無
*/
bool CSoil::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	// アクション中だった場合終了
	if (m_bIsAction)	return false;

	const auto& childList = m_spTransform.lock()->GetChildList();

	// 持っているアイテムによって処理を変える
	switch (itemObj.lock()->GetObjectID())
	{
	case EObjectType::Seed:		//-----種
		// 子オブジェクトがなかった場合
		if (childList.size() == 0)
		{
			// プレイヤーにアクション追加
			const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
			const auto& playerAction = playerObj.lock()->AddComponent<CPlantAction>();
			playerAction.lock()->SetTarget(m_spGameObject, itemObj);
			return true;
		}
		// 肥料オブジェクトのみ存在している場合
		else if (childList.size() == 1 && SearchExistsList(childList, "SupportItem").lock())
		{
			// プレイヤーにアクション追加
			const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
			const auto& playerAction = playerObj.lock()->AddComponent<CPlantAction>();
			playerAction.lock()->SetTarget(m_spGameObject, itemObj);
			return true;
		}
		return false;

	case EObjectType::Bucket:	//-----バケツ
		// 子オブジェクトがあれば実行
		if (childList.size() > 0)
		{
			// 指定のオブジェクトが存在していた場合
			const auto& plantObj = SearchExistsList(childList, "Item");
			if (plantObj.lock())
			{
				// オブジェクトが成長済みだった場合終了
				if (plantObj.lock()->GetObjectID() == EObjectType::Flower)		return false;

				// 水が入っていた場合
				if (itemObj.lock()->GetComponent<CBucket>().lock()->GetWaterFlag())
				{
					// プレイヤーにアクション追加
					const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
					const auto& playerAction = playerObj.lock()->AddComponent<CGiveWaterAction>();
					playerAction.lock()->SetTarget(m_spGameObject, itemObj);
					return true;
				}
			}
		}
		return false;

	case EObjectType::Potted:	//-----鉢植え
		// 既に鉢植えにオブジェクトが入っていた場合終了(1になっているのは生成時にUIアイコンを子としてもっているため)
		if (itemObj.lock()->m_spTransform.lock()->GetChildList().size() > 1)	return false;

		// 子オブジェクトがなかった場合終了
		if (childList.size() == 0)	return false;
		// 子オブジェクトが存在している場合
		else
		{
			// 指定のオブジェクトが存在していた場合
			const auto& plantObj = SearchExistsList(childList, "Item").lock();
			if (plantObj)
			{
				// 種オブジェクトだった場合終了
				if (plantObj->GetObjectID() == EObjectType::Seed)	return false;

				// 肥料があった場合
				const auto& fertilizerObj = SearchExistsList(childList, "SupportItem").lock();
				if (fertilizerObj)
				{
					plantObj->m_spTransform.lock()->ReplaceChild(fertilizerObj, false);
					const auto& plantChild = plantObj->m_spTransform.lock()->GetChildList();
					for (auto it = plantChild.begin(); it != plantChild.end(); ++it)
					{
						it->lock()->GetComponent<CIconUI>().lock()->MoveON(-5.0f);
					}
				}

				// 子オブジェクトを取り替える
				plantObj->m_spTransform.lock()->ReplaceChildAll(itemObj);

				// 親子関係の解除
				m_spTransform.lock()->ReleaseRelationship(plantObj);

				// 親子関係を作る
				CTransform::SetParentChildRelation(itemObj, plantObj, EDirection::Up, 0.0f);

				// プレイヤーにアクション追加
				const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
				playerObj.lock()->AddComponent<CTakeAction>();
				return true;
			}
		}
		 return false;
	case EObjectType::FertilizerC:	//-----肥料
	case EObjectType::FertilizerM:
	case EObjectType::FertilizerY:
		// 子オブジェクトがあった場合
		if (childList.size() > 0)
		{
			// 既に肥料が存在していた場合終了
			if (SearchExistsList(childList, "SupportItem").lock())		return false;

			// 子オブジェクトが成長済みだった場合終了
			const auto& plantObj = SearchExistsList(childList, "Item");
			if (!plantObj.lock() || plantObj.lock()->GetObjectID() == EObjectType::Flower)	return false;

			// プレイヤーにアクション追加
			const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
			const auto& playerAction = playerObj.lock()->AddComponent<CPutAction>();
			playerAction.lock()->SetTarget(playerObj, itemObj);

			// アイテムのリリース
			playerObj.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();

			// 親子関係を解除
			playerObj.lock()->m_spTransform.lock()->ReleaseRelationship(itemObj);

			if (plantObj.lock()->GetObjectID() == EObjectType::Sprout)
			{
				// 子オブジェクトを取り替える
				itemObj.lock()->m_spTransform.lock()->ReplaceChildAll(plantObj);
			}

			// 親子関係を作る
			CTransform::SetParentChildRelation(m_spGameObject, itemObj, EDirection::Up, 0.0f);
		}
		// 子オブジェクトがなかった場合
		else
		{
			// プレイヤーにアクション追加
			const auto& playerObj = itemObj.lock()->m_spTransform.lock()->GetParent();
			const auto& playerAction = playerObj.lock()->AddComponent<CPutAction>();
			playerAction.lock()->SetTarget(playerObj, itemObj);

			// アイテムのリリース
			playerObj.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();

			// 親子関係を解除
			playerObj.lock()->m_spTransform.lock()->ReleaseRelationship(itemObj);

			// 親子関係を作る
			CTransform::SetParentChildRelation(m_spGameObject, itemObj, EDirection::Up, 0.0f);
		}
		return true;
	default:break;
	}

	return false;
}
