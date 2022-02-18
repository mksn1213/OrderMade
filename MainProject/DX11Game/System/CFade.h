#pragma once
/**
*
* @file		CFade.h
* @brief	フェードクラス
* @author	SHONOSUKE MAKITA
* @date		2021/01/14	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

// 前定義
class CSpriteRenderer;

/** フェードクラス */
class CFade final : public CScriptBase
{
public:
	/**
	* @enum		フェード状態
	*/
	enum EFade
	{
		FADE_NONE = 0,	// 何もなし
		FADE_IN,		// フェードイン
		FADE_OUT,		// フェードアウト

		MAX_FADE
	};

	CFade();
	virtual ~CFade();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void StartFadeOut();

	/**
	* @brief	フェード状態取得
	* @return	EFade	フェード状態
	*/
	EFade GetFadeState() { return m_eFadeState; }

	/**
	* @brief	パラメータ取得
	* @return	float	パラメータ
	*/
	float GetParam() { return m_fParam; }

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spRenderer;
	// フェード状態
	EFade	m_eFadeState;
	// フェード用パラメータ
	float	m_fParam;
};