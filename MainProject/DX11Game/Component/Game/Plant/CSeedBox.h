#pragma once
/**
*
* @file		CSeedBox.h
* @brief	�픠�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/11	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �픠�N���X */
class CSeedBox final : public CScriptBase
{
public:
	CSeedBox();
	virtual ~CSeedBox();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
};