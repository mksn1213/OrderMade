#pragma once
/**
*
* @file		CComponent.h
* @brief	コンポーネントクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/28	実装開始
*
*/

/** インクルード部 */
#include <System/Object/CObject.h>
#include <System/Component/ComponentIDData.h>
#include <memory>

class CGameObject;
/** コンポーネントクラス */
class CComponent :public CObject<CComponent>
{
public:
	CComponent() {}
	CComponent(std::weak_ptr<CGameObject> spObj);
	virtual ~CComponent();

	virtual void OnCreate()  {}
	virtual void OnDestroy() {}
	virtual void Update()	 {}
	
	void SetID(EComponentType id)	{ m_typeID = id; }
	EComponentType GetID() const	{ return m_typeID; }
	void SetGameObject(std::weak_ptr<CGameObject> spObj) { m_spGameObject = spObj; }

	// アタッチしているゲームオブジェクト
	std::weak_ptr<CGameObject> m_spGameObject;

private:
	// コンポーネントタイプID
	EComponentType m_typeID;
};

