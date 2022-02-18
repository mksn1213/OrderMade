/**
*
* @file		CTakeAction.cpp
* @brief	取るアクションクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	実装開始
* @date		2021/12/16	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CTakeAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Player/CPlayer.h>


/** マクロ定義 */
namespace
{
	const int TIME = 5;
}

/**
* @brief	コンストラクタ
*/
CTakeAction::CTakeAction()
{

}


/**
* @brief	デストラクタ
*/
CTakeAction::~CTakeAction()
{

}


/**
* @brief	生成時
*/
void CTakeAction::OnCreate()
{
	// スクリプト初期化
	CScriptBase::OnCreate();
	// コンポーネントID設定
	SetID(EComponentType::Action);
	// タイマーの生成
	m_pTimer = new CTimer(TIME);
}


/**
* @brief	更新処理
*/
void CTakeAction::Update()
{
	// 更新出来なければ終了
	if (!IsUpdate())
	{
		// アクション終了時の処理
		EndProcess();
		// アクションフラグOFF
		m_spGameObject.lock()->GetComponent<CPlayer>().lock()->SetActionFlag(false);
		return;
	}
}


/**
* @brief	アクション終了時の処理
*/
void CTakeAction::EndProcess()
{

}