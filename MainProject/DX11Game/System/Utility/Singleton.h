#pragma once
/**
*
* @file		Singleton.h
* @brief	シングルトンクラス
* @author	SHONOSUKE MAKITA
* @date		2021/01/15	実装開始
*
*/

/** インクルード部 */
#include <System/Defines.h>

//#define SINGLETON_CONSTRACTOR(_class) \
//private:\
//	_class(){}\
//	~_class(){}\
//	friend Singleton<_class>

/** シングルトンクラス */
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
	* @brief	インスタンス取得
	* @return	T*	インスタンス
	*/
	static T* GetInstance()
	{
		return m_pInstance;
	}

	/**
	* @brief	インスタンス化
	*/
	static HRESULT CreateInstance()
	{
		DestroyInstance();
		m_pInstance = new T;
		HRESULT hr = m_pInstance->Init();
		return hr;
	}

	/**
	* @brief	インスタンス削除
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
	// インスタンス
	static T* m_pInstance;
};

template <class T> T* Singleton<T>::m_pInstance = nullptr;