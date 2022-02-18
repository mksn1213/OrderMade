#pragma once
/**
*
* @file		CScoreUI.h
* @brief	スコアクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/25	実装開始
* @date		2021/12/22	コンポーネントに変更
* @date		2021/12/30	CScoreからCScoreUIに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <Scene/CSceneManager.h>

class CSpriteRenderer;
/** スコアUIクラス */
class CScoreUI final : public CScriptBase
{
public:
	CScoreUI();
	virtual ~CScoreUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// スコアUI
	std::weak_ptr<CSpriteRenderer>	m_spRenderer[4];
	// 前回のスコア
	unsigned	m_uOldScore;
	// スコア変動時の演出用
	int			m_nFrame;
	bool		m_bPerform;
	// 現在のシーンタイプ
	ESceneType	m_eSceneType;
};