#pragma once
/**
*
* @file		CSystemBase.h
* @brief	システムベースクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <list>
#include <System/Component/ComponentIDData.h>
#include <d3d11.h>

/** システムベースクラス */
class CSystemBase
{
public:
	CSystemBase();
	virtual ~CSystemBase();

	virtual void OnCreate() {}
	virtual void OnDestroy(){}
	virtual void OnUpdate() {}
	virtual void OnDraw(ID3D11DeviceContext* pDC)	{}
	virtual void ListClear() {}

	/**
	* @brief	コンポーネントIDセット
	* @param	typeID	コンポーネントID
	*/
	void SetTypeID(int typeID) { m_eComponentTypeID = typeID; }

	/**
	* @brief	コンポーネントID取得
	* @return	int	コンポーネントID
	*/
	int GetTypeID() { return m_eComponentTypeID; }

private:
	int m_eComponentTypeID;
};