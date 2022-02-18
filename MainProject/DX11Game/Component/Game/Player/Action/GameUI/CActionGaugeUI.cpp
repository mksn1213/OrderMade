/**
*
* @file		CActionGaugeUI.cpp
* @brief	アクションゲージUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/26	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/GameUI/CActionGaugeUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>

// コンポーネント
#include <System/Renderer/CMeshRenderer.h>

/**
* @brief	コンストラクタ
*/
CActionGaugeUI::CActionGaugeUI()
{

}


/**
* @brief	デストラクタ
*/
CActionGaugeUI::~CActionGaugeUI()
{

}


/**
* @brief	生成時
*/
void CActionGaugeUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Billboard");

	// 名前設定
	obj->SetName("ActionGaugeUI");

	// コンポーネントID設定
	SetID(Script);

	m_spTransform.lock()->SetScale(Vector3(0.0f, 1.0f, 1.0f));

	// レンダラー追加
	const auto& renderer = m_spGameObject.lock()->AddComponent<CMeshRenderer>().lock();
	renderer->MakeBillboard();
	renderer->SetBaseTexture(ETexture::ActionGauge);
}


/**
* @brief	破棄時
*/
void CActionGaugeUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CActionGaugeUI::Update()
{
	// サイズ更新
	auto scale = m_spTransform.lock()->GetScale();
	scale->x += m_fIncrease/1.5f;
	m_spTransform.lock()->SetScale(scale);

	// ローカル座標更新
	m_spTransform.lock()->SetLocalPosition(EDirection::Right, m_fIncrease / 1.5f, true);
}