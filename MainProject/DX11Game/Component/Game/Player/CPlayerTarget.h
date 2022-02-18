#pragma once
/**
*
* @file		CPlayerTarget.h
* @brief	プレイヤーターゲットクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/20	実装開始
* @date		2021/12/03	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

class CPlayer;
/** プレイヤーターゲットクラス */
class CPlayerTarget final : public CScriptBase
{
public:
	CPlayerTarget();
	virtual ~CPlayerTarget();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider);

	/**
	* @brief	ターゲット決定状態へ
	*/
	void TargetON() { m_bIsTarget = true; }

	/**
	* @brief	ターゲットが決まっているか
	* @return	bool	true/決まっている,false/決まっていない
	*/
	bool IsTarget() { return m_bIsTarget; }

	// 親(プレイヤー)コンポーネント
	std::weak_ptr<CPlayer> m_spPlayer;

private:
	// ターゲットが決まっているか
	bool	m_bIsTarget;
};