#pragma once
/**
*
* @file		CTitleTruck.h
* @brief	タイトルトラッククラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/10	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

class CModelRenderer;
/** タイトルトラッククラス */
class CTitleTruck final : public CScriptBase
{
public:
	CTitleTruck();
	virtual ~CTitleTruck();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// スプライトレンダラー
	std::weak_ptr<CModelRenderer> m_spRenderer;
	// エフェクト再生用
	int m_nFrame;
};