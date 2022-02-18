#pragma once
/**
*
* @file		CMeshRendererSystem.h
* @brief	メッシュ描画システムクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CTemplateSystem.h>

// 前定義
class CMeshRenderer;

/** メッシュ描画システムクラス */
class CMeshRendererSystem final : public CTemplateSystem<CMeshRenderer>
{
public:
	CMeshRendererSystem();
	virtual ~CMeshRendererSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnDraw(ID3D11DeviceContext* pDC)	override;
};