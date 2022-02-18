#pragma once
/**
*
* @file		CTimeUpUI.h
* @brief	�^�C���A�b�vUI�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/01/13	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

class CSpriteRenderer;
class Vector3;
/** �^�C���A�b�vUI */
class CTimeUpUI final : public CScriptBase
{
public:
	CTimeUpUI();
	virtual ~CTimeUpUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// �A���t�@�l
	float							m_fAlpha;
};
