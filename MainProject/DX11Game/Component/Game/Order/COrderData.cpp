/**
*
* @file		COrderData.cpp
* @brief	�����f�[�^�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Order/COrderData.h>

/**
* @brief	�R���X�g���N�^
* @param	need	���A�����K�v��
* @param	kind	�I�u�W�F�N�g�̎��
* @param	color	�F���
* @param	score	�X�R�A
*/
COrderData::COrderData(bool need, EObjectType kind, CColor::EColor color, int score)
	: m_bPotted(need)
	, m_eKind(kind)
	, m_eColor(color)
	, m_nScore(score)
{

}


/**
* @brief	�f�X�g���N�^
*/
COrderData::~COrderData()
{

}