#pragma once
/**
*
* @file		CColorUI.h
* @brief	カラーUIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** カラーUIクラス */
class CColorUI final : public CScriptBase
{
public:
	CColorUI();
	virtual ~CColorUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};