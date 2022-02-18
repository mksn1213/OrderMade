#pragma once
/**
*
* @file		CTemplateSystem.h
* @brief	テンプレートシステムベースクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CSystemBase.h>
#include <list>
#include <iostream>

/** テンプレートシステムベースクラス */
template <class T>
class CTemplateSystem : public CSystemBase
{
public:
	CTemplateSystem() {}
	virtual ~CTemplateSystem() { m_pComponentList.clear(); }

	/**
	* @brief	リストに追加
	* @param	com		追加するコンポーネント
	*/
	void AddList(T* com)
	{
		m_pComponentList.push_back(com);
	}

	/**
	* @brief	リストから削除
	* @param	com		削除するコンポーネント
	*/
	void RemoveList(T* com)
	{
		// コンポーネントリストに含まれているか検索
		auto it = std::find(m_pComponentList.begin(), m_pComponentList.end(), com);

		// リストになかった場合終了
		if (it == m_pComponentList.end())	return;

		// リストから削除
		m_pComponentList.erase(it);
	}

	/**
	* @brief	リストから削除(名前で判断)
	* @param	name	削除するコンポーネントの親オブジェクト名
	*/
	void RemoveList(std::string name)
	{
		// コンポーネントリストに含まれていれば削除
		for (auto it = m_pComponentList.begin(); it != m_pComponentList.end();)
		{
			// 名前が一致した場合
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
	* @brief	コンポーネントリストクリア
	*/
	void ListClear() override
	{
		m_pComponentList.clear();
	}

protected:
	// コンポーネントリスト
	std::list<T*>	m_pComponentList;
};
