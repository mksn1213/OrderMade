/**
*
* @file		CGiveWaterAction.cpp
* @brief	水を与えるアクションクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/07	実装開始
* @date		2021/12/18	コンポーネントに変更
* @date		2021/12/28	アクションゲージ追加
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CGiveWaterAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Water/CBucket.h>
#include <System/Sound/CSound.h>
#include <System/Utility/Search.h>

// コンポーネント
#include <Component/Game/Soil/Action/CGrowAction.h>
#include <Component/Game/Soil/CSoil.h>

/** マクロ定義 */
namespace
{
	const int TIME = 60;				// アクション
	const int SE_PLAY_INTERVAL = 20;	// SE再生間隔
}

/**
* @brief	コンストラクタ
*/
CGiveWaterAction::CGiveWaterAction()
	: m_nFrame(SE_PLAY_INTERVAL)
{

}


/**
* @brief	デストラクタ
*/
CGiveWaterAction::~CGiveWaterAction()
{

}


/**
* @brief	生成時
*/
void CGiveWaterAction::OnCreate()
{
	// スクリプト初期化
	CScriptBase::OnCreate();
	// コンポーネントID設定
	SetID(EComponentType::Action);
	// タイマー生成
	m_pTimer = new CTimer(TIME);
	// アクションゲージUI生成
	CreateActionGauge(TIME, EDirection::Up, 15.0f);
	// SEボリュームセット
	SOUND_MANAGER->SetVolume(SE_GIVEWATER, 2.0f);
}


/**
* @brief	更新処理
*/
void CGiveWaterAction::Update()
{
	// SE再生
	if (m_nFrame > SE_PLAY_INTERVAL)
	{
		SOUND_MANAGER->Play(SE_GIVEWATER);
		m_nFrame = 0;
	}
	m_nFrame++;

	// 更新出来なければ終了
	if (!IsUpdate())
	{
		// アクション終了時の処理
		EndProcess();
		// アクションフラグOFF
		m_spGameObject.lock()->GetComponent<CPlayer>().lock()->SetActionFlag(false);
	}
}


/**
* @brief	アクション終了時の処理
*/
void CGiveWaterAction::EndProcess()
{
	// 水フラグOFF
	const auto& bucket = m_spTargetItem.lock()->GetComponent<CBucket>().lock();
	bucket->SetWaterFlag(false);
	// 水メッシュ非アクティブ化
	bucket->m_spWaterObj.lock()->SetActive(false);

	// 成長アクション追加
	const auto& action = m_spTargetObject.lock()->AddComponent<CGrowAction>();
	const auto& childList = m_spTargetObject.lock()->m_spTransform.lock()->GetChildList();
	const auto& plantObj = SearchExistsList(childList, "Item");
	action.lock()->SetTarget(m_spTargetObject, plantObj);
	m_spTargetObject.lock()->GetComponent<CSoil>().lock()->SetActionFlag(true);

	// アクションゲージ削除
	DeleteActionGauge();
}
