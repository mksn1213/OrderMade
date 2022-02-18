#pragma once
/**
*
* @file		CResultScreen.h
* @brief	���U���g��ʃN���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

// �O��`
class CScriptRenderer;

/** ���U���g��ʃN���X */
class CResultScreen final : public CScriptBase
{
public:
	CResultScreen();
	virtual ~CResultScreen();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CScriptRenderer>	m_spSprite;
};