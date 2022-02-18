/**
*
* @file		CSeedBox.cpp
* @brief	種箱クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Plant/CSeedBox.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Player/CPlayerTarget.h>

// オブジェクト生成用
#include <System/Factory/CStageFactory.h>

/**
* @brief	コンストラクタ
*/
CSeedBox::CSeedBox()
{

}


/**
* @brief	デストラクタ
*/
CSeedBox::~CSeedBox()
{

}


/**
* @brief	生成時
*/
void CSeedBox::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Stationary");
	// 名前設定
	obj->SetName("SeedBox");
	// コンポーネントID設定
	SetID(Script);
	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::SeedBox);
	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(25.0f, 20.0f, 25.0f));
	collider->m_pMainScript = this;
}


/**
* @brief	破棄時
*/
void CSeedBox::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CSeedBox::Update()
{

}


/**
* @brief	当たった時の処理
* @param	collider		相手のコライダー
*/
void CSeedBox::OnCollision(std::weak_ptr<CCollider> collider)
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
* @param	collider		相手のコライダー
* @return	bool			アクションの有無
*/
bool CSeedBox::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// 相手オブジェクトによって処理が変わる
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----プレイヤーターゲット
	{
		// 種オブジェクトを生成
		const auto& seedObj = CStageFactory::CreateGameObject(EObjectType::Seed);

		// 親子関係を作る
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		CTransform::SetParentChildRelation(playerObj, seedObj, EDirection::Front, 15.0f);

		// アイテムセット
		const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>().lock();
		playerCom->SetItem(seedObj);
		
		// プレイヤーにアクション追加
		playerObj.lock()->AddComponent<CTakeAction>();
		return true;
	}
	default:	break;
	}

	return false;
}