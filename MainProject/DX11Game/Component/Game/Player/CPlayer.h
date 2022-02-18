#pragma once
/**
*
* @file		CPlayer.h
* @brief	プレイヤークラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/13  実装開始
* @date		2021/12/03	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <System/Utility/Vector3.h>

/** 前定義 */
class CRigidbody;
class CAssimpModel;

/** プレイヤークラス */
class CPlayer final : public CScriptBase
{
public:
	CPlayer();
	virtual ~CPlayer();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void MoveUpdate();
	void AngleUpdate();

	void OnCollision(std::weak_ptr<CCollider> collider)	override;
	void SetItem(std::weak_ptr<CGameObject> item);
	void ReleaseItem();

	/**
	* @brief	アイテムフラグの取得
	* @return	bool		アイテムフラグ
	*/
	bool GetItemFlag() { return m_bHasItem; }

	/**
	* @brief	アイテム取得
	* @return	std::weak_ptr<CGameObject>	もっているアイテム
	*/
	std::weak_ptr<CGameObject> GetItem() { return m_spItem; }



	/**
	* @brief	アクションフラグセット
	* @param	flag		アクションフラグ(true/アクション中,false/アクション未実施)
	*/
	void SetActionFlag(bool flag) { m_bIsAction = flag; }

	/**
	* @brief	アクションフラグ取得
	* @return	bool		アクションフラグ(true/アクション中 , false/アクション未実施)
	*/
	bool IsAction() { return m_bIsAction; }

private:
	// プレイヤーモデル情報(アニメーション用)
	CAssimpModel*				m_pModel;
	// プレイヤーのターゲットポイントオブジェクト
	std::weak_ptr<CGameObject>	m_spTargetPoint;
	// リジッドボディ
	std::weak_ptr<CRigidbody>	m_spRigidbody;
	// もっているアイテムオブジェクト
	std::weak_ptr<CGameObject>	m_spItem;
	// アイテムを持っているか
	bool						m_bHasItem;
	// アクション中かどうか
	bool						m_bIsAction;
	// 前回のアクションフラグ
	bool						m_bOldIsAction;
	// 目的角度
	Vector3 m_rotDest;
};
