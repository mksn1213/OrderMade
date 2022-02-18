#pragma once
/**
*
* @file		CSpriteRendererSystem.h
* @brief	�X�v���C�g�`��V�X�e���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CTemplateSystem.h>

// �O��`
class CSpriteRenderer;

/** �X�v���C�g�`��V�X�e���N���X */
class CSpriteRendererSystem final : public CTemplateSystem<CSpriteRenderer>
{
public:
	CSpriteRendererSystem();
	virtual ~CSpriteRendererSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnDraw(ID3D11DeviceContext* pDC)	override;
};