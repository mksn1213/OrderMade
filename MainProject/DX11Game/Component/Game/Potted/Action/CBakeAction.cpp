/**
*
* @file		CBakeAction.cpp
* @brief	焼くアクションクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	実装開始
* @date		2021/12/19	コンポーネントに変更
* @date		2021/12/28	アクションゲージ追加
*
*/

/** インクルード部 */
#include <Component/Game/Potted/Action/CBakeAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Factory/CStageFactory.h>
#include <System/Effect/CEffectManager.h>
#include <Component/Tutorial/CTutorialManager.h>
#include <Scene/CSceneManager.h>
#include <System/Sound/CSound.h>

// コンポーネント
#include <Component/Game/Potted/COven.h>
#include <Component/Game/Potted/CClay.h>

/** マクロ定義 */
namespace
{
	const int TIME = 300;					// アクション時間
	const int EFFECT_PLAY_INTERVAL = 20;	// エフェクト再生間隔
}

/**
* @brief	コンストラクタ
*/
CBakeAction::CBakeAction()
	: m_nFrame(EFFECT_PLAY_INTERVAL)
	, m_effectPos(Vector3::zero())
{

}


/**
* @brief	デストラクタ
*/
CBakeAction::~CBakeAction()
{

}


/**
* @brief	生成時
*/
void CBakeAction::OnCreate()
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
	SOUND_MANAGER->SetVolume(SE_BAKE, 3.0f);
	SOUND_MANAGER->Play(SE_BAKE);

	// エフェクト描画座標を事前に計算しておく
	XMFLOAT4X4 localWorld;
	XMStoreFloat4x4(&localWorld, XMMatrixIdentity());
	localWorld._41 = 6.0f;
	localWorld._42 = 30.0f;
	localWorld._43 = 0.0f;
	auto mtx = XMLoadFloat4x4(&localWorld);
	mtx *= XMLoadFloat4x4(&m_spTransform.lock()->GetWorldMatrix());
	XMFLOAT4X4 world;
	XMStoreFloat4x4(&world, XMMatrixIdentity());
	XMStoreFloat4x4(&world, mtx);
	m_effectPos = Vector3(world._41, world._42, world._43);
}


/**
* @brief	更新
*/
void CBakeAction::Update()
{
	// エフェクト再生
	if (m_nFrame > EFFECT_PLAY_INTERVAL)
	{
		// 炎エフェクト
		Vector3 pos = m_spTargetItem.lock()->m_spTransform.lock()->GetPosition();
		pos->y -= 10.0f;
		EFFECT_MANAGER->Play(EEffectType::OvenFire, pos);
		
		// 煙エフェクト
		EFFECT_MANAGER->Play(EEffectType::OvenSmoke, m_effectPos);
		m_nFrame = 0;
	}
	m_nFrame++;

	// 更新出来なければ終了
	if (!IsUpdate())
	{
		// アクション終了時の処理
		EndProcess();
		// アクションフラグOFF
		m_spGameObject.lock()->GetComponent<COven>().lock()->SetActionFlag(false);
		// SE停止
		SOUND_MANAGER->Stop(SE_BAKE);
		return;
	}
}


/**
* @brief	アクション終了時の処理
*/
void CBakeAction::EndProcess()
{
	// 粘土オブジェクトの削除
	m_spTargetItem.lock()->Destroy();
	// 鉢植えオブジェクトの生成
	const auto& pottedObj = CStageFactory::CreateGameObject(EObjectType::Potted);
	// 親子関係を作る
	CTransform::SetParentChildRelation(m_spGameObject, pottedObj, EDirection::Up, 12.0f,EDirection::Front,5.0f);

	// アクションゲージ削除
	DeleteActionGauge();

	// チュートリアルシーンだった場合
	if (SCENE_MANAGER->GetScene()->GetSceneType() == ESceneType::SceneTutorial)
	{
		if (TUTORIAL_MANAGER->GetStageNo() == 2)
		{
			TUTORIAL_MANAGER->Fin();
		}
	}
}
