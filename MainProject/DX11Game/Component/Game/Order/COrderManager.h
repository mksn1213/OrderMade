#pragma once
/**
*
* @file		COrderManager.h
* @brief	注文管理クラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	実装開始
* @date		2021/12/21	コンポーネントに対応
* @date		2022/01/30	シングルトン継承
*
*/

/** インクルード部 */
#include <System/Utility/Singleton.h>
#include <System/Defines.h>
#include <vector>
#include <memory>
#include <Component/Game/Order/COrderData.h>
#include <System/GameObject/CGameObject.h>

#define ORDER_MANAGER	(COrderManager::GetInstance())

/** 注文管理クラス */
class COrderManager final : public Singleton<COrderManager>
{
public:
	COrderManager();
	virtual ~COrderManager();

	HRESULT Init()	override;
	void Uninit()	override;
	void Update();
	void Draw();

	/**
	* @brief	注文データの追加
	* @param	data	追加するデータ
	*/
	void AddOrderData(COrderData data) { m_orderDataList.push_back(data); }

	/**
	* @brief	注文の数取得
	* @return	int		現在の注文数
	*/
	int GetOrderQuantity() { return m_spOrderList.size(); }

	std::weak_ptr<CGameObject> CreateOrder(COrderData data);
	void ShouldAddOrder();
	bool CheckOrder(std::weak_ptr<CGameObject> itemObj);

private:
	// 存在する注文パターンリスト
	std::vector<COrderData>						m_orderDataList;
	// 現在の注文リスト
	std::vector<std::shared_ptr<CGameObject>>	m_spOrderList;
	// 注文生成間隔用
	int											m_nCount;
};
