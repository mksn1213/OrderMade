#pragma once
/**
*
* @file		CModelRendererSystem.h
* @brief	���f���`��V�X�e���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CTemplateSystem.h>

// �O��`
class CModelRenderer;

/** ���f���`��V�X�e���N���X */
class CModelRendererSystem final : public CTemplateSystem<CModelRenderer>
{
public:
	CModelRendererSystem();
	virtual ~CModelRendererSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnDraw(ID3D11DeviceContext* pDC)	override;
};