#pragma once
/**
*
* @file		CAction.h
* @brief	アクションベースクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/26	実装開始
* @date		2021/12/16	コンポーネントに変更
* @date		2022/01/30	CScriptBaseを継承
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <System/Component/CTransform.h>

class CGameObject;
class CTimer;
/** アクションベースクラス */
class CAction :public CScriptBase
{
public:
	CAction();
	virtual ~CAction();

	virtual void EndProcess() {}
	bool IsUpdate();

	/**
	* @brief	アクションを行うオブジェクトのセット
	* @param	spTargetObj		アクションの対象オブジェクト
	* @param	spTargetItem	アクションの対象アイテムオブジェクト
	*/
	void SetTarget(std::weak_ptr<CGameObject> spTargetObj, std::weak_ptr<CGameObject> spTargetItem)
	{
		m_spTargetObject = spTargetObj;
		m_spTargetItem = spTargetItem;
	}

protected:
	// アクションの終了判定を行うタイマー
	CTimer* m_pTimer;

	// アクションの対象オブジェクト
	std::weak_ptr<CGameObject>	m_spTargetObject;

	// アクションの対象アイテム
	std::weak_ptr<CGameObject>	m_spTargetItem;

	// アクションゲージオブジェクト
	std::weak_ptr<CGameObject>	m_spActionGauge;

	void CreateActionGauge(int time, EDirection dir, float distance, EDirection dir2 = EDirection::Front, float distance2 = 0.0f);
	void DeleteActionGauge();

public:
	// コンポーネントID
	static const EComponentType comID;
};
