#pragma once
/**
*
* @file		CTutorialUserGuideUI.h
* @brief	操作説明UIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** 操作説明UIクラス */
class CTutorialUserGuideUI final : public CScriptBase
{
public:
	CTutorialUserGuideUI();
	virtual ~CTutorialUserGuideUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};