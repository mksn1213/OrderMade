/**
*
* @file		CTrimShapeAction.cpp
* @brief	形状を整えるアクションクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	実装開始
* @date		2021/12/19	コンポーネントに変更
* @date		2021/12/28	アクションゲージ追加
*
*/

/** インクルード部 */
#include <Component/Game/Potted/Action/CTrimShapeAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Sound/CSound.h>

// コンポーネント
#include <Component/Game/Potted/CPotteryWheel.h>
#include <Component/Game/Potted/CClay.h>
#include <System/Renderer/CModelRenderer.h>

/** マクロ定義 */
namespace
{
	const int TIME = 240;				// アクション時間
	const int SE_PLAY_INTERVAL = 30;	// SE再生間隔
}

/**
* @brief	コンストラクタ
*/
CTrimShapeAction::CTrimShapeAction()
	: m_nFrame(SE_PLAY_INTERVAL)
{

}


/**
* @brief	デストラクタ
*/
CTrimShapeAction::~CTrimShapeAction()
{

}


/**
* @brief	生成時
*/
void CTrimShapeAction::OnCreate()
{
	// スクリプト初期化
	CScriptBase::OnCreate();
	// コンポーネントID設定
	SetID(EComponentType::Action);
	// タイマーの生成
	m_pTimer = new CTimer(TIME);
	// アクションゲージUI生成
	CreateActionGauge(TIME, EDirection::Up, 30.0f);
	// SEボリュームセット
	SOUND_MANAGER->SetVolume(SE_TRIM, 5.0f);
}


/**
* @brief	更新
*/
void CTrimShapeAction::Update()
{
	// SE再生
	if (m_nFrame > SE_PLAY_INTERVAL)
	{
		SOUND_MANAGER->Play(SE_TRIM);
		m_nFrame = 0;
	}
	m_nFrame++;

	if (m_pTimer->GetTime() == TIME / 2)
	{
		m_spTargetItem.lock()->GetComponent<CModelRenderer>().lock()->SetModel(EModelType::TrimClay);
	}

	// 更新出来なければ終了
	if (!IsUpdate())
	{
		// アクション終了時の処理
		EndProcess();
		// アクションフラグOFF
		m_spGameObject.lock()->GetComponent<CPotteryWheel>().lock()->SetActionFlag(false);
		return;
	}
}


/**
* @brief	アクション終了時の処理
*/
void CTrimShapeAction::EndProcess()
{
	// 加工フラグON
	m_spTargetItem.lock()->GetComponent<CClay>().lock()->SetProcessedFlag(true);
	
	// アクションゲージ削除
	DeleteActionGauge();
}
