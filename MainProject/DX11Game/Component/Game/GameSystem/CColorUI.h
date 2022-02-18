#pragma once
/**
*
* @file		CColorUI.h
* @brief	�J���[UI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** �J���[UI�N���X */
class CColorUI final : public CScriptBase
{
public:
	CColorUI();
	virtual ~CColorUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};