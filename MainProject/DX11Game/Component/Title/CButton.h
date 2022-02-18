#pragma once
/**
*
* @file		CButton.h
* @brief	ボタンクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** ボタンクラス */
class CButton final : public CScriptBase
{
public:
	CButton();
	virtual ~CButton();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// 透明度
	float	m_fAlpha;
	bool	m_bIsUp;
};