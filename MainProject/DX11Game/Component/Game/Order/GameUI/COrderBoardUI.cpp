/**
*
* @file		COrderBoardUI.cpp
* @brief	注文(看板)UIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/Order/GameUI/COrderBoardUI.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Order/COrderData.h>
#include <System/Sound/CSound.h>

// コンポーネント
#include <System/Renderer/CSpriteRenderer.h>

/** マクロ定義 */
namespace
{
	const float FALL_SPEED		= 10.0f;	// 落下スピード
	const float MOVE_SPEED_X	= 5.0f;		// X方向移動スピード
}

/**
* @brief	コンストラクタ
*/
COrderBoardUI::COrderBoardUI()
	: m_bMoveFlag(false)
	, m_fRemainingDistance(0.0f)
	, m_bIsPlaySound(false)
{

}


/**
* @brief	デストラクタ
*/
COrderBoardUI::~COrderBoardUI()
{

}


/**
* @brief	生成時
*/
void COrderBoardUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Sprite");

	// 名前設定
	obj->SetName("OrderBoardUI");

	// コンポーネントID設定
	SetID(Script);

	// スプライトセット
	const auto& sprite = obj->AddComponent<CSpriteRenderer>();
	m_spSprite = sprite;
	m_spSprite.lock()->SetDrawSize(Vector3(100.0f, 120.0f, 1.0f));
}


/**
* @brief	破棄時
*/
void COrderBoardUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void COrderBoardUI::Update()
{
	// 落下移動処理
	auto pos = m_spTransform.lock()->GetPosition();
	if (pos->y >= -SCREEN_HEIGHT / 2 + m_spSprite.lock()->GetDrawSize()->y / 2)
	{
		pos->y -= FALL_SPEED;
	}
	else
	{
		// 一度のみSEを再生
		if (!m_bIsPlaySound)
		{
			SOUND_MANAGER->SetVolume(SE_ORDER_IN, 4.5f);
			SOUND_MANAGER->Play(SE_ORDER_IN);
			m_bIsPlaySound = true;
		}
	}

	// 左詰め移動処理
	if (m_bMoveFlag)
	{
		pos->x -= MOVE_SPEED_X;
		m_fRemainingDistance -= MOVE_SPEED_X;
		// 残り移動量がなくなったら終了
		if (m_fRemainingDistance <= 0.0f)
		{
			m_fRemainingDistance = 0.0f;
			m_bMoveFlag = false;
		}
	}

	// 座標反映
	m_spTransform.lock()->SetPosition(pos);
}


/**
* @brief	注文データを基に使用するテクスチャをセットする
* @param	data	注文データ
*/
void COrderBoardUI::SetOrder(COrderData data)
{
	switch (data.m_eColor)
	{
	case CColor::EColor::White:		m_spSprite.lock()->SetTexture(ETexture::OrderBoard_White);		break;
	case CColor::EColor::Cyan:		m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Cyan);		break;
	case CColor::EColor::Magenta:	m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Magenta);	break;
	case CColor::EColor::Yellow:	m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Yellow);		break;
	case CColor::EColor::Red:		m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Red);		break;
	case CColor::EColor::Green:		m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Green);		break;
	case CColor::EColor::Blue:		m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Blue);		break;
	default:																						break;
	}
}