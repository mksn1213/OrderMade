#pragma once
/**
*
* @file		CShipGate.h
* @brief	�o�׃Q�[�g�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/11	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <vector>

/** �o�׃Q�[�g�N���X */
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