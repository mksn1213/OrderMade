#pragma once
/**
*
* @file		CCameraManager.h
* @brief	カメラ管理クラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/21	実装開始
*
*/

/** インクルード */
#include <System/Camera/CCamera.h>
#include <System/Utility/Singleton.h>
#include <list>
#include <algorithm>
#include <typeinfo>

#define CAMERA (CCameraManager::GetInstance())

/** カメラ管理クラス */
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
* @brief	カメラ作成
* @return	int		カメラ番号
*/
template <class T> 
int CCameraManager::Create()
{
	// テンプレートのデータ型チェック
	static_assert(std::is_base_of<CCamera, T>::value,
		"[CCameraManager::Create<T>] template T not inherit from 'CCamera'");

	// 生成・リストに追加
	m_list.push_back(new T);
	m_list.back()->Update();
	return static_cast<int>(m_list.size() - 1);
}

/**
* @brief	カメラ取得
* @return	T*	カメラオブジェクト
*/
template <class T> T* CCameraManager::Get()
{
	// 実行時型チェック
	const std::type_info& type = typeid(T);
	CameraList::iterator it = std::find_if(m_list.begin(), m_list.end(),
		[&type](CCamera*& obj)
	{
		return typeid(*obj) == type;
	});
	return reinterpret_cast<T*>(*it);
}
