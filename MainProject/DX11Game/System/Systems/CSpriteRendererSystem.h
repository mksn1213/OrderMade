#pragma once
/**
*
* @file		CSpriteRendererSystem.h
* @brief	スプライト描画システムクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CTemplateSystem.h>

// 前定義
class CSpriteRenderer;

/** スプライト描画システムクラス */
class CSpriteRendererSystem final : public CTemplateSystem<CSpriteRenderer>
{
public:
	CSpriteRendererSystem();
	virtual ~CSpriteRendererSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnDraw(ID3D11DeviceContext* pDC)	override;
};