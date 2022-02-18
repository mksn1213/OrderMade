#pragma once
/**
*
* @file		Singleton.h
* @brief	�V���O���g���N���X
* @author	SHONOSUKE MAKITA
* @date		2021/01/15	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Defines.h>

//#define SINGLETON_CONSTRACTOR(_class) \
//private:\
//	_class(){}\
//	~_class(){}\
//	friend Singleton<_class>

/** �V���O���g���N���X */
template <class T>
class Singleton
{
protected:
	Singleton() {}
	virtual ~Singleton() {}
	virtual HRESULT Init() { return S_OK; }
	virtual void Uninit() {}

public:
	/**
	* @brief	�C���X�^���X�擾
	* @return	T*	�C���X�^���X
	*/
	static T* GetInstance()
	{
		return m_pInstance;
	}

	/**
	* @brief	�C���X�^���X��
	*/
	static HRESULT CreateInstance()
	{
		DestroyInstance();
		m_pInstance = new T;
		HRESULT hr = m_pInstance->Init();
		return hr;
	}

	/**
	* @brief	�C���X�^���X�폜
	*/
	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			m_pInstance->Uninit();
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	// �C���X�^���X
	static T* m_pInstance;
};

template <class T> T* Singleton<T>::m_pInstance = nullptr;