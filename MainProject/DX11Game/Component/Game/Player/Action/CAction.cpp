/**
*
* @file		CAction.cpp
* @brief	アクションベースクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/26	実装開始
* @date		2021/12/16	コンポーネントに変更
* @date		2021/12/28	アクションゲージUI生成処理作成
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CAction.h>
#include <System/CTimer.h>
#include <System/Defines.h>

#include <System/GameObject/CGameObjectManager.h>
#include <Component/Game/Player/Action/GameUI/CActionGaugeUI.h>
#include <Component/Game/Player/Action/GameUI/CActionGaugeBaseUI.h>

/** 静的メンバ */
const EComponentType CAction::comID = EComponentType::Action;

/**
* @brief	コンストラクタ
*/
CAction::CAction()
	: m_pTimer(nullptr)
{

}


/**
* @brief	デストラクタ
*/
CAction::~CAction()
{
	SAFE_DELETE(m_pTimer);
}


/**
* @brief	更新出来るか
* @return	bool	更新の可否(true/更新可能 , false/終了)
*/
bool CAction::IsUpdate()
{
	// タイマーの更新
	if (!m_pTimer->Update())	return false;
	return true;
}


/**
* @brief	アクションゲージUI生成
* @param	time		アクションにかかる時間
* @param	dir			生成する方向
* @param	distance	生成する距離
*/
void CAction::CreateActionGauge(int time, EDirection dir, float distance, EDirection dir2, float distance2)
{
	// アクションゲージUIの生成
	m_spActionGauge = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& gaugeBaseCom = m_spActionGauge.lock()->AddComponent<CActionGaugeBaseUI>().lock();

	const auto& gaugeObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& gaugeCom = gaugeObj->AddComponent<CActionGaugeUI>().lock();
	gaugeCom->SetActionTime(time);

	// 親子関係を作る
	CTransform::SetParentChildRelation(m_spGameObject, m_spActionGauge, dir, distance, dir2, distance2);
	CTransform::SetParentChildRelation(m_spActionGauge, gaugeObj, EDirection::Front, 0.05f,EDirection::Left,10.0f/1.5f);
}


/**
* @brief	アクションゲージUI削除
*/
void CAction::DeleteActionGauge()
{
	m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(m_spActionGauge);
	m_spActionGauge.lock()->Destroy();
}