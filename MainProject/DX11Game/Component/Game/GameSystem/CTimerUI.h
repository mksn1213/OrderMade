#pragma once
/**
*
* @file		CTimerUI.h
* @brief	タイマーUIクラス
* @author	SHONOSUKE MAKITA
* @date		2021/01/04	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <Scene/CSceneManager.h>

class CSpriteRenderer;
//class CTimer;
/** タイマーUIクラス */
class CTimerUI final : public CScriptBase
{
public:
	CTimerUI();
	virtual ~CTimerUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// 時間UI
	std::weak_ptr<CSpriteRenderer>	m_spRenderer[4];
	// タイム変更時の演出用
	int			m_nFrame;
	bool		m_bPerform;
	// 現在のシーンタイプ
	ESceneType	m_eSceneType;
};