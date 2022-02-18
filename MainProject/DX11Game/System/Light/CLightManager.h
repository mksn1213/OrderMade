#pragma once
/**
*
* @file		CLightManager.h
* @brief	ライト管理クラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	実装開始
*
*/

/** インクルード */
#include <System/Light/CLight.h>
#include <System/Utility/Singleton.h>
#include <list>
#include <algorithm>
#include <typeinfo>

#define	LIGHT (CLightManager::GetInstance())

/** ライト管理クラス */
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
* @brief	ライト作成
* @return	int		ライト番号
*/
template <class T>
int CLightManager::Create()
{
	// テンプレートのデータ型チェック
	static_assert(std::is_base_of<CLight, T>::value,
		"[_CLightManager::Create<T>] template T not inherit from 'CLight'");

	// 生成・リストに追加
	m_list.push_back(new T);
	m_list.back()->Update();
	return static_cast<int>(m_list.size() - 1);
}

/**
* @brief	ライト取得
* @return	T*	ライトオブジェクト
*/
template <class T>
T* CLightManager::Get()
{
	// 実行時型チェック
	const std::type_info& type = typeid(T);
	LightList::iterator it = std::find_if(m_list.begin(), m_list.end(),
		[&type](CLight*& obj)
	{
		return typeid(*obj) == type;
	});
	return reinterpret_cast<T*>(*it);
}
