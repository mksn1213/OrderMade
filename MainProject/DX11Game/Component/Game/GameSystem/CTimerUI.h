#pragma once
/**
*
* @file		CTimerUI.h
* @brief	�^�C�}�[UI�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/01/04	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <Scene/CSceneManager.h>

class CSpriteRenderer;
//class CTimer;
/** �^�C�}�[UI�N���X */
class CTimerUI final : public CScriptBase
{
public:
	CTimerUI();
	virtual ~CTimerUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// ����UI
	std::weak_ptr<CSpriteRenderer>	m_spRenderer[4];
	// �^�C���ύX���̉��o�p
	int			m_nFrame;
	bool		m_bPerform;
	// ���݂̃V�[���^�C�v
	ESceneType	m_eSceneType;
};