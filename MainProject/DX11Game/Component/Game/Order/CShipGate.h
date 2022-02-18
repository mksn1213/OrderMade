#pragma once
/**
*
* @file		CShipGate.h
* @brief	出荷ゲートクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <vector>

/** 出荷ゲートクラス */
class CShipGate final : public CScriptBase
{
public:
	CShipGate();
	virtual ~CShipGate();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)	override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> item)	override;

private:
	std::vector<std::weak_ptr<CGameObject>>	m_spTruckList;
};