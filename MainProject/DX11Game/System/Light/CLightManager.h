#pragma once
/**
*
* @file		CLightManager.h
* @brief	���C�g�Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	�����J�n
*
*/

/** �C���N���[�h */
#include <System/Light/CLight.h>
#include <System/Utility/Singleton.h>
#include <list>
#include <algorithm>
#include <typeinfo>

#define	LIGHT (CLightManager::GetInstance())

/** ���C�g�Ǘ��N���X */
class CLightManager final : public Singleton<CLightManager>
{
private:
	using LightList = std::list<CLight*>;

public:
	HRESULT Init()	 override;
	void	Uninit() override;
	void	Update();

	CLight* Get(int nNo = -1);
	template <class T> int Create();
	template <class T> T* Get();

private:
	LightList	m_list;
	int			m_nMainLightNo;
};

/**
* @brief	���C�g�쐬
* @return	int		���C�g�ԍ�
*/
template <class T>
int CLightManager::Create()
{
	// �e���v���[�g�̃f�[�^�^�`�F�b�N
	static_assert(std::is_base_of<CLight, T>::value,
		"[_CLightManager::Create<T>] template T not inherit from 'CLight'");

	// �����E���X�g�ɒǉ�
	m_list.push_back(new T);
	m_list.back()->Update();
	return static_cast<int>(m_list.size() - 1);
}

/**
* @brief	���C�g�擾
* @return	T*	���C�g�I�u�W�F�N�g
*/
template <class T>
T* CLightManager::Get()
{
	// ���s���^�`�F�b�N
	const std::type_info& type = typeid(T);
	LightList::iterator it = std::find_if(m_list.begin(), m_list.end(),
		[&type](CLight*& obj)
	{
		return typeid(*obj) == type;
	});
	return reinterpret_cast<T*>(*it);
}
