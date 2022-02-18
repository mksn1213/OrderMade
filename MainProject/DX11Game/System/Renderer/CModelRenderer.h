#pragma once
/**
*
* @file		CModelRenderer.h
* @brief	���f���`��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Renderer/CRenderer.h>
#include <System/Renderer/AssimpModel.h>
#include <System/Resource/ModelTypeID.h>

/** ���f���`��N���X */
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

