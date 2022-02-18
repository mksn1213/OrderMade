#pragma once
/**
*
* @file		CTutorialOperateUI.h
* @brief	チュートリアル説明UIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** チュートリアル説明UIクラス */
class CTutorialOperateUI final : public CScriptBase
{
public:
	CTutorialOperateUI();
	virtual ~CTutorialOperateUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetTexture(int nStageNo);

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};