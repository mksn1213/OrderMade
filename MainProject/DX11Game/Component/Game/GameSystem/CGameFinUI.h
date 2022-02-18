#pragma once
/**
*
* @file		CGameFinUI.h
* @brief	�Q�[���I��UI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** �Q�[���I��UI�N���X */
class CGameFinUI final : public CScriptBase
{
public:
	CGameFinUI();
	virtual ~CGameFinUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	/**
	* @brief	�Z���N�g��ԃZ�b�g
	* @param	bSelect		true/�I������Ă��� , false/�I������Ă��Ȃ�
	*/
	void SetSelect(bool bSelect) { m_bIsSelect = bSelect; }

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// �I������Ă��邩
	bool	m_bIsSelect;
	// �����x
	float	m_fAlpha;
	bool	m_bIsUp;
};
