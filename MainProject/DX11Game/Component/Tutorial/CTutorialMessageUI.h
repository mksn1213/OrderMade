#pragma once
/**
*
* @file		CTutorialMessageUI.h
* @brief	チュートリアルメッセージUIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** チュートリアルメッセージUIクラス */
class CTutorialMessageUI final : public CScriptBase
{
public:
	CTutorialMessageUI();
	virtual ~CTutorialMessageUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetTexture(int nStageNo);

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// カウント用
	int m_nFrame;
};