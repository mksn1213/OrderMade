#pragma once
/**
*
* @file		CCollider.h
* @brief	コライダークラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	実装開始
* @date		2021/12/05	collisionクラスからcolliderクラスに変更
*						コンポーネント化
*
*/

/** インクルード部 */
#include <System/Component/CComponent.h>
#include <System/Utility/Vector3.h>
#include <list>
#include <memory>

// 前定義
class CTransform;
class CScriptBase;
class CRigidbody;
class CMeshRenderer;

/** コライダークラス */
class CCollider final : public CComponent
{
public:
	CCollider();
	virtual ~CCollider();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	/**
	* @brief	当たり判定のもとにするかどうかフラグセット
	* @param	flag		フラグのON/OFF
	*/
	void SetCollisionFlag(bool flag) { m_bIsCollision = flag; }

	/**
	* @brief	コライダーサイズ取得
	* @return	Vector3		コライダーサイズ
	*/
	Vector3 GetColliderSize() { return m_colliderSize; }

	/**
	* @brief	指定のコライダーをリストから削除
	* @param	collider	削除するコライダー
	*/
	static void RemoveFromList(std::weak_ptr<CCollider> collider)
	{
		// コライダーリストに含まれていれば削除
		for (auto it = m_spColliderList.begin(); it != m_spColliderList.end();)
		{
			if (collider.lock() == it->lock())
			{
				m_spColliderList.erase(it);
				break;
			}
			else
			{
				++it;
			}
		}
	}

	/**
	* @brief	リストクリア
	*/
	static void ClearList() { m_spColliderList.clear(); }

	void CheckCollision(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other);

	// アタッチしているゲームオブジェクトのトランスフォーム
	std::weak_ptr<CTransform> m_spTransform;

	// リジッドボディ取得
	const std::weak_ptr<CRigidbody>& GetRigidbody() { return m_spRigidbody; }

	// 当たり判定処理を行うスクリプト
	CScriptBase* m_pMainScript;

public:
	/**
	* @enum		EColliderType
	* @brief	コライダータイプ
	*/
	enum EColliderType
	{
		Box = 0,
		Sphere,

		MaxHitType
	};

	void SetColliderSize(EColliderType type, Vector3 size, Vector3 center = Vector3::zero());
	void SetCenter(Vector3 center) { m_center = center; }
	Vector3 GetCenter() { return m_center; }

private:
	// 当たり判定用コライダーリスト
	static std::list<std::weak_ptr<CCollider>>	m_spColliderList;
	// 当たり判定を行う元になるかどうか
	bool							m_bIsCollision;
	// 当たり判定サイズ
	Vector3							m_colliderSize;
	// 中心座標
	Vector3							m_center;
	// コライダー形状
	EColliderType					m_eColliderType;
	// リジッドボディ
	std::weak_ptr<CRigidbody>		m_spRigidbody;
	// TODO : デバッグ用
	std::weak_ptr<CMeshRenderer>	m_spRenderer;

public:
	static const EComponentType comID;
};