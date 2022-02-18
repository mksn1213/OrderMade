#pragma once
/**
*
* @file		CSelectGate.h
* @brief	�Z���N�g�Q�[�g�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �Z���N�g�Q�[�g�N���X */
class CSelectGate final : public CScriptBase
{
public:
	/**
	* @enum		EGateType
	* @brief	�Q�[�g�^�C�v
	*/
	enum EGateType
	{
		GateTitle = 0,	// �^�C�g��
		GateTutorial,	// �`���[�g���A��
		GateGame1,		// �Q�[��1

		MaxGate
	};

public:
	CSelectGate();
	virtual ~CSelectGate();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;

	/**
	* @brief	�Q�[�g�^�C�v�Z�b�g
	* @param	type	�Q�[�g�^�C�v
	*/
	void SetGateType(EGateType type);

private:
	// �Q�[�g�^�C�v
	EGateType	m_eType;
};
