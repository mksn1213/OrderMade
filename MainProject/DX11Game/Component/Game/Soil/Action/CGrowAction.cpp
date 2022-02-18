/**
*
* @file		CGrowAction.cpp
* @brief	成長アクションクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/07	実装開始
* @date		2021/12/18	コンポーネントに変更
* @date		2021/12/28	アクションゲージUI作成
*
*/

/** インクルード部 */
#include <Component/Game/Soil/Action/CGrowAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Factory/CStageFactory.h>
#include <System/Effect/CEffectManager.h>
#include <Component/Tutorial/CTutorialManager.h>
#include <Scene/CSceneManager.h>
#include <System/Sound/CSound.h>
#include <System/Utility/Search.h>

// コンポーネント
#include <Component/Game/Soil/CSoil.h>
#include <Component/Game/Soil/CFertilizer.h>
#include <Component/Game/Plant/CSprout.h>
#include <Component/Game/Plant/CFlower.h>
#include <Component/Game/Order/GameUI/CIconUI.h>

/** マクロ定義 */
namespace
{
	const int TIME = 180;					// アクション時間
	const int EFFECT_PLAY_INTERVAL = 60;	// エフェクト再生間隔
}

/**
* @brief	コンストラクタ
*/
CGrowAction::CGrowAction()
	: m_nFrame(EFFECT_PLAY_INTERVAL)
{

}


/**
* @brief	デストラクタ
*/
CGrowAction::~CGrowAction()
{

}


/**
* @brief	生成時
*/
void CGrowAction::OnCreate()
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
	SOUND_MANAGER->SetVolume(SE_GROW, 0.5f);
}


/**
* @brief	更新処理
*/
void CGrowAction::Update()
{
	// エフェクト再生
	if (m_nFrame > EFFECT_PLAY_INTERVAL)
	{
		EFFECT_MANAGER->Play(EEffectType::GrowAction, m_spTransform.lock()->GetPosition());
		m_nFrame = 0;
	}
	m_nFrame++;

	// 更新できなければ終了
	if (!IsUpdate())
	{
		// アクション終了時の処理
		EndProcess();
		// アクションフラグOFF
		m_spGameObject.lock()->GetComponent<CSoil>().lock()->SetActionFlag(false);
		return;
	}
}


/**
* @brief	アクション終了時の処理
*/
void CGrowAction::EndProcess()
{
	// SE再生
	SOUND_MANAGER->Play(SE_GROW);

	// エフェクト再生
	EFFECT_MANAGER->Play(EEffectType::Grow, m_spTransform.lock()->GetPosition());

	const auto& id = m_spTargetItem.lock()->GetObjectID();

	// 成長段階によって処理を変える
	if (id == EObjectType::Seed)
	{
		// 親子関係を解除
		m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(m_spTargetItem);
		// 種オブジェクトの削除
		m_spTargetItem.lock()->Destroy();
		// 芽オブジェクトの生成
		const auto& sproutObj = CStageFactory::CreateGameObject(EObjectType::Sprout);
		// 親子関係を作る
		CTransform::SetParentChildRelation(m_spGameObject, sproutObj, EDirection::Up, 0.0f);
	
		// 肥料が存在していた場合
		const auto& childList = m_spGameObject.lock()->m_spTransform.lock()->GetChildList();
		const auto& fertilizerObj = SearchExistsList(childList, "SupportItem");
		if (fertilizerObj.lock())
		{
			// 芽オブジェクトに色情報をセット
			const auto& addColor = fertilizerObj.lock()->GetComponent<CFertilizer>().lock()->GetColor();
			sproutObj.lock()->GetComponent<CSprout>().lock()->SetColor(addColor);
						
			// 子オブジェクトを取り替える
			fertilizerObj.lock()->m_spTransform.lock()->ReplaceChildAll(sproutObj);

			// 親子関係を解除
			m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(fertilizerObj);
			// 肥料オブジェクト削除
			fertilizerObj.lock()->Destroy();
		}
	}
	else if (id == EObjectType::Sprout)
	{
		// 親子関係を解除
		m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(m_spTargetItem);
		// 花オブジェクトの生成
		const auto& flowerObj = CStageFactory::CreateGameObject(EObjectType::Flower);
		// 芽オブジェクトの色情報を保持
		auto color = m_spTargetItem.lock()->GetComponent<CSprout>().lock()->GetColor();
		// 子オブジェクトを取り替える
		const auto& targetItemTrans = m_spTargetItem.lock()->m_spTransform.lock();
		targetItemTrans->GetChildList().begin()->lock()->Destroy();
		targetItemTrans->ReplaceChildAll(flowerObj);
		// 芽オブジェクトの削除
		m_spTargetItem.lock()->Destroy();
		// 親子関係を作る
		CTransform::SetParentChildRelation(m_spGameObject, flowerObj, EDirection::Up, 0.0f);
	
		// 肥料が存在していた場合
		const auto& childList = m_spGameObject.lock()->m_spTransform.lock()->GetChildList();
		const auto& fertilizerObj = SearchExistsList(childList, "SupportItem").lock();
		if (fertilizerObj)
		{
			// 花オブジェクトに色情報をセット
			const auto& addColor = fertilizerObj->GetComponent<CFertilizer>().lock()->GetColor();
			// セットする色の決定
			color = color + addColor;
			// アイコンを変更する
			const auto& flowerTrans = flowerObj.lock()->m_spTransform.lock();
			flowerTrans->GetChildList().back().lock()->Destroy();
			flowerTrans->GetChildList().back().lock()->GetComponent<CIconUI>().lock()->SetIconTexture(color);
			const auto& flowerChild = flowerTrans->GetChildList();
			// アイコンの移動
			for (auto it = flowerChild.begin(); it != flowerChild.end(); ++it)
			{
				it->lock()->GetComponent<CIconUI>().lock()->MoveON(5.0f);
			}
			// 親子関係を解除
			m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(fertilizerObj);
			// 肥料オブジェクト削除
			fertilizerObj->Destroy();
		}

		// 色情報のセット
		flowerObj.lock()->GetComponent<CFlower>().lock()->SetColor(color);
		
		// チュートリアルシーンだった場合
		if (SCENE_MANAGER->GetScene()->GetSceneType() == ESceneType::SceneTutorial)
		{
			auto stageNo = TUTORIAL_MANAGER->GetStageNo();
			if (stageNo == 0)
			{
				TUTORIAL_MANAGER->Fin();
			}
			else if (stageNo == 1)
			{
				if (color.colorType != CColor::EColor::White)	TUTORIAL_MANAGER->Fin();
			}
		}
	}

	// アクションゲージ削除
	DeleteActionGauge();
}
