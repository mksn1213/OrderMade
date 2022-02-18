#pragma once
/**
*
* @file		CPlayer.h
* @brief	�v���C���[�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/13  �����J�n
* @date		2021/12/03	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <System/Utility/Vector3.h>

/** �O��` */
class CRigidbody;
class CAssimpModel;

/** �v���C���[�N���X */
class CPlayer final : public CScriptBase
{
public:
	CPlayer();
	virtual ~CPlayer();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void MoveUpdate();
	void AngleUpdate();

	void OnCollision(std::weak_ptr<CCollider> collider)	override;
	void SetItem(std::weak_ptr<CGameObject> item);
	void ReleaseItem();

	/**
	* @brief	�A�C�e���t���O�̎擾
	* @return	bool		�A�C�e���t���O
	*/
	bool GetItemFlag() { return m_bHasItem; }

	/**
	* @brief	�A�C�e���擾
	* @return	std::weak_ptr<CGameObject>	�����Ă���A�C�e��
	*/
	std::weak_ptr<CGameObject> GetItem() { return m_spItem; }



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
	// �v���C���[���f�����(�A�j���[�V�����p)
	CAssimpModel*				m_pModel;
	// �v���C���[�̃^�[�Q�b�g�|�C���g�I�u�W�F�N�g
	std::weak_ptr<CGameObject>	m_spTargetPoint;
	// ���W�b�h�{�f�B
	std::weak_ptr<CRigidbody>	m_spRigidbody;
	// �����Ă���A�C�e���I�u�W�F�N�g
	std::weak_ptr<CGameObject>	m_spItem;
	// �A�C�e���������Ă��邩
	bool						m_bHasItem;
	// �A�N�V���������ǂ���
	bool						m_bIsAction;
	// �O��̃A�N�V�����t���O
	bool						m_bOldIsAction;
	// �ړI�p�x
	Vector3 m_rotDest;
};
