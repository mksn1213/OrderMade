#pragma once
/**
*
* @file		CClayBox.h
* @brief	�S�y���N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/11	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �S�y���N���X */
class CClayBox final : public CScriptBase
{
public:
	CClayBox();
	virtual ~CClayBox();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
};