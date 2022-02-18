#pragma once
/**
*
* @file		CResultButton.h
* @brief	���U���g�{�^���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

class CSpriteRenderer;
/** ���U���g�{�^���N���X */
class CResultButton final : public CScriptBase
{
public:
	CResultButton();
	virtual ~CResultButton();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};