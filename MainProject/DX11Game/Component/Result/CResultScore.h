#pragma once
/**
*
* @file		CResultScore.h
* @brief	リザルトスコアクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** リザルトスコアクラス */
class CResultScore final : public CScriptBase
{
public:
	CResultScore();
	virtual ~CResultScore();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetScore(int nScore);

private:
	// スコア
	std::weak_ptr<CSpriteRenderer>	m_spRenderer[4];
};