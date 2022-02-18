#pragma once
/**
*
* @file		CModelRenderer.h
* @brief	モデル描画クラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	実装開始
*
*/

/** インクルード部 */
#include <System/Renderer/CRenderer.h>
#include <System/Renderer/AssimpModel.h>
#include <System/Resource/ModelTypeID.h>

/** モデル描画クラス */
class CModelRenderer final : public CRenderer
{
public:
	CModelRenderer();
	virtual ~CModelRenderer();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
	void Draw(ID3D11DeviceContext* pDC) override;

	void SetModel(EModelType model);

private:
	CAssimpModel* m_pModel;

public:
	static const EComponentType comID;
};

