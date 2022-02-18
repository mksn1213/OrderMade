#pragma once
/**
*
* @file		CMeshRendererSystem.h
* @brief	���b�V���`��V�X�e���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CTemplateSystem.h>

// �O��`
class CMeshRenderer;

/** ���b�V���`��V�X�e���N���X */
class CMeshRendererSystem final : public CTemplateSystem<CMeshRenderer>
{
public:
	CMeshRendererSystem();
	virtual ~CMeshRendererSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnDraw(ID3D11DeviceContext* pDC)	override;
};