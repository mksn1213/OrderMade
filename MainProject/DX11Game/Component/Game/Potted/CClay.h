#pragma once
/**
*
* @file		CClay.h
* @brief	粘土クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/19	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 粘土クラス */
class CClay final : public CScriptBase
{
public:
	CClay();
	virtual ~CClay();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;

	/**
	* @brief	加工フラグセット
	* @param	flag	フラグのON/OFF
	*/
	void SetProcessedFlag(bool flag) { m_bProcessed = flag; }

	/**
	* @brief	加工フラグ取得
	* @return	bool	true/加工済み.false/未加工
	*/
	bool GetProcessedFlag() { return m_bProcessed; }

private:
	// 加工済みか
	bool	m_bProcessed;
};