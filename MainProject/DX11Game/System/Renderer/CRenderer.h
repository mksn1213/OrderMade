#pragma once
/**
*
* @file		CRenderer.h
* @brief	描画クラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CComponent.h>
#include <System/Defines.h>

class CTransform;
/** 描画クラス */
class CRenderer : public CComponent
{
public:
	CRenderer();
	virtual ~CRenderer();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
	virtual void Draw(ID3D11DeviceContext* pDC) {}

protected:
	std::weak_ptr<CTransform> m_spTransform;
};