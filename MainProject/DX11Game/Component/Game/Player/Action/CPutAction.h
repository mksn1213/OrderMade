#pragma once
/**
*
* @file		CPutAction.h
* @brief	置くアクションクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	実装開始
* @date		2021/12/16	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CAction.h>

/** 置くアクションクラス */
class CPutAction final : public CAction
{
public:
	CPutAction();
	virtual ~CPutAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;
};
