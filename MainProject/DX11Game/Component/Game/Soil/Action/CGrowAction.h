#pragma once
/**
*
* @file		CGrowAction.h
* @brief	成長アクションクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/07	実装開始
* @date		2021/12/18	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CAction.h>

/** 成長アクションクラス */
class CGrowAction final : public CAction
{
public:
	CGrowAction();
	virtual ~CGrowAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	// エフェクト再生用
	int m_nFrame;
};
