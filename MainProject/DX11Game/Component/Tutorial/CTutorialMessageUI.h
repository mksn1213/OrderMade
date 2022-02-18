#pragma once
/**
*
* @file		CTutorialMessageUI.h
* @brief	�`���[�g���A�����b�Z�[�WUI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** �`���[�g���A�����b�Z�[�WUI�N���X */
class CTutorialMessageUI final : public CScriptBase
{
public:
	CTutorialMessageUI();
	virtual ~CTutorialMessageUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetTexture(int nStageNo);

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// �J�E���g�p
	int m_nFrame;
};