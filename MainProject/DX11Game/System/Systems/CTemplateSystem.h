#pragma once
/**
*
* @file		CTemplateSystem.h
* @brief	�e���v���[�g�V�X�e���x�[�X�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CSystemBase.h>
#include <list>
#include <iostream>

/** �e���v���[�g�V�X�e���x�[�X�N���X */
template <class T>
class CTemplateSystem : public CSystemBase
{
public:
	CTemplateSystem() {}
	virtual ~CTemplateSystem() { m_pComponentList.clear(); }

	/**
	* @brief	���X�g�ɒǉ�
	* @param	com		�ǉ�����R���|�[�l���g
	*/
	void AddList(T* com)
	{
		m_pComponentList.push_back(com);
	}

	/**
	* @brief	���X�g����폜
	* @param	com		�폜����R���|�[�l���g
	*/
	void RemoveList(T* com)
	{
		// �R���|�[�l���g���X�g�Ɋ܂܂�Ă��邩����
		auto it = std::find(m_pComponentList.begin(), m_pComponentList.end(), com);

		// ���X�g�ɂȂ������ꍇ�I��
		if (it == m_pComponentList.end())	return;

		// ���X�g����폜
		m_pComponentList.erase(it);
	}

	/**
	* @brief	���X�g����폜(���O�Ŕ��f)
	* @param	name	�폜����R���|�[�l���g�̐e�I�u�W�F�N�g��
	*/
	void RemoveList(std::string name)
	{
		// �R���|�[�l���g���X�g�Ɋ܂܂�Ă���΍폜
		for (auto it = m_pComponentList.begin(); it != m_pComponentList.end();)
		{
			// ���O����v�����ꍇ
			if ((*it)->m_spGameObject.lock()->GetName() == name)
			{
				m_pComponentList.erase(it);
				break;
			}
			else
			{
				++it;
			}
		}
	}

	/**
	* @brief	�R���|�[�l���g���X�g�N���A
	*/
	void ListClear() override
	{
		m_pComponentList.clear();
	}

protected:
	// �R���|�[�l���g���X�g
	std::list<T*>	m_pComponentList;
};
