#pragma once
/**
*
* @file		CGameObjectManager.h
* @brief	�Q�[���I�u�W�F�N�g�Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	�����J�n
* @date		2021/11/30	�I�u�W�F�N�g�Ǘ�����Q�[���I�u�W�F�N�g�Ǘ��ɕύX
* @date		2022/01/23	�V���O���g���p��
*
*/

/** �C���N���[�h�� */
#include <System/Utility/Singleton.h>
#include <System/GameObject/CGameObject.h>
#include <System/Component/CTransform.h>
#include <list>
#include <memory>
#include <System/Utility/Vector3.h>
#include <System/Texture/CTexture.h>

#define GAMEOBJECT_MANAGER (CGameObjectManager::GetInstance())

/** �I�u�W�F�N�g�Ǘ��N���X */
class CGameObjectManager final : public Singleton<CGameObjectManager>
{
public :
	CGameObjectManager();
	virtual ~CGameObjectManager();

	HRESULT Init()		override;
	void	Uninit()	override;

	/**
	* @brief	�C���X�^���X��
	* @param	pos		�������W
	* @return	T*		�����I�u�W�F�N�g
	*/
	template <class T>
	std::weak_ptr<T> Instantiation(Vector3 pos = Vector3::zero())
	{
		// �C���X�^���X��
		std::shared_ptr<T> spObj = std::make_shared<T>();
		// ���g���i�[
		spObj->m_self = spObj;
		// ������
		spObj->Init();
		spObj->GetComponent<CTransform>().lock()->SetPosition(pos);
		// ���X�g�Ɋi�[
		m_spGameObjectList.push_back(spObj);

		return spObj;
	}

	/**
	* @brief	�Q�[���I�u�W�F�N�g�폜
	* @param	spObj	�폜����Q�[���I�u�W�F�N�g
	*/
	void DestroyGameObject(std::weak_ptr<CGameObject> spObj)
	{
		auto obj = spObj.lock();
		if (!obj)	return;

		// ���X�g�Ɋ܂܂�Ă��邩
		auto it = std::find(m_spGameObjectList.begin(), m_spGameObjectList.end(), obj);
		
		// ���X�g�ɂȂ���ΏI��
		if (m_spGameObjectList.end() == it)	return;
		
		// �e�����݂��Ă���ꍇ�e�q�֌W���폜
		const auto& parentObj = obj->m_spTransform.lock()->GetParent();
		if (parentObj.lock())	parentObj.lock()->m_spTransform.lock()->ReleaseRelationship(spObj);

		// �R���C�_�[�������Ă���΃R���C�_�[���X�g����폜
		auto collider = obj->GetComponent<CCollider>();
		if (collider.lock())	CCollider::RemoveFromList(collider);

		// �R���|�[�l���g�폜
		obj->RemoveComponentAll();

		// �I�u�W�F�N�g���X�g����폜
		m_spGameObjectList.erase(it);
	}

	/**
	* @brief	�Q�[���I�u�W�F�N�g���X�g�擾
	* @return	std::list<std::shared_ptr<CGameObject>>	�Q�[���I�u�W�F�N�g���X�g
	*/
	std::list<std::shared_ptr<CGameObject>> GetGameObjectList() { return m_spGameObjectList; }

private:
	// �Q�[���I�u�W�F�N�g���X�g
	std::list<std::shared_ptr<CGameObject>> m_spGameObjectList;
};