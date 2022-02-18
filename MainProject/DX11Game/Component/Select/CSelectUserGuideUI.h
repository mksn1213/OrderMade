#pragma once
/**
*
* @file		CSelectUserGuideUI.h
* @brief	操作ガイドUIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** 操作ガイドUIクラス */
class CSelectUserGuideUI final : public CScriptBase
{
public:
	CSelectUserGuideUI();
	virtual ~CSelectUserGuideUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};