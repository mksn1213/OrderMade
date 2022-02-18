#pragma once
/**
*
* @file		CActionGaugeUI.h
* @brief	�A�N�V�����Q�[�WUI�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/26	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �A�N�V�����Q�[�WUI�N���X */
class CActionGaugeUI final : public CScriptBase
{
public:
	CActionGaugeUI();
	virtual ~CActionGaugeUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	/**
	* @brief	�A�N�V�������ԃZ�b�g
	* @param	time	�A�N�V���������ɂ����鎞��
	*/
	void SetActionTime(int time) 
	{ 
		m_nTime = time; 
		m_fIncrease = 10.0f / m_nTime;
	}

private:
	int		m_nTime;
	// �Q�[�W�̑�����
	float	m_fIncrease;
};
