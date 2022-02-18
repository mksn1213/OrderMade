#pragma once
/**
*
* @file		CPutWaterAction.h
* @brief	水を入れるアクションクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/06	実装開始
* @date		2021/12/18	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Player/Action/CAction.h>

/** 水を入れるアクションクラス */
class CPutWaterAction final : public CAction
{
public:
	CPutWaterAction();
	virtual ~CPutWaterAction();

	void OnCreate()		override;
	void Update()		override;
	void EndProcess()	override;

private:
	bool m_bIsWater;
};