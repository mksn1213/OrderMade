#pragma once
/**
*
* @file		CTutorialFinUI.h
* @brief	�`���[�g���A���I��UI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** �`���[�g���A���I��UI�N���X */
class CTutorialFinUI final : public CScriptBase
{
public:
	CTutorialFinUI();
	virtual ~CTutorialFinUI();

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