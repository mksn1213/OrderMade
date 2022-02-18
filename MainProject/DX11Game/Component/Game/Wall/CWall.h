#pragma once
/**
*
* @file		CWall.h
* @brief	�ǃN���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/10	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �ǃN���X */
class CWall final : public CScriptBase
{
public:
	CWall();
	virtual ~CWall();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)	override;
};