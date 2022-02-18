#pragma once
/**
*
* @file		CTitleFlower.h
* @brief	タイトル花クラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/10	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <vector>

/** 前定義 */
class CModelRenderer;

/** タイトル花クラス */
class CTitleFlower final : public CScriptBase
{
public:
	CTitleFlower();
	virtual ~CTitleFlower();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// レンダラー
	std::weak_ptr<CModelRenderer> m_spRenderer;
	// モデル番号
	int m_nModelNum;
	// エフェクト再生用
	int		m_nFrame;
	int		m_nFrame2;
	int		m_nFrame3;
	bool	m_bChange;
};