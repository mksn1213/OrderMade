#pragma once
/**
*
* @file		CSelectUserGuideUI.h
* @brief	����K�C�hUI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** ����K�C�hUI�N���X */
class CSelectUserGuideUI final : public CScriptBase
{
public:
	CSelectUserGuideUI();
	virtual ~CSelectUserGuideUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};