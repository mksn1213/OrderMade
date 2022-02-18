#pragma once
/**
*
* @file		CScriptBase.h
* @brief	スクリプトベースクラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CComponent.h>

class CTransform;
class CCollider;
/** スクリプトベースクラス */
class CScriptBase :public CComponent
{
public:
	CScriptBase();
	virtual ~CScriptBase();

	virtual void OnCreate()		override;
	virtual void OnDestroy()	override;
	virtual void Update()		override {}

	// 当たり判定
	virtual void OnCollision(std::weak_ptr<CCollider> collider) {}

	// アクションがあるかどうか
	virtual bool ExistsProcess(std::weak_ptr<CCollider> collider) { return false; }

	// アクションがあるかどうか(アイテムを持っているとき)
	virtual bool ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> item) { return false; }

protected:
	// アタッチしているゲームオブジェクトのトランスフォーム
	std::weak_ptr<CTransform>	m_spTransform;

public:
	// コンポーネントID
	static const EComponentType comID;
};
