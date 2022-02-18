/**
*
* @file		CPutAction.cpp
* @brief	置くアクションクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	実装開始
* @date		2021/12/16	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CPutAction.h>
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
CPutAction::CPutAction()
{

}


/**
* @brief	デストラクタ
*/
CPutAction::~CPutAction()
{

}


/**
* @brief	生成時
*/
void CPutAction::OnCreate()
{
	// スクリプト初期化
	CScriptBase::OnCreate();
	// コンポーネントID設定
	SetID(EComponentType::Action);
	// タイマーの生成
	m_pTimer = new CTimer(TIME);
}


/**
* @brief	更新
*/
void CPutAction::Update()
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
void CPutAction::EndProcess()
{

}
