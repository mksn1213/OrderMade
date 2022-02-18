#pragma once
/**
*
* @file		CTrashBox.h
* @brief	���ݔ��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/30	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** ���ݔ��N���X */
class CTrashBox final : public CScriptBase
{
public:
	CTrashBox();
	virtual ~CTrashBox();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)	override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> item)	override;
};