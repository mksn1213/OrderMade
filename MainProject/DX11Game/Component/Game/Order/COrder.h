#pragma once
/**
*
* @file		COrder.h
* @brief	注文クラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	実装開始
* @date		2021/12/21	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CComponent.h>
#include <Component/Game/Order/COrderData.h>

/** 前定義 */
class CTimer;
class CSpriteRenderer;

/** 注文クラス */
class COrder final : public CComponent
{
public:
	COrder();
	virtual ~COrder();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
	bool IsUpdate();

	void CreateUI();
	void SetOrderTexture();

	/**
	* @brief	データセット
	* @param	data	セットする注文データ
	*/
	void SetOrderData(COrderData data) 
	{ 
		m_orderData = data;
		CreateUI();
	}

	/**
	* @brief	データ取得
	* @return	COrderData	注文データ
	*/
	COrderData GetOrderData() { return m_orderData; }

	/**
	* @brief	UIオブジェクト取得
	* @return	std::weak_ptr<CGameObject>
	*/
	std::weak_ptr<CGameObject>	GetGameObject() { return m_spSpriteObject; }

private:
	// 注文データのUIオブジェクト
	std::weak_ptr<CGameObject>		m_spSpriteObject;
	// 注文データのUIスプライト
	std::weak_ptr<CSpriteRenderer>	m_spSpriteRenderer;
	// 注文データ
	COrderData	m_orderData;
	// 注文生存時間
	CTimer*		m_pTimer;
public:
	// コンポーネントID
	static const EComponentType comID;
};