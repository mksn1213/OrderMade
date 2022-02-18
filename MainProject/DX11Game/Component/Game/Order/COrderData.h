#pragma once
/**
*
* @file		COrderData.h
* @brief	�����f�[�^�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/GameObject/ObjectIDData.h>
#include <System/Utility/CColor.h>

/** �����f�[�^�N���X */
class COrderData
{
public:
	COrderData() {}
	COrderData(bool need, EObjectType kind, CColor::EColor color, int score);
	~COrderData();

	// �u==�v�L���̃I�[�o�[���[�h
	bool operator==(COrderData data)
	{
		// ��v���Ă��邩�ǂ���
		if (m_bPotted	== data.m_bPotted	&&
			m_eKind		== data.m_eKind		&&
			m_eColor	== data.m_eColor)
		{
			return true;
		}
		return false;
	}

	// ���A�����K�v��
	bool			m_bPotted;
	// �I�u�W�F�N�g�̎��
	EObjectType		m_eKind;
	// �F���
	CColor::EColor	m_eColor;
	// �X�R�A
	int				m_nScore;
};
