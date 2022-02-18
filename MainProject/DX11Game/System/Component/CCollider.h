#pragma once
/**
*
* @file		CCollider.h
* @brief	�R���C�_�[�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	�����J�n
* @date		2021/12/05	collision�N���X����collider�N���X�ɕύX
*						�R���|�[�l���g��
*
*/

/** �C���N���[�h�� */
#include <System/Component/CComponent.h>
#include <System/Utility/Vector3.h>
#include <list>
#include <memory>

// �O��`
class CTransform;
class CScriptBase;
class CRigidbody;
class CMeshRenderer;

/** �R���C�_�[�N���X */
class CCollider final : public CComponent
{
public:
	CCollider();
	virtual ~CCollider();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	/**
	* @brief	�����蔻��̂��Ƃɂ��邩�ǂ����t���O�Z�b�g
	* @param	flag		�t���O��ON/OFF
	*/
	void SetCollisionFlag(bool flag) { m_bIsCollision = flag; }

	/**
	* @brief	�R���C�_�[�T�C�Y�擾
	* @return	Vector3		�R���C�_�[�T�C�Y
	*/
	Vector3 GetColliderSize() { return m_colliderSize; }

	/**
	* @brief	�w��̃R���C�_�[�����X�g����폜
	* @param	collider	�폜����R���C�_�[
	*/
	static void RemoveFromList(std::weak_ptr<CCollider> collider)
	{
		// �R���C�_�[���X�g�Ɋ܂܂�Ă���΍폜
		for (auto it = m_spColliderList.begin(); it != m_spColliderList.end();)
		{
			if (collider.lock() == it->lock())
			{
				m_spColliderList.erase(it);
				break;
			}
			else
			{
				++it;
			}
		}
	}

	/**
	* @brief	���X�g�N���A
	*/
	static void ClearList() { m_spColliderList.clear(); }

	void CheckCollision(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other);

	// �A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃g�����X�t�H�[��
	std::weak_ptr<CTransform> m_spTransform;

	// ���W�b�h�{�f�B�擾
	const std::weak_ptr<CRigidbody>& GetRigidbody() { return m_spRigidbody; }

	// �����蔻�菈�����s���X�N���v�g
	CScriptBase* m_pMainScript;

public:
	/**
	* @enum		EColliderType
	* @brief	�R���C�_�[�^�C�v
	*/
	enum EColliderType
	{
		Box = 0,
		Sphere,

		MaxHitType
	};

	void SetColliderSize(EColliderType type, Vector3 size, Vector3 center = Vector3::zero());
	void SetCenter(Vector3 center) { m_center = center; }
	Vector3 GetCenter() { return m_center; }

private:
	// �����蔻��p�R���C�_�[���X�g
	static std::list<std::weak_ptr<CCollider>>	m_spColliderList;
	// �����蔻����s�����ɂȂ邩�ǂ���
	bool							m_bIsCollision;
	// �����蔻��T�C�Y
	Vector3							m_colliderSize;
	// ���S���W
	Vector3							m_center;
	// �R���C�_�[�`��
	EColliderType					m_eColliderType;
	// ���W�b�h�{�f�B
	std::weak_ptr<CRigidbody>		m_spRigidbody;
	// TODO : �f�o�b�O�p
	std::weak_ptr<CMeshRenderer>	m_spRenderer;

public:
	static const EComponentType comID;
};