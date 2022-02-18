#pragma once
/**
*
* @file		CResultScreen.h
* @brief	リザルト画面クラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

// 前定義
class CScriptRenderer;

/** リザルト画面クラス */
class CResultScreen final : public CScriptBase
{
public:
	CResultScreen();
	virtual ~CResultScreen();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CScriptRenderer>	m_spSprite;
};