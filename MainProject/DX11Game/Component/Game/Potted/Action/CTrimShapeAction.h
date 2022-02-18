#pragma once
/**
*
* @file		CTrimShapeAction.h
* @brief	形状を整えるアクションクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	実装開始
* @date		2021/12/19	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CAction.h>

/** 形状を整えるアクションクラス */
class CTrimShapeAction final : public CAction
{
public:
	CTrimShapeAction();
	virtual ~CTrimShapeAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	// SE再生用
	int m_nFrame;
};