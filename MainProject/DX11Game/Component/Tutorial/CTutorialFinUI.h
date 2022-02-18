#pragma once
/**
*
* @file		CTutorialFinUI.h
* @brief	チュートリアル終了UIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** チュートリアル終了UIクラス */
class CTutorialFinUI final : public CScriptBase
{
public:
	CTutorialFinUI();
	virtual ~CTutorialFinUI();

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