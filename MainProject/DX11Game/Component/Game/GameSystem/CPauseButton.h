#pragma once
/**
*
* @file		CPauseButton.h
* @brief	�|�[�Y�{�^���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** �|�[�Y�{�^���N���X */
class CPauseButton final : public CScriptBase
{
public:
	CPauseButton();
	virtual ~CPauseButton();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};