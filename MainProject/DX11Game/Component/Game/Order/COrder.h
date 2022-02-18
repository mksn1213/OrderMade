#pragma once
/**
*
* @file		COrder.h
* @brief	�����N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	�����J�n
* @date		2021/12/21	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CComponent.h>
#include <Component/Game/Order/COrderData.h>

/** �O��` */
class CTimer;
class CSpriteRenderer;

/** �����N���X */
class COrder final : public CComponent
{
public:
	COrder();
	virtual ~COrder();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
	bool IsUpdate();

	void CreateUI();
	void SetOrderTexture();

	/**
	* @brief	�f�[�^�Z�b�g
	* @param	data	�Z�b�g���钍���f�[�^
	*/
	void SetOrderData(COrderData data) 
	{ 
		m_orderData = data;
		CreateUI();
	}

	/**
	* @brief	�f�[�^�擾
	* @return	COrderData	�����f�[�^
	*/
	COrderData GetOrderData() { return m_orderData; }

	/**
	* @brief	UI�I�u�W�F�N�g�擾
	* @return	std::weak_ptr<CGameObject>
	*/
	std::weak_ptr<CGameObject>	GetGameObject() { return m_spSpriteObject; }

private:
	// �����f�[�^��UI�I�u�W�F�N�g
	std::weak_ptr<CGameObject>		m_spSpriteObject;
	// �����f�[�^��UI�X�v���C�g
	std::weak_ptr<CSpriteRenderer>	m_spSpriteRenderer;
	// �����f�[�^
	COrderData	m_orderData;
	// ������������
	CTimer*		m_pTimer;
public:
	// �R���|�[�l���gID
	static const EComponentType comID;
};