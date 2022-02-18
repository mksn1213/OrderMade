#pragma once
/**
*
* @file		CTitleTruck.h
* @brief	�^�C�g���g���b�N�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/10	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

class CModelRenderer;
/** �^�C�g���g���b�N�N���X */
class CTitleTruck final : public CScriptBase
{
public:
	CTitleTruck();
	virtual ~CTitleTruck();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CModelRenderer> m_spRenderer;
	// �G�t�F�N�g�Đ��p
	int m_nFrame;
};