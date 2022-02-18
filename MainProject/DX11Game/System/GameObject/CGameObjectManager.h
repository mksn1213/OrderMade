#pragma once
/**
*
* @file		CGameObjectManager.h
* @brief	ゲームオブジェクト管理クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	実装開始
* @date		2021/11/30	オブジェクト管理からゲームオブジェクト管理に変更
* @date		2022/01/23	シングルトン継承
*
*/

/** インクルード部 */
#include <System/Utility/Singleton.h>
#include <System/GameObject/CGameObject.h>
#include <System/Component/CTransform.h>
#include <list>
#include <memory>
#include <System/Utility/Vector3.h>
#include <System/Texture/CTexture.h>

#define GAMEOBJECT_MANAGER (CGameObjectManager::GetInstance())

/** オブジェクト管理クラス */
class CGameObjectManager final : public Singleton<CGameObjectManager>
{
public :
	CGameObjectManager();
	virtual ~CGameObjectManager();

	HRESULT Init()		override;
	void	Uninit()	override;

	/**
	* @brief	インスタンス化
	* @param	pos		生成座標
	* @return	T*		生成オブジェクト
	*/
	template <class T>
	std::weak_ptr<T> Instantiation(Vector3 pos = Vector3::zero())
	{
		// インスタンス化
		std::shared_ptr<T> spObj = std::make_shared<T>();
		// 自身を格納
		spObj->m_self = spObj;
		// 初期化
		spObj->Init();
		spObj->GetComponent<CTransform>().lock()->SetPosition(pos);
		// リストに格納
		m_spGameObjectList.push_back(spObj);

		return spObj;
	}

	/**
	* @brief	ゲームオブジェクト削除
	* @param	spObj	削除するゲームオブジェクト
	*/
	void DestroyGameObject(std::weak_ptr<CGameObject> spObj)
	{
		auto obj = spObj.lock();
		if (!obj)	return;

		// リストに含まれているか
		auto it = std::find(m_spGameObjectList.begin(), m_spGameObjectList.end(), obj);
		
		// リストになければ終了
		if (m_spGameObjectList.end() == it)	return;
		
		// 親が存在している場合親子関係を削除
		const auto& parentObj = obj->m_spTransform.lock()->GetParent();
		if (parentObj.lock())	parentObj.lock()->m_spTransform.lock()->ReleaseRelationship(spObj);

		// コライダーを持っていればコライダーリストから削除
		auto collider = obj->GetComponent<CCollider>();
		if (collider.lock())	CCollider::RemoveFromList(collider);

		// コンポーネント削除
		obj->RemoveComponentAll();

		// オブジェクトリストから削除
		m_spGameObjectList.erase(it);
	}

	/**
	* @brief	ゲームオブジェクトリスト取得
	* @return	std::list<std::shared_ptr<CGameObject>>	ゲームオブジェクトリスト
	*/
	std::list<std::shared_ptr<CGameObject>> GetGameObjectList() { return m_spGameObjectList; }

private:
	// ゲームオブジェクトリスト
	std::list<std::shared_ptr<CGameObject>> m_spGameObjectList;
};