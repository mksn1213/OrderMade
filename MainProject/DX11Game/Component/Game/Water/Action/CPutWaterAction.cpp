/**
*
* @file		CPutWaterAction.cpp
* @brief	水を入れるアクションクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/06	実装開始
* @date		2021/12/18	コンポーネントに変更
* @date		2021/12/28	アクションゲージ追加
*
*/

/** インクルード部 */
#include <Component/Game/Water/Action/CPutWaterAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Sound/CSound.h>
#include <System/Effect/CEffectManager.h>

// コンポーネント
#include <Component/Game/Water/CWell.h>
#include <Component/Game/Water/CBucket.h>

/** マクロ定義 */
namespace
{
	const int	TIME = 180;						// アクション時間
	const int	SE_IN_TIME = TIME - TIME / 4;	// 入りSE再生タイミング
	const int	SE_OUT_TIME = TIME / 2 / 2;		// 出SE再生タイミング
	const float	PUT_SPEED = 0.4f;				// ローカル座標移動速度
}

/**
* @brief	コンストラクタ
*/
CPutWaterAction::CPutWaterAction()
	: m_bIsWater(false)
{
	
}


/**
* @brief	デストラクタ
*/
CPutWaterAction::~CPutWaterAction()
{

}


/**
* @brief	生成時
*/
void CPutWaterAction::OnCreate()
{
	// スクリプト初期化
	CScriptBase::OnCreate();
	// コンポーネントID設定
	SetID(EComponentType::Action);
	// タイマーの生成
	m_pTimer = new CTimer(TIME);
	// アクションゲージUI生成
	CreateActionGauge(TIME, EDirection::Up, 30.0f, EDirection::Front, 10.0f);
	// SEボリュームセット
	SOUND_MANAGER->SetVolume(SE_WELL_IN, 4.0f);
	SOUND_MANAGER->SetVolume(SE_WELL_OUT, 4.0f);
	SOUND_MANAGER->SetVolume(SE_WELL_PULLEY, 0.5f);
	SOUND_MANAGER->Play(SE_WELL_PULLEY);
}


/**
* @brief	更新
*/
void CPutWaterAction::Update()
{
	// 水をくむ演出処理
	if (m_pTimer->GetTime() >= TIME / 2)
	{
		m_spTargetItem.lock()->m_spTransform.lock()->SetLocalPosition(EDirection::Down, PUT_SPEED, true);
		// SE再生 + エフェクト再生
		if (m_pTimer->GetTime() == SE_IN_TIME)
		{
			SOUND_MANAGER->Play(SE_WELL_IN);
			auto pos = m_spTransform.lock()->GetPosition();
			pos->y += 10.0f;
			EFFECT_MANAGER->Play(EEffectType::Water, pos);
		}
	}
	else
	{
		// 一度だけ実行
		// 水メッシュをアクティブ化
		if (!m_bIsWater)
		{
			m_spTargetItem.lock()->GetComponent<CBucket>().lock()->m_spWaterObj.lock()->SetActive(true);
			m_bIsWater = true;
		}
		m_spTargetItem.lock()->m_spTransform.lock()->SetLocalPosition(EDirection::Up, PUT_SPEED, true);
		// SE再生
		if (m_pTimer->GetTime() == SE_OUT_TIME)
		{
			SOUND_MANAGER->Play(SE_WELL_OUT);
			auto pos = m_spTransform.lock()->GetPosition();
			pos->y += 10.0f;
			EFFECT_MANAGER->Play(EEffectType::Water, pos);
		}
	}

	// 更新出来なければ終了
	if (!IsUpdate())
	{
		// アクション終了時の処理
		EndProcess();
		// アクションフラグOFF
		m_spGameObject.lock()->GetComponent<CWell>().lock()->SetActionFlag(false);
		// SE停止
		SOUND_MANAGER->Stop(SE_WELL_PULLEY);
		return;
	}
}


/**
* @brief	アクション終了時の処理
*/
void CPutWaterAction::EndProcess()
{
	// 水フラグON
	m_spTargetItem.lock()->GetComponent<CBucket>().lock()->SetWaterFlag(true);
	// アクションゲージ削除
	DeleteActionGauge();
}
