#pragma once
/**
*
* @file		CPotteryWheel.h
* @brief	�{炑�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/11	�R���|�[�l���g�ɕύX
* @date		2021/12/19	�A�N�V�����ǉ�
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �{炃N���X */
class CPotteryWheel final : public CScriptBase
{
public:
	CPotteryWheel();
	virtual ~CPotteryWheel();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> item)	override;

	/**
	* @brief	�A�N�V�����t���O�Z�b�g
	* @param	flag		�A�N�V�����t���O(true/�A�N�V������,false/�A�N�V���������{)
	*/
	void SetActionFlag(bool flag) { m_bIsAction = flag; }

	/**
	* @brief	�A�N�V�����t���O�擾
	* @return	bool		�A�N�V�����t���O(true/�A�N�V������ , false/�A�N�V���������{)
	*/
	bool IsAction() { return m_bIsAction; }

private:
	// ��]����I�u�W�F�N�g
	std::weak_ptr<CGameObject>	m_spWheel;
	// �A�N�V���������ǂ���
	bool						m_bIsAction;
	// �O��̃A�N�V�����t���O
	bool						m_bOldIsAction;
};