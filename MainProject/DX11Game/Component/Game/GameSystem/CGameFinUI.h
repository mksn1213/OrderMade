#pragma once
/**
*
* @file		CGameFinUI.h
* @brief	ゲーム終了UIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;

/** ゲーム終了UIクラス */
class CGameFinUI final : public CScriptBase
{
public:
	CGameFinUI();
	virtual ~CGameFinUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	/**
	* @brief	セレクト状態セット
	* @param	bSelect		true/選択されている , false/選択されていない
	*/
	void SetSelect(bool bSelect) { m_bIsSelect = bSelect; }

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// 選択されているか
	bool	m_bIsSelect;
	// 透明度
	float	m_fAlpha;
	bool	m_bIsUp;
};
