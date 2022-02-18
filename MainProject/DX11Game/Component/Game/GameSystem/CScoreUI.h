#pragma once
/**
*
* @file		CScoreUI.h
* @brief	�X�R�A�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/25	�����J�n
* @date		2021/12/22	�R���|�[�l���g�ɕύX
* @date		2021/12/30	CScore����CScoreUI�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <Scene/CSceneManager.h>

class CSpriteRenderer;
/** �X�R�AUI�N���X */
class CScoreUI final : public CScriptBase
{
public:
	CScoreUI();
	virtual ~CScoreUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// �X�R�AUI
	std::weak_ptr<CSpriteRenderer>	m_spRenderer[4];
	// �O��̃X�R�A
	unsigned	m_uOldScore;
	// �X�R�A�ϓ����̉��o�p
	int			m_nFrame;
	bool		m_bPerform;
	// ���݂̃V�[���^�C�v
	ESceneType	m_eSceneType;
};