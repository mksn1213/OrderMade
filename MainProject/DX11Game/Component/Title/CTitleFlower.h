#pragma once
/**
*
* @file		CTitleFlower.h
* @brief	�^�C�g���ԃN���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/10	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <vector>

/** �O��` */
class CModelRenderer;

/** �^�C�g���ԃN���X */
class CTitleFlower final : public CScriptBase
{
public:
	CTitleFlower();
	virtual ~CTitleFlower();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

private:
	// �����_���[
	std::weak_ptr<CModelRenderer> m_spRenderer;
	// ���f���ԍ�
	int m_nModelNum;
	// �G�t�F�N�g�Đ��p
	int		m_nFrame;
	int		m_nFrame2;
	int		m_nFrame3;
	bool	m_bChange;
};