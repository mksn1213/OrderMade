#pragma once
/**
*
* @file		CScriptBase.h
* @brief	�X�N���v�g�x�[�X�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CComponent.h>

class CTransform;
class CCollider;
/** �X�N���v�g�x�[�X�N���X */
class CScriptBase :public CComponent
{
public:
	CScriptBase();
	virtual ~CScriptBase();

	virtual void OnCreate()		override;
	virtual void OnDestroy()	override;
	virtual void Update()		override {}

	// �����蔻��
	virtual void OnCollision(std::weak_ptr<CCollider> collider) {}

	// �A�N�V���������邩�ǂ���
	virtual bool ExistsProcess(std::weak_ptr<CCollider> collider) { return false; }

	// �A�N�V���������邩�ǂ���(�A�C�e���������Ă���Ƃ�)
	virtual bool ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> item) { return false; }

protected:
	// �A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃g�����X�t�H�[��
	std::weak_ptr<CTransform>	m_spTransform;

public:
	// �R���|�[�l���gID
	static const EComponentType comID;
};
