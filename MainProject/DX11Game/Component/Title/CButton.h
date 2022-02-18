#pragma once
/**
*
* @file		CButton.h
* @brief	�{�^���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** �{�^���N���X */
class CButton final : public CScriptBase
{
public:
	CButton();
	virtual ~CButton();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// �����x
	float	m_fAlpha;
	bool	m_bIsUp;
};