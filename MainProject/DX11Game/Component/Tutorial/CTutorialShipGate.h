#pragma once
/**
*
* @file		CTutorialShipGate.h
* @brief	�`���[�g���A���p�o�׃Q�[�g�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <vector>

/** �`���[�g���A���p�o�׃Q�[�g�N���X */
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