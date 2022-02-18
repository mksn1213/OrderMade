/**
*
* @file		CTimer.cpp
* @brief	���ԃN���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/31	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/CTimer.h>

/**
* @brief	�R���X�g���N�^
*/
CTimer::CTimer(int nTime)
	: m_nTime(nTime)
{

}


/**
* @brief	�f�X�g���N�^
*/
CTimer::~CTimer()
{

}


/**
* @brief	�X�V����
* @return	bool	�X�V�̉�(true/�X�V�\�@false/�I��)
*/
bool CTimer::Update()
{
	// �^�C�}�[�̏I������
	if (m_nTime <= 0)	return false;
	m_nTime--;
	return true;
}