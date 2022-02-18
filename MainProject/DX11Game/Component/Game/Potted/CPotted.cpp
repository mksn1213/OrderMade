/**
*
* @file		CPotted.cpp
* @brief	鉢植えクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	実装開始
* @date		2021/12/19	コンポーネントに変更
* @date		2021/12/28	アイコンUI追加
*
*/

/** インクルード部 */
#include <Component/Game/Potted/CPotted.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Player/Action/CTakeAction.h>
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <Component/Game/Player/CPlayerTarget.h>

/**
* @brief	コンストラクタ
*/
CPotted::CPotted()
{

}


/**
* @brief	デストラクタ
*/
CPotted::~CPotted()
{

}


/**
* @brief	生成時
*/
void CPotted::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Item");

	// 名前設定
	obj->SetName("Potted");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Potted);

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(5.0f, 10.0f, 10.0f));
	collider->m_pMainScript = this;

	// アイコンUI作成
	const auto& uiObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& uiCom = uiObj->AddComponent<CIconUI>().lock();
	uiCom->SetIconTexture(ETexture::Icon_Potted);

	// 親子関係を作る
	CTransform::SetParentChildRelation(m_spGameObject, uiObj, EDirection::Up, 20.0f);
}


/**
* @brief	破棄時
*/
void CPotted::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CPotted::Update()
{

}


/**
* @brief	当たった際の処理
* @param	collider		当たり相手のコライダー
*/
void CPotted::OnCollision(std::weak_ptr<CCollider> collider)
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
bool CPotted::ExistsProcess(std::weak_ptr<CCollider> collider)
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
