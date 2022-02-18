#pragma once
/**
*
* @file		CTitleLogo.h
* @brief	�^�C�g�����S�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

// �O��`
class CSpriteRenderer;

/** �^�C�g�����S�N���X */
class CTitleLogo final : public CScriptBase
{
public:
	CTitleLogo();
	virtual ~CTitleLogo();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};