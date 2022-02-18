#pragma once
/**
*
* @file		CSeed.h
* @brief	��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/17  �����J�n
* @date		2021/12/14	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** ��N���X */
class CSeed final : public CScriptBase
{
public:
	CSeed();
	virtual ~CSeed();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
};