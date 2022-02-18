#pragma once
/**
*
* @file		CModelRendererSystem.h
* @brief	モデル描画システムクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CTemplateSystem.h>

// 前定義
class CModelRenderer;

/** モデル描画システムクラス */
class CModelRendererSystem final : public CTemplateSystem<CModelRenderer>
{
public:
	CModelRendererSystem();
	virtual ~CModelRendererSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnDraw(ID3D11DeviceContext* pDC)	override;
};