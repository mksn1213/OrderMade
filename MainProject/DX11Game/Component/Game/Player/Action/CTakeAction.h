#pragma once
/**
*
* @file		CTakeAction.h
* @brief	取るアクションクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	実装開始
* @date		2021/12/16	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CAction.h>

/** 取るアクションクラス */
class CTakeAction final : public CAction
{
public:
	CTakeAction();
	virtual ~CTakeAction();
	
	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;
};
