/**
*
* @file		CTitleFlower.cpp
* @brief	タイトル花クラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/10	実装開始
*
*/

/** インクルード部 */
#include <Component/Title/CTitleFlower.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Effect/CEffectManager.h>

/** マクロ定義 */
namespace
{
	const int EFFECT_PLAY_INTERVAL = 240;	// エフェクト再生間隔
	const int EFFECT_PLAY_INTERVAL2 = 60;	// エフェクト再生間隔
	const int MODEL_CHANGE_INTERVAL = 30;	// モデル変更間隔
}

/**
* @brief	コンストラクタ
*/
CTitleFlower::CTitleFlower()
	: m_nModelNum((int)EModelType::Flower_W)
	, m_nFrame(0)
	, m_nFrame2(0)
	, m_nFrame3(0)
	, m_bChange(false)
{
	
}


/**
* @brief	デストラクタ
*/
CTitleFlower::~CTitleFlower()
{

}


/**
* @brief	生成時
*/
void CTitleFlower::OnCreate()
{
	// スクリプト初期化
	CScriptBase::OnCreate();

	// モデル追加
	const auto& renderer = m_spGameObject.lock()->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Flower_W);
	m_spRenderer = renderer;
	m_nModelNum = (int)EModelType::Flower_W;
}


/**
* @brief	破棄時
*/
void CTitleFlower::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CTitleFlower::Update()
{
	// エフェクト再生
	if (m_nFrame > EFFECT_PLAY_INTERVAL)
	{
		EFFECT_MANAGER->Play(EEffectType::Grow, m_spTransform.lock()->GetPosition());
		m_nFrame = 0;
		m_bChange = true;
	}
	m_nFrame++;
	
	if (m_nFrame2 > EFFECT_PLAY_INTERVAL2)
	{
		EFFECT_MANAGER->Play(EEffectType::GrowAction, m_spTransform.lock()->GetPosition()+Vector3::up()*5);
		m_nFrame2 = 0;
	}
	m_nFrame2++;

	if (m_bChange)
	{
		if (m_nFrame3 > MODEL_CHANGE_INTERVAL)
		{
			m_nModelNum++;
			if (m_nModelNum > (int)EModelType::Flower_B)
			{
				m_nModelNum = (int)EModelType::Flower_W;
			}
			m_spRenderer.lock()->SetModel((EModelType)m_nModelNum);
			m_nFrame3 = 0;
			m_bChange = false;
		}
		m_nFrame3++;
	}
}