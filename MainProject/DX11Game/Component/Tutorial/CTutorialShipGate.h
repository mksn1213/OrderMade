#pragma once
/**
*
* @file		CTutorialShipGate.h
* @brief	チュートリアル用出荷ゲートクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <vector>

/** チュートリアル用出荷ゲートクラス */
class CTutorialShipGate final : public CScriptBase
{
public:
	CTutorialShipGate();
	virtual ~CTutorialShipGate();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)	override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> item)	override;
	
private:
	std::vector<std::weak_ptr<CGameObject>>	m_spTruckList;
};