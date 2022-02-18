#pragma once
/**
*
* @file		CObject.h
* @brief	全てのオブジェクトの基本クラス
* @author	SHONOSUKE MAKITA
* @date		2021/09/29	実装開始
*			2021/11/28	基底クラスの肥大化に対応して構造を大幅に変更
*
*/

/** インクルード部 */
#include <string>

/** 前定義 */
class CItem;

/** オブジェクトクラス */
template <class T>
class CObject
{
public:
	CObject() {}
	~CObject() {}

	// 自身の破棄
	virtual void Destroy() {}
	
	/**
	* @brief	名前取得
	* @return	std::string		名前
	*/
	std::string GetName() { return m_name; }

	/**
	* @brief	名前セット
	* @return	name	セットする名前
	*/
	void SetName(std::string name) { m_name = name; }

	// 自身のweakポインタ
	std::weak_ptr<T> m_self;

protected:
	// オブジェクト生成時
	virtual void OnCreate() {}
	// オブジェクト破棄時
	virtual void OnDestroy() {}

private:
	// 名前
	std::string m_name;
};

