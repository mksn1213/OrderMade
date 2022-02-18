#pragma once
/**
*
* @file		CTutorialOperateUI.h
* @brief	�`���[�g���A������UI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** �`���[�g���A������UI�N���X */
class CTutorialOperateUI final : public CScriptBase
{
public:
	CTutorialOperateUI();
	virtual ~CTutorialOperateUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetTexture(int nStageNo);

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
};