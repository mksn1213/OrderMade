#pragma once
/**
*
* @file		CTitleLogo.h
* @brief	タイトルロゴクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/11	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

// 前定義
class CSpriteRenderer;

/** タイトルロゴクラス */
class CTitleLogo final : public CScriptBase
{
public:
	CTitleLogo();
	virtual ~CTitleLogo();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};