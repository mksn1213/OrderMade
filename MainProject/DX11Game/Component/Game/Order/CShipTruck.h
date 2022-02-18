#pragma once
/**
*
* @file		CShipTruck.h
* @brief	�o�׃g���b�N�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/07	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <System/Utility/Vector3.h>

/** �o�׃g���b�N�N���X */
class CShipTruck final : public CScriptBase
{
public:
	CShipTruck();
	virtual ~CShipTruck();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	bool IsFin()		{ return m_bFin; }
	void SetShipFlag()	
	{ 
		m_bShipping = true; 
		m_bIsPlaySE = false;
	}
	void SetMoveFlag(Vector3 pos)
	{ 
		m_gatePos = pos;
		m_bMove = true;
		m_bIsPlaySE = false;
	}

private:
	// �ړ��t���O
	bool	m_bMove;
	// �o�׃t���O
	bool	m_bShipping;
	// �I���t���O
	bool	m_bFin;
	// �Z�b�g���W
	Vector3	m_gatePos;
	// SE�Đ��p
	bool	m_bIsPlaySE;
	// �G�t�F�N�g�Đ��p
	int		m_nFrame;
};