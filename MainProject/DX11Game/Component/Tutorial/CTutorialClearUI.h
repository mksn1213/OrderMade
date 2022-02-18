#pragma once
/**
*
* @file		CTutorialClearUI.h
* @brief	チュートリアルクリアUIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** チュートリアルクリアUIクラス */
class CTutorialClearUI final : public CScriptBase
{
public:
	CTutorialClearUI();
	virtual ~CTutorialClearUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// カウント用
	int		m_nFrame;
	bool	m_bIsCreate;
};
