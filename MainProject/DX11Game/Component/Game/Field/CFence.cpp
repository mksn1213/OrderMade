/**
*
* @file		CFence.cpp
* @brief	柵クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/01/11	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/Field/CFence.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>

/**
* @brief	コンストラクタ
*/
CFence::CFence()
{

}


/**
* @brief	デストラクタ
*/
CFence::~CFence()
{

}


/**
* @brief	生成時
*/
void CFence::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Stationary");

	// 名前設定
	obj->SetName("Fence");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Fence1);
	
	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(40.0f, 20.0f, 10.0f), Vector3::up()*10.0f);
	collider->m_pMainScript = this;
}


/**
* @brief	破棄時
*/
void CFence::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CFence::Update()
{

}