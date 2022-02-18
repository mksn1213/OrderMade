/**
*
* @file		CSelectGateUI.cpp
* @brief	セレクトゲートUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	実装開始
*
*/

/** インクルード部 */
#include <Component/Select/CSelectGateUI.h>
#include <System/GameObject/CGameObject.h>

/**
* @brief	コンストラクタ
*/
CSelectGateUI::CSelectGateUI()
{

}


/**
* @brief	デストラクタ
*/
CSelectGateUI::~CSelectGateUI()
{

}


/**
* @brief	生成時
*/
void CSelectGateUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Billboard");

	// 名前設定
	obj->SetName("SelectGateUI");

	// コンポーネントID設定
	SetID(Script);

	m_spTransform.lock()->SetScale(Vector3(20.0f, 10.0f, 1.0f));

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CMeshRenderer>().lock();
	renderer->MakeBillboard();
	m_spRenderer = renderer;
}


/**
* @brief	破棄時
*/
void CSelectGateUI::OnDestroy()
{

}


/**
* @brief	更新処理
*/
void CSelectGateUI::Update()
{

}


/**
* @brief	テクスチャセット
* @param	type	ゲートタイプ
*/
void CSelectGateUI::SetTexture(CSelectGate::EGateType type)
{
	switch (type)
	{
	case CSelectGate::GateTitle:		m_spRenderer.lock()->SetBaseTexture(ETexture::GateTitle);		break;
	case CSelectGate::GateTutorial:		m_spRenderer.lock()->SetBaseTexture(ETexture::GateTutorial);	break;
	case CSelectGate::GateGame1:		m_spRenderer.lock()->SetBaseTexture(ETexture::GateGame);		break;
	default:																							break;
	}
}
