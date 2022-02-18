/**
*
* @file		CClayBox.cpp
* @brief	粘土箱クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Potted/CClayBox.h>
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
CClayBox::CClayBox()
{

}


/**
* @brief	デストラクタ
*/
CClayBox::~CClayBox()
{

}


/**
* @brief	生成時
*/
void CClayBox::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Stationary");

	// 名前設定
	obj->SetName("ClayBox");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ClayBox);

	// コンポーネント追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(10.0f, 10.0f, 10.0f));
	collider->m_pMainScript = this;
}


/**
* @brief	破棄時
*/
void CClayBox::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CClayBox::Update()
{

}


/**
* @brief	当たり判定
* @param	collider		相手のコライダー
*/
void CClayBox::OnCollision(std::weak_ptr<CCollider> collider)
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
bool CClayBox::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// 相手オブジェクトによって処理が変わる
	switch (collider.lock()->m_spGameObject.lock()->GetObjectID())
	{
	case EObjectType::PlayerTarget:		//-----プレイヤーターゲット
	{
		// 粘土オブジェクトを生成
		const auto& clayObj = CStageFactory::CreateGameObject(EObjectType::Clay);

		// 親子関係を作る
		const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent();
		CTransform::SetParentChildRelation(playerObj, clayObj, EDirection::Front, 15.0f);

		// アイテムセット
		const auto& playerCom = playerObj.lock()->GetComponent<CPlayer>().lock();
		playerCom->SetItem(clayObj);

		// プレイヤーにアクション追加
		playerObj.lock()->AddComponent<CTakeAction>();
		return true;
	}
	default:	break;
	}

	return false;
}