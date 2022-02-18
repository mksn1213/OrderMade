#pragma once
/**
*
* @file		CGameObject.h
* @brief	�Q�[���I�u�W�F�N�g�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/28	�����J�n
* @date		2021/12/04	�X�}�[�g�|�C���^�ŊǗ�����悤�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Object/CObject.h>
#include <System/Component/CComponent.h>
#include <System/GameObject/ObjectIDData.h>
#include <System/Graphics/ShaderList.h>
#include <list>
#include <memory>
#include <algorithm>

#include <System/Component/CTransform.h>
#include <System/Component/CCollider.h>
#include <System/Component/CScriptBase.h>
#include <System/Renderer/CRenderer.h>
#include <System/Renderer/CModelRenderer.h>

/** �Q�[���I�u�W�F�N�g�N���X */
class CGameObject final : public CObject<CGameObject>
{
public:
	CGameObject();
	virtual ~CGameObject();

	void Init();
	void Uninit();
	void Update();

	/**
	* @brief	�R���|�[�l���g�̒ǉ�
	* @return	std::weak_ptr<T>	�ǉ������R���|�[�l���g
	*/
	template <class T>
	std::weak_ptr<T> AddComponent()
	{
		// ����
		std::shared_ptr<T> spComponent = std::make_shared<T>();
		// ���g���i�[
		spComponent->m_self = spComponent;
		// �A�^�b�`���Ă���Q�[���I�u�W�F�N�g���Z�b�g
		spComponent->SetGameObject(m_spGameObject.lock());
		// ���X�g�Ɋi�[
		m_spComponentList.push_back(spComponent);
		// ����������
		spComponent->OnCreate();
		
		return spComponent;
	}

	/**
	* @brief	�R���|�[�l���g�̎擾
	* @return	std::weak_ptr<T>	�擾����R���|�[�l���g
	*/
	template <class T>
	std::weak_ptr<T> GetComponent()
	{
		std::weak_ptr<T> comTemp;
		for (auto& com : m_spComponentList)
		{
			// �R���|�[�l���gID�Ŕ���
			if (com->GetID() == T::comID)
			{
				comTemp = std::static_pointer_cast<T>(com);
				return comTemp;
			}
		}
		return comTemp.lock();
	}
	
	/**
	* @brief	�R���|�[�l���g�̍폜
	* @return	bool	�폜�̐���
	*/
	template <class T>
	bool RemoveComponent()
	{
		for (auto it = m_spComponentList.begin(); it != m_spComponentList.end(); ++it)
		{
			// �R���|�[�l���gID�Ŕ���
			if ((*it)->GetID() == T::comID)
			{
				// �R���|�[�l���g�̍폜
				(*it)->OnDestroy();
				m_spComponentList.erase(it);
				return true;
			}
		}
		return false;
	}

	/**
	* @brief	�������Ă���R���|�[�l���g�S�č폜
	*/
	void RemoveComponentAll()
	{
		for (auto it = m_spComponentList.begin(); it != m_spComponentList.end();)
		{
			// �폜������
			(*it)->OnDestroy();
			// ���X�g����폜
			it = m_spComponentList.erase(it);
		}
	}

	/**
	* @brief	�g�p����V�F�[�_�[�^�C�v�Z�b�g
	* @param	EVertexShaderKind	���_�V�F�[�_�[
	* @param	EPixelShaderKind	�s�N�Z���V�F�[�_�[
	*/
	void SetShader(EVertexShaderKind vertex, EPixelShaderKind pixel)
	{
		m_eVertexShader = vertex;
		m_ePixelShader = pixel;
	}

	/**
	* @brief	���݂̃V�F�[�_�[�^�C�v���ꎞ�ۑ�
	*/
	void SaveShaderKind()
	{
		m_eVSKindBuffer = m_eVertexShader;
		m_ePSKindBuffer = m_ePixelShader;
	}

	/**
	* @brief	�g�p���钸�_�V�F�[�_�[�擾
	* @return	EVertexShaderKind	���_�V�F�[�_�[�̃^�C�v
	*/
	EVertexShaderKind GetVSKind() { return m_eVertexShader; }

	/**
	* @brief	�g�p����s�N�Z���V�F�[�_�[�擾
	* @return	EPixelShaderKind	�s�N�Z���V�F�[�_�[�̃^�C�v
	*/
	EPixelShaderKind GetPSKind() { return m_ePixelShader; }

	/**
	* @brief	�g�p���钸�_�V�F�[�_�[�擾
	* @return	EVertexShaderKind	���_�V�F�[�_�[�̃^�C�v
	*/
	EVertexShaderKind GetVSKindBuffer() { return m_eVSKindBuffer; }

	/**
	* @brief	�g�p����s�N�Z���V�F�[�_�[�擾
	* @return	EPixelShaderKind	�s�N�Z���V�F�[�_�[�̃^�C�v
	*/
	EPixelShaderKind GetPSKindBuffer() { return m_ePSKindBuffer; }

	/**
	* @brief	�A�N�e�B�u�Z�b�g
	* @param	active		true/�A�N�e�B�u�� , false/��A�N�e�B�u��
	*/
	void SetActive(bool active) { m_isActive = active; }

	/**
	* @brief	�A�N�e�B�u��Ԃ��ǂ���
	* @return	true/�A�N�e�B�u , false/��A�N�e�B�u
	*/
	bool IsActive() { return m_isActive; }

	/**
	* @brief	�^�O�Z�b�g
	* @param	tag		�^�O��
	*/
	void SetTag(std::string tag) { m_tag = tag; }
	
	/**
	* @brief	�^�O�擾
	* @return	std::string		�^�O��
	*/
	const std::string& GetTag() { return m_tag; }

	/**
	* @brief	�I�u�W�F�N�gID�Z�b�g
	* @param	type	�I�u�W�F�N�gID�^�C�v
	*/
	void SetObjectID(EObjectType type) { m_eObjectID = type; }
	
	/**
	* @brief	�I�u�W�F�N�gID�擾
	* @return	EObjectType		�I�u�W�F�N�gID
	*/
	const EObjectType& GetObjectID() { return m_eObjectID; }

	void Destroy();

	std::weak_ptr<CTransform>		m_spTransform;
private:
	std::weak_ptr<CGameObject>		m_spGameObject;
	std::string						m_tag;
	bool							m_isActive;
	EObjectType						m_eObjectID;

	// �V�F�[�_�^�C�v
	EVertexShaderKind				m_eVertexShader;
	EPixelShaderKind				m_ePixelShader;
	// �V�F�[�_�[�^�C�v�ꎞ�ۑ��p
	EVertexShaderKind				m_eVSKindBuffer;
	EPixelShaderKind				m_ePSKindBuffer;

	// �R���|�[�l���g���X�g
	std::list<std::shared_ptr<CComponent>>	m_spComponentList;
};

