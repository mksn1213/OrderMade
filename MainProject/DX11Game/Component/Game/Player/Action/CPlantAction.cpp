/**
*
* @file		CPlantAction.cpp
* @brief	植えるアクションクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/28	実装開始
* @date		2021/12/17	コンポーネントに変更
* @date		2021/12/28	アクションゲージ追加
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CPlantAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Effect/CEffectManager.h>
#include <System/Sound/CSound.h>

// コンポーネント
#include <Component/Game/Player/CPlayer.h>

/** マクロ定義 */
namespace
{
	const int TIME = 60;			// アクション時間
	const int PLAY_INTERVAL = 20;	// SE.エフェクト再生間隔
}

/**
* @brief	コンストラクタ
*/
CPlantAction::CPlantAction()
	: m_nFrame(PLAY_INTERVAL)

{

}


/**
* @brief	デストラクタ
*/
CPlantAction::~CPlantAction()
{

}


/**
* @brief	生成時
*/
void CPlantAction::OnCreate()
{
	// スクリプト初期化
	CScriptBase::OnCreate();
	// コンポーネントID設定
	SetID(EComponentType::Action);
	// タイマーの生成
	m_pTimer = new CTimer(TIME);
	// アクションゲージUI生成
	CreateActionGauge(TIME, EDirection::Up, 15.0f);
	// SEボリュームセット
	SOUND_MANAGER->SetVolume(SE_PLANT, 3.0f);
}


/**
* @brief	更新処理
*/
void CPlantAction::Update()
{
	if (m_nFrame > PLAY_INTERVAL)
	{
		// SE再生
		SOUND_MANAGER->Play(SE_PLANT);
		m_nFrame = 0;
		// エフェクト再生
		Vector3 pos = m_spTargetObject.lock()->m_spTransform.lock()->GetPosition() + Vector3::up()*5.0f;
		EFFECT_MANAGER->Play(EEffectType::PlantSmoke, pos);
	}
	m_nFrame++;

	// 更新出来なければ終了
	if (!IsUpdate())
	{
		// アクション終了時の処理
		EndProcess();
		// アクションフラグOFF
		m_spGameObject.lock()->GetComponent<CPlayer>().lock()->SetActionFlag(false);		
		// SE再生停止
		SOUND_MANAGER->Stop(SE_PLANT);
		return;
	}
}


/**
* @brief	アクション終了時の処理
*/
void CPlantAction::EndProcess()
{
	// アイテムのリリース
	m_spGameObject.lock()->GetComponent<CPlayer>().lock()->ReleaseItem();
	// 親子関係を解除
	m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(m_spTargetItem);
	// 親子関係を作る
	CTransform::SetParentChildRelation(m_spTargetObject, m_spTargetItem, EDirection::Up, 0.0f);
	
	// アクションゲージ削除
	DeleteActionGauge();
}
