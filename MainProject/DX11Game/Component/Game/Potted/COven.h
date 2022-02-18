#pragma once
/**
*
* @file		COvec.h
* @brief	竈クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/11	コンポーネントに変更
* @date		2021/12/19	アクション追加
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 竈クラス */
class COven final : public CScriptBase
{
public:
	COven();
	virtual ~COven();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> item)	override;

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
	// アクション中かどうか
	bool	m_bIsAction;
	// 前回のアクションフラグ
	bool	m_bOldIsAction;
};