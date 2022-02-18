#pragma once
/**
*
* @file		CResultButton.h
* @brief	リザルトボタンクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

class CSpriteRenderer;
/** リザルトボタンクラス */
class CResultButton final : public CScriptBase
{
public:
	CResultButton();
	virtual ~CResultButton();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};