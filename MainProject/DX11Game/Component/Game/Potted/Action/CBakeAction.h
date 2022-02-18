#pragma once
/**
*
* @file		CBakeAction.h
* @brief	焼くアクションクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	実装開始
* @date		2021/12/19	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CAction.h>

/** 焼くアクションクラス */
class CBakeAction final : public CAction
{
public:
	CBakeAction();
	virtual ~CBakeAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	// エフェクト再生用
	int		m_nFrame;
	Vector3 m_effectPos;
};