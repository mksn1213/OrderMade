#pragma once
/**
*
* @file		CGiveWaterAction.h
* @brief	水を与えるアクションクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/07	実装開始
* @date		2021/12/18	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CAction.h>

/** 水を与えるアクションクラス */
class CGiveWaterAction final : public CAction
{
public:
	CGiveWaterAction();
	virtual ~CGiveWaterAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	// SE再生用
	int	m_nFrame;
};