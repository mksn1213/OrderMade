#pragma once
/**
*
* @file		CTutorialClearUI.h
* @brief	�`���[�g���A���N���AUI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** �`���[�g���A���N���AUI�N���X */
class CTutorialClearUI final : public CScriptBase
{
public:
	CTutorialClearUI();
	virtual ~CTutorialClearUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// �J�E���g�p
	int		m_nFrame;
	bool	m_bIsCreate;
};
