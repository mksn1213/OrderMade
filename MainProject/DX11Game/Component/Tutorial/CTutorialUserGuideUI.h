#pragma once
/**
*
* @file		CTutorialUserGuideUI.h
* @brief	�������UI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** �������UI�N���X */
class CTutorialUserGuideUI final : public CScriptBase
{
public:
	CTutorialUserGuideUI();
	virtual ~CTutorialUserGuideUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};