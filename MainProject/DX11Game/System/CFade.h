#pragma once
/**
*
* @file		CFade.h
* @brief	�t�F�[�h�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/01/14	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

// �O��`
class CSpriteRenderer;

/** �t�F�[�h�N���X */
class CFade final : public CScriptBase
{
public:
	/**
	* @enum		�t�F�[�h���
	*/
	enum EFade
	{
		FADE_NONE = 0,	// �����Ȃ�
		FADE_IN,		// �t�F�[�h�C��
		FADE_OUT,		// �t�F�[�h�A�E�g

		MAX_FADE
	};

	CFade();
	virtual ~CFade();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void StartFadeOut();

	/**
	* @brief	�t�F�[�h��Ԏ擾
	* @return	EFade	�t�F�[�h���
	*/
	EFade GetFadeState() { return m_eFadeState; }

	/**
	* @brief	�p�����[�^�擾
	* @return	float	�p�����[�^
	*/
	float GetParam() { return m_fParam; }

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spRenderer;
	// �t�F�[�h���
	EFade	m_eFadeState;
	// �t�F�[�h�p�p�����[�^
	float	m_fParam;
};