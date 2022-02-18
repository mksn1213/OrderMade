#pragma once
/**
*
* @file		CSceneManager.h
* @brief	�V�[���Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
* @date		2021/12/03	�e���v���[�g�\���ɕύX
* @date		2022/01/16	�V���O���g���p��
* @date		2022/01/29	�R���|�[�l���g���^�C�v�ʂňꊇ�X�V����悤�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Utility/Singleton.h>
#include <Scene/CSceneBase.h>
#include <iostream>
#include <vector>

#include <System/Systems/CSystemBase.h>
#include <System/CFade.h>
#include <System/GameObject/CGameObject.h>

#define SCENE_MANAGER (CSceneManager::GetInstance())

/** �V�[���Ǘ��N���X */
class CSceneManager final : public Singleton<CSceneManager>
{
public:
	CSceneManager();
	virtual ~CSceneManager();

	HRESULT Init()		override;
	void	Uninit()	override;
	void	Update();
	void	Draw();
	
	/**
	* @brief	�V�[������
	* @return	T*		���������V�[��
	*/
	template <class T>
	T* CreateScene()
	{
		// �C���X�^���X��
		T* pScene = new T;
		return pScene;
	}

	/**
	* @brief	���̃V�[�����Z�b�g
	* @detail	�V�[��������V�[���J�ڊJ�n
	*/
	template <class T>
	T* SetNextScene()
	{
		// ���̃V�[�������ɃZ�b�g����Ă���ꍇ�I��
		if (m_pNextScene != nullptr) return nullptr;
		// ���̃V�[������
		auto pNextScene = CreateScene<T>();
		m_pNextScene = pNextScene;
		// �t�F�[�h�A�E�g�J�n
		m_spFade->GetComponent<CFade>().lock()->StartFadeOut();

		return pNextScene;
	}

	/**
	* @brief	���݂̃V�[���擾
	* @return	CSceneBase*		���݂̃V�[��
	*/
	CSceneBase* GetScene() { return m_pCurrentScene; }

	/**
	* @brief	�t�F�[�h�̏�Ԏ擾
	* @return	EFade	�t�F�[�h���
	*/
	CFade::EFade GetFadeState() { return m_spFadeScript.lock()->GetFadeState(); }

	/**
	* @brief	�V�X�e���X�V��ON/OFF
	* @param	bON		true/ON , false/OFF
	*/
	void SystemStop(bool bON) { m_bIsStop = bON; }

	/**
	* @brief	�t�F�[�h�X�N���v�g�擾
	* @return	std::weak_ptr<CFade>	�t�F�[�h�X�N���v�g
	*/
	std::weak_ptr<CFade> GetFadeScript() { return m_spFadeScript; }

	void SetSceneChange();

	// �V�X�e���̒ǉ�
	template <class T>
	void AddSystem(EComponentType typeID);
	// �V�X�e���̎擾
	template <class T>
	T* GetSystem(EComponentType typeID);

private:
	// ���݂̃V�[��
	CSceneBase*						m_pCurrentScene;
	// ���̃V�[��
	CSceneBase*						m_pNextScene;
	// �X�V��ON/OFF
	bool							m_bIsStop;
	// �t�F�[�h�I�u�W�F�N�g
	std::shared_ptr<CGameObject>	m_spFade;
	// �t�F�[�h�X�N���v�g
	std::weak_ptr<CFade>			m_spFadeScript;
	// �t�F�[�h�X�v���C�g
	std::weak_ptr<CSpriteRenderer>	m_spFadeSprite;
	// �V�X�e�����X�g
	std::vector<std::shared_ptr<CSystemBase>>	m_spSystemList;
};

/**
* @brief	�V�X�e���̒ǉ�
* @param	typeID	�R���|�[�l���gID
*/
template <class T>
void CSceneManager::AddSystem(EComponentType typeID)
{
	// ����
	std::shared_ptr<T> spSystem = std::make_shared<T>();
	// �V�X�e��ID�̃Z�b�g
	spSystem->SetTypeID(typeID);
	// ���X�g�ɒǉ�
	m_spSystemList.push_back(spSystem);
	// ����������
	spSystem->OnCreate();
}

/**
* @brief	�V�X�e���̎擾
* @param	typeID	�R���|�[�l���gID
* @return	T*	�V�X�e��
*/
template <class T>
T* CSceneManager::GetSystem(EComponentType typeID)
{
	for (auto system : m_spSystemList)
	{
		// �R���|�[�l���gID�𔻒�
		if (system->GetTypeID() == typeID)
		{
			T* buffer = static_cast<T*>(system.get());
			return buffer;
		}
	}
	return nullptr;
}