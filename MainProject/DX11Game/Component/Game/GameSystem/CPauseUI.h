#pragma once
/**
*
* @file		CPauseUI.h
* @brief	�|�[�YUI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** �|�[�YUI�N���X */
class CPauseUI final : public CScriptBase
{
public:
	CPauseUI();
	virtual ~CPauseUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void Select(bool bSelect);

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// �I��
	std::weak_ptr<CGameObject>		m_spSelectObj[2];
	bool							m_bBackGame;
};