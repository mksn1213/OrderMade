#pragma once
/**
*
* @file		CCameraManager.h
* @brief	�J�����Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/21	�����J�n
*
*/

/** �C���N���[�h */
#include <System/Camera/CCamera.h>
#include <System/Utility/Singleton.h>
#include <list>
#include <algorithm>
#include <typeinfo>

#define CAMERA (CCameraManager::GetInstance())

/** �J�����Ǘ��N���X */
class CCameraManager final : public Singleton<CCameraManager>
{
private:
	using CameraList = std::list<CCamera*>;

public:
	HRESULT Init()	 override;
	void	Uninit() override;
	void	Update();

	CCamera* Get(int nNo = -1);
	template<class T> int Create();
	template<class T> T* Get();

private:
	CameraList	m_list;
	int			m_nMainCameraNo;

};

/**
* @brief	�J�����쐬
* @return	int		�J�����ԍ�
*/
template <class T> 
int CCameraManager::Create()
{
	// �e���v���[�g�̃f�[�^�^�`�F�b�N
	static_assert(std::is_base_of<CCamera, T>::value,
		"[CCameraManager::Create<T>] template T not inherit from 'CCamera'");

	// �����E���X�g�ɒǉ�
	m_list.push_back(new T);
	m_list.back()->Update();
	return static_cast<int>(m_list.size() - 1);
}

/**
* @brief	�J�����擾
* @return	T*	�J�����I�u�W�F�N�g
*/
template <class T> T* CCameraManager::Get()
{
	// ���s���^�`�F�b�N
	const std::type_info& type = typeid(T);
	CameraList::iterator it = std::find_if(m_list.begin(), m_list.end(),
		[&type](CCamera*& obj)
	{
		return typeid(*obj) == type;
	});
	return reinterpret_cast<T*>(*it);
}
