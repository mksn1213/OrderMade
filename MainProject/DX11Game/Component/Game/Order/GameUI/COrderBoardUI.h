#pragma once
/**
*
* @file		COrderBoardUI.h
* @brief	����(�Ŕ�)UI�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;
class COrderData;

/** �����Ŕ�UI�N���X */
class COrderBoardUI final : public CScriptBase
{
public:
	COrderBoardUI();
	virtual ~COrderBoardUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetOrder(COrderData data);

	/**
	* @brief	�ړ��t���OON
	*/
	void MoveON()
	{
		m_bMoveFlag = true;
		m_fRemainingDistance += 150.0f;
	}

private:
	// �X�v���C�g�����_���[
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// �ړ��t���O
	bool							m_bMoveFlag;
	// �ړ���
	float							m_fRemainingDistance;
	// SE�Đ��ς��ǂ���
	bool							m_bIsPlaySound;
};
