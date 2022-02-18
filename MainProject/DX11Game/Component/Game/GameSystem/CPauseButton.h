#pragma once
/**
*
* @file		CPauseButton.h
* @brief	ポーズボタンクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** ポーズボタンクラス */
class CPauseButton final : public CScriptBase
{
public:
	CPauseButton();
	virtual ~CPauseButton();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};