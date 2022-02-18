#pragma once
/**
*
* @file		CTimer.h
* @brief	���ԃN���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/31	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Defines.h>

/** �^�C�}�[�N���X */
class CTimer
{
public:
	CTimer(int nTime);
	~CTimer();

	bool Update();
	
	/**
	* @brief	�c�莞�Ԃ̎擾
	* @return	int		�c�莞��
	*/
	int GetTime() { return m_nTime; }

private:
	int m_nTime;
};