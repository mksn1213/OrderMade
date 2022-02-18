#pragma once
/**
*
* @file		COptionUI.h
* @brief	オプションUIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

// 前定義
class CSpriteRenderer;

/** オプションUIクラス */
class COptionUI final : public CScriptBase
{
public:
	COptionUI();
	virtual ~COptionUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};