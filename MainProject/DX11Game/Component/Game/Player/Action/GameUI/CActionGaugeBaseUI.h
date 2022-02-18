#pragma once
/**
*
* @file		CActionGaugeBaseUI.h
* @brief	アクションゲージベースUIクラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/26	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** アクションゲージベースUIクラス */
class CActionGaugeBaseUI final : public CScriptBase
{
public:
	CActionGaugeBaseUI();
	virtual ~CActionGaugeBaseUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
};
