#pragma once
/**
*
* @file		CPauseUI.h
* @brief	ポーズUIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** ポーズUIクラス */
class CPauseUI final : public CScriptBase
{
public:
	CPauseUI();
	virtual ~CPauseUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void Select(bool bSelect);

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// 選択
	std::weak_ptr<CGameObject>		m_spSelectObj[2];
	bool							m_bBackGame;
};