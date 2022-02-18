#pragma once
/**
*
* @file		CPotted.h
* @brief	���A���N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	�����J�n
* @date		2021/12/19	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** ���A���N���X */
class CPotted final : public CScriptBase
{
public:
	CPotted();
	virtual ~CPotted();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
};