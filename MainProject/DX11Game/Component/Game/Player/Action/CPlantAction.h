#pragma once
/**
*
* @file		CPlantAction.h
* @brief	植えるアクションクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/28	実装開始
* @date		2021/12/17	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CAction.h>

/** 植えるアクションクラス */
class CPlantAction final : public CAction
{
public:
	CPlantAction();
	virtual ~CPlantAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	// SE再生用
	int m_nFrame;
};
