/**
*
* @file		CShipTruck.cpp
* @brief	出荷トラッククラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/07	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/Order/CShipTruck.h>
#include <System/GameObject/CGameObject.h>
#include <System/Effect/CEffectManager.h>
#include <System/Sound/CSound.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>

/** マクロ定義 */
namespace
{
	const float SPEED		= 1.5f;			// 移動速度
	const float FIN_POS_X	= 300.0f;		// 終了座標
	const int	EFFECT_PLAY_INTERVAL = 5;	// エフェクト再生間隔
}

/**
* @brief	コンストラクタ
*/
CShipTruck::CShipTruck()
	: m_bMove(false)
	, m_bShipping(false)
	, m_bFin(false)
	, m_gatePos(Vector3::zero())
	, m_bIsPlaySE(false)
	, m_nFrame(0)
{

}


/**
* @brief	デストラクタ
*/
CShipTruck::~CShipTruck()
{

}


/**
* @brief	生成時
*/
void CShipTruck::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	// タグ設定
	obj->SetTag("Stationary");
	// 名前設定
	obj->SetName("ShipTruck");
	// コンポーネントID
	SetID(Script);
	// モデルのセット
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ShipTruck);
	// SEボリュームセット
	SOUND_MANAGER->SetVolume(SE_CAR, 3.0f);
}


/**
* @brief	破棄時
*/
void CShipTruck::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CShipTruck::Update()
{
	// 移動フラグが立っていれば移動
	if (m_bMove)
	{
		// SE再生
		if (!m_bIsPlaySE)
		{
			SOUND_MANAGER->Play(SE_CAR);
			m_bIsPlaySE = true;
		}
		// エフェクト再生
		if (m_nFrame > EFFECT_PLAY_INTERVAL)
		{
			EFFECT_MANAGER->Play(EEffectType::Smoke, m_spTransform.lock()->GetPosition());
			m_nFrame = 0;
		}
		m_nFrame++;
		auto pos = m_spTransform.lock()->GetPosition();
		pos->x += SPEED;
		m_spTransform.lock()->SetPosition(pos);
		if (pos->x >= m_gatePos->x)	m_bMove = false;
	}

	// 出荷フラグが立っていれば移動
	if (m_bShipping)
	{
		// SE再生
		if (!m_bIsPlaySE)
		{
			SOUND_MANAGER->Play(SE_CAR);
			m_bIsPlaySE = true;
		}
		// エフェクト再生
		if (m_nFrame > EFFECT_PLAY_INTERVAL)
		{
			EFFECT_MANAGER->Play(EEffectType::Smoke, m_spTransform.lock()->GetPosition());
			m_nFrame = 0;
		}
		m_nFrame++;
		auto pos = m_spTransform.lock()->GetPosition();
		pos->x += SPEED;
		m_spTransform.lock()->SetPosition(pos);
		if (pos->x >= m_gatePos->x + FIN_POS_X)
		{
			m_bFin = true;
			m_bShipping = false;
		}
	}
}