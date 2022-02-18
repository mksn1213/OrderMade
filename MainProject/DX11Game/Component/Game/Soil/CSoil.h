#pragma once
/**
*
* @file		CSoil.h
* @brief	�y�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/11	�R���|�[�l���g�ɕύX
* @date		2021/12/18	�A�N�V�����ǉ�
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �y�N���X */
class CSoil final : public CScriptBase
{
public:
	CSoil();
	virtual ~CSoil();

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
	// �A�N�V���������ǂ���
	bool	m_bIsAction;
	// �O��̃A�N�V�����t���O
	bool	m_bOldIsAction;
};