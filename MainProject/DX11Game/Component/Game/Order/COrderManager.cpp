/**
*
* @file		COrderManager.cpp
* @brief	注文管理クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	実装開始
* @date		2021/12/21	コンポーネントに対応
*
*/

/** インクルード部 */
#include <Component/Game/Order/COrderManager.h>
#include <System/Utility/CSVLoader.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Order/COrder.h>
#include <System/Utility/Search.h>
#include <Scene/CGameManager.h>
#include <System/Systems/CTransformSystem.h>
#include <System/Sound/CSound.h>
#include <Scene/CSceneManager.h>

// コンポーネント
#include <Component/Game/Plant/CSprout.h>
#include <Component/Game/Plant/CFlower.h>
#include <Component/Game/Order/GameUI/COrderBoardUI.h>

/** マクロ定義 */
namespace
{
	const int ADDTIME = 60 * 13;	// 注文を追加する時間間隔
}

/**
* @brief	コンストラクタ
*/
COrderManager::COrderManager()
{

}


/**
* @brief	デストラクタ
*/
COrderManager::~COrderManager()
{

}


/**
* @brief	初期化処理
*/
HRESULT COrderManager::Init()
{
	// 注文データ読み込み
	LoadOrderDataFromCSV("data/csv/orderData/orderList.csv", 1, 0);

	// SEボリュームセット
	SOUND_MANAGER->SetVolume(SE_ORDER_BREAK, 4.0f);
	SOUND_MANAGER->SetVolume(SE_SHIP, 5.0f);
	// 変数初期化
	m_nCount = 60 * 10;

	return S_OK;
}


/**
* @brief	終了処理
*/
void COrderManager::Uninit()
{
	// 注文データのクリア
	m_orderDataList.clear();

	// 注文データオブジェクトの削除
	for (auto it = m_spOrderList.begin(); it != m_spOrderList.end();)
	{
		(*it)->RemoveComponentAll();
		it = m_spOrderList.erase(it);
	}
	m_spOrderList.clear();
}


/**
* @brief	更新処理
*/
void COrderManager::Update()
{
	// 注文を追加するか
	ShouldAddOrder();

	// UI移動用フラグ
	bool move = false;

	// 注文の更新
	for (auto order = m_spOrderList.begin(); order != m_spOrderList.end();)
	{	
		const auto& com = (*order)->GetComponent<COrder>();
		// 注文が削除された時、後ろの注文の移動フラグをONにする
		if (move)
		{
			const auto& uiCom = com.lock()->GetGameObject().lock()->GetComponent<COrderBoardUI>().lock();
			uiCom->MoveON();
		}

		// 更新できなかった場合注文削除
		if (!com.lock()->IsUpdate())
		{
			(*order)->RemoveComponentAll();
			// 注文削除
			order = m_spOrderList.erase(order);
			// SE再生
			SOUND_MANAGER->Play(SE_ORDER_BREAK);
			// 移動フラグON
			move = true;
		}
		else
		{
			order++;
		}
	}
}


/**
* @brief	描画処理
*/
void COrderManager::Draw()
{

}


/**
* @brief	注文を生成
* @param	data	作成する注文データ
* @return	std::weak_ptr<CGameObject>	生成したゲームオブジェクト
*/
std::weak_ptr<CGameObject> COrderManager::CreateOrder(COrderData data)
{
	// インスタンス化
	std::shared_ptr<CGameObject> spObj = std::make_shared<CGameObject>();
	// 自身を格納
	spObj->m_self = spObj;
	// 初期化
	spObj->Init();
	// コンポーネント追加
	const auto& spCom = spObj->AddComponent<COrder>();
	// 注文データセット
	spCom.lock()->SetOrderData(data);
	// リストに格納
	m_spOrderList.push_back(spObj);
	// 注文は別で管理するため、コンポーネントシステムから削除
	CTransformSystem* pSystem = SCENE_MANAGER->GetSystem<CTransformSystem>(EComponentType::Transform);
	if (pSystem != nullptr)	pSystem->RemoveList("Order");

	return spObj;
}


/**
* @brief	注文を追加するかどうか
*/
void COrderManager::ShouldAddOrder()
{
	m_nCount++;
	if (m_nCount >= ADDTIME)
	{
		// 注文リストからランダムで注文を決定
		int randomNum = rand() % m_orderDataList.size();
		COrderData data = m_orderDataList.at(randomNum);
		// 注文生成
		const auto& orderObj = CreateOrder(data);
		// カウントリセット
		m_nCount = 0;
	}
}


/**
* @brief	アイテムと注文を照合
* @param	itemObj		アイテムオブジェクト
* @return	bool		照合結果(true/一致,false/不一致)
*/
bool COrderManager::CheckOrder(std::weak_ptr<CGameObject> itemObj)
{
	// アイテムデータを注文データに変換
	COrderData itemData;
	if (itemObj.lock()->GetObjectID() == EObjectType::Potted)
	{
		itemData.m_bPotted = true;
		const auto& childList = itemObj.lock()->m_spTransform.lock()->GetChildList();
		const auto& item = SearchExistsList(childList, "Item");
		EObjectType id = item.lock()->GetObjectID();
		if (id == EObjectType::Sprout)
		{
			const auto& com = item.lock()->GetComponent<CSprout>();
			itemData.m_eColor = com.lock()->GetColor().colorType;
		}
		else if (id == EObjectType::Flower)
		{
			const auto& com = item.lock()->GetComponent<CFlower>();
			itemData.m_eColor = com.lock()->GetColor().colorType;
		}
		itemData.m_eKind = id;
	}
	else
	{
		itemData.m_bPotted = false;
		EObjectType id = itemObj.lock()->GetObjectID();
		if (id == EObjectType::Sprout)
		{
			const auto& com = itemObj.lock()->GetComponent<CSprout>();
			itemData.m_eColor = com.lock()->GetColor().colorType;
		}
		else if (id == EObjectType::Flower)
		{
			const auto& com = itemObj.lock()->GetComponent<CFlower>();
			itemData.m_eColor = com.lock()->GetColor().colorType;
		}
		itemData.m_eKind = id;
	}

	// UI移動用フラグ
	bool move = false;

	// 注文リストと照合
	for (auto it = m_spOrderList.begin(); it != m_spOrderList.end();)
	{
		// 注文データ取得
		const auto& com = (*it)->GetComponent<COrder>().lock();
		COrderData orderData = com->GetOrderData();

		// 注文が削除された時、後ろの注文の移動フラグをONにする
		if (move)
		{
			const auto& uiCom = com->GetGameObject().lock()->GetComponent<COrderBoardUI>().lock();
			uiCom->MoveON();
		}

		// 注文と照合
		if (orderData == itemData && !move)
		{
			// スコア加算
			GAME_MANAGER->AddScore(orderData.m_nScore);
			// SE再生
			SOUND_MANAGER->Play(SE_SHIP);
			// 注文の削除
			(*it)->RemoveComponentAll();
			it = m_spOrderList.erase(it);
			move = true;
		}
		else
		{
			++it;
		}
	}

	if (move)	return true;
	return false;
}