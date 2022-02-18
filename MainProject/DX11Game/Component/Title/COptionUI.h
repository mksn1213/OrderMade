#pragma once
/**
*
* @file		COptionUI.h
* @brief	�I�v�V����UI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

// �O��`
class CSpriteRenderer;

/** �I�v�V����UI�N���X */
class COptionUI final : public CScriptBase
{
public:
	COptionUI();
	virtual ~COptionUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};