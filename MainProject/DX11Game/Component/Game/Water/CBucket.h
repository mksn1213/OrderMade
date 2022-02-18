#pragma once
/**
*
* @file		CBucket.h
* @brief	バケツクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/17  実装開始
* @date		2021/12/17	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** バケツクラス */
class CBucket final : public CScriptBase
{
public:
	CBucket();
	virtual ~CBucket();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;

	/**
	* @brief	水フラグセット
	* @param	flag	フラグのON/OFF
	*/
	void SetWaterFlag(bool flag) { m_bHasWater = flag; }

	/**
	* @brief	水フラグ取得
	* @return	bool	true/水を持っている,false/水を持っていない
	*/
	bool GetWaterFlag() { return m_bHasWater; }

	// 水メッシュオブジェクト
	std::weak_ptr<CGameObject>	m_spWaterObj;

private:
	// 水を持っているか
	bool	m_bHasWater;
};