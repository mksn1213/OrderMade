/**
*
* @file		CBucket.cpp
* @brief	バケツクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/17  実装開始
* @date		2021/12/17	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Water/CBucket.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Player/CPlayerTarget.h>
#include <Component/Game/Water/CWater.h>

/**
* @brief	コンストラクタ
*/
CBucket::CBucket()
	: m_bHasWater(false)
{

}


/**
* @brief	デストラクタ
*/
CBucket::~CBucket()
{

}


/**
* @brief	生成時
*/
void CBucket::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Item");

	// 名前設定
	obj->SetName("Bucket");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Bucket);

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(5.0f, 10.0f, 10.0f));
	collider->m_pMainScript = this;

	// 水メッシュの生成
	const auto& waterObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	waterObj->AddComponent<CWater>();
	waterObj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3::up() * 7.0f);
	waterObj->m_spTransform.lock()->SetScale(Vector3(3.0f, 1.0f, 3.0f));
	waterObj->SetActive(false);
	m_spWaterObj = waterObj;
}


/**
* @brief	破棄時
*/
void CBucket::OnDestroy()
{
	CScriptBase::OnDestroy();
}



/**
* @brief	更新処理
*/
void CBucket::Update()
{
	m_spWaterObj.lock()->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3::up() * 7.0f);
}


/**
* @brief	当たった際の処理
* @param	collider		当たり相手のコライダー
*/
void CBucket::OnCollision(std::weak_ptr<CCollider> collider)
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
* @details	相手がアイテムを持っていなかった場合の処理
* @param	collider		相手のコライダー
* @return	bool			アクション有無
*/
bool CBucket::ExistsProcess(std::weak_ptr<CCollider> collider)
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
	default:break;
	}

	return false;
}