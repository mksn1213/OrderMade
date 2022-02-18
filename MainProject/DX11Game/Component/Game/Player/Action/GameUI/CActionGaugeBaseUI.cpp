/**
*
* @file		CActionGaugeBaseUI.cpp
* @brief	アクションゲージベースUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/26	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/GameUI/CActionGaugeBaseUI.h>
#include <System/GameObject/CGameObject.h>

// コンポーネント
#include <System/Renderer/CMeshRenderer.h>

/**
* @brief	コンストラクタ
*/
CActionGaugeBaseUI::CActionGaugeBaseUI()
{

}


/**
* @brief	デストラクタ
*/
CActionGaugeBaseUI::~CActionGaugeBaseUI()
{

}


/**
* @brief	生成時
*/
void CActionGaugeBaseUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Billboard");

	// 名前設定
	obj->SetName("ActionGaugeBaseUI");

	// コンポーネントID設定
	SetID(Script);

	m_spTransform.lock()->SetScale(Vector3(11.0f/1.5f, 1.5f, 1.0f));

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CMeshRenderer>().lock();
	renderer->MakeBillboard();
	renderer->SetBaseTexture(ETexture::ActionGaugeBase);
}


/**
* @brief	破棄時
*/
void CActionGaugeBaseUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CActionGaugeBaseUI::Update()
{

}