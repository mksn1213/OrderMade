#pragma once
/**
*
* @file		COrderManager.h
* @brief	�����Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	�����J�n
* @date		2021/12/21	�R���|�[�l���g�ɑΉ�
* @date		2022/01/30	�V���O���g���p��
*
*/

/** �C���N���[�h�� */
#include <System/Utility/Singleton.h>
#include <System/Defines.h>
#include <vector>
#include <memory>
#include <Component/Game/Order/COrderData.h>
#include <System/GameObject/CGameObject.h>

#define ORDER_MANAGER	(COrderManager::GetInstance())

/** �����Ǘ��N���X */
class COrderManager final : public Singleton<COrderManager>
{
public:
	COrderManager();
	virtual ~COrderManager();

	HRESULT Init()	override;
	void Uninit()	override;
	void Update();
	void Draw();

	/**
	* @brief	�����f�[�^�̒ǉ�
	* @param	data	�ǉ�����f�[�^
	*/
	void AddOrderData(COrderData data) { m_orderDataList.push_back(data); }

	/**
	* @brief	�����̐��擾
	* @return	int		���݂̒�����
	*/
	int GetOrderQuantity() { return m_spOrderList.size(); }

	std::weak_ptr<CGameObject> CreateOrder(COrderData data);
	void ShouldAddOrder();
	bool CheckOrder(std::weak_ptr<CGameObject> itemObj);

private:
	// ���݂��钍���p�^�[�����X�g
	std::vector<COrderData>						m_orderDataList;
	// ���݂̒������X�g
	std::vector<std::shared_ptr<CGameObject>>	m_spOrderList;
	// ���������Ԋu�p
	int											m_nCount;
};
