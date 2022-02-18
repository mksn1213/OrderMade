#pragma once
/**
*
* @file		CTimeUpUI.h
* @brief	タイムアップUIクラス
* @author	SHONOSUKE MAKITA
* @date		2021/01/13	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

class CSpriteRenderer;
class Vector3;
/** タイムアップUI */
class CTimeUpUI final : public CScriptBase
{
public:
	CTimeUpUI();
	virtual ~CTimeUpUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// アルファ値
	float							m_fAlpha;
};
