/**
*
* @file		CIconUI.cpp
* @brief	アイコンUIクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/28	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>
#include <System/Utility/CColor.h>

// コンポーネント
#include <System/Renderer/CMeshRenderer.h>

/** マクロ定義 */
namespace
{
	const float MOVE_SPEED_X = 1.0f;
}

/**
* @brief	コンストラクタ
*/
CIconUI::CIconUI()
	: m_bMoveFlag(false)
	, m_fRemainingDistance(0.0f)
{

}


/**
* @brief	デストラクタ
*/
CIconUI::~CIconUI()
{

}


/**
* @brief	生成時
*/
void CIconUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();
	
	// タグ設定
	obj->SetTag("Billboard");

	// 名前設定
	obj->SetName("IconUI");

	// コンポーネントID設定
	SetID(Script);

	m_spTransform.lock()->SetScale(Vector3(3.5f, 3.5f, 1.0f));

	// レンダラー追加
	const auto& renderer = m_spGameObject.lock()->AddComponent<CMeshRenderer>().lock();
	renderer->MakeBillboard();
	m_spRenderer = renderer;
}


/**
* @brief	破棄時
*/
void CIconUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CIconUI::Update()
{
	// アイコン移動処理
	if (m_bMoveFlag)
	{
		auto localMatrix = m_spTransform.lock()->GetLocalMatrix();
		if (m_fRemainingDistance > 0.0f)
		{
			localMatrix._41 += MOVE_SPEED_X;
			m_fRemainingDistance -= MOVE_SPEED_X;
			// 残り移動量がなくなったら終了
			if (m_fRemainingDistance <= 0.0f)
			{
				m_fRemainingDistance = 0.0f;
				m_bMoveFlag = false;
			}
		}
		else
		{
			localMatrix._41 -= MOVE_SPEED_X;
			m_fRemainingDistance += MOVE_SPEED_X;
			// 残り移動量がなくなったら終了
			if (m_fRemainingDistance >= 0.0f)
			{
				m_fRemainingDistance = 0.0f;
				m_bMoveFlag = false;
			}
		}
		m_spTransform.lock()->SetLocalMatrix(localMatrix);
	}
}


/**
* @brief	アイコンのテクスチャセット
* @param	type
*/
void CIconUI::SetIconTexture(ETexture type)
{
	m_spRenderer.lock()->SetBaseTexture(type);
}


/**
* @brief	アイコンのテクスチャセット
* @param	color
*/
void CIconUI::SetIconTexture(CColor color)
{
	if		(color.colorType == CColor::EColor::Red)	m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Red);
	else if (color.colorType == CColor::EColor::Green)	m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Green);
	else if (color.colorType == CColor::EColor::Blue)	m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Blue);
}