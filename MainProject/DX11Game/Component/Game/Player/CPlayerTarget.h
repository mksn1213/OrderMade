#pragma once
/**
*
* @file		CPlayerTarget.h
* @brief	�v���C���[�^�[�Q�b�g�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/20	�����J�n
* @date		2021/12/03	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

class CPlayer;
/** �v���C���[�^�[�Q�b�g�N���X */
class CPlayerTarget final : public CScriptBase
{
public:
	CPlayerTarget();
	virtual ~CPlayerTarget();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider);

	/**
	* @brief	�^�[�Q�b�g�����Ԃ�
	*/
	void TargetON() { m_bIsTarget = true; }

	/**
	* @brief	�^�[�Q�b�g�����܂��Ă��邩
	* @return	bool	true/���܂��Ă���,false/���܂��Ă��Ȃ�
	*/
	bool IsTarget() { return m_bIsTarget; }

	// �e(�v���C���[)�R���|�[�l���g
	std::weak_ptr<CPlayer> m_spPlayer;

private:
	// �^�[�Q�b�g�����܂��Ă��邩
	bool	m_bIsTarget;
};