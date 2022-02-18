#pragma once
/**
*
* @file		CClay.h
* @brief	�S�y�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/19	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �S�y�N���X */
class CClay final : public CScriptBase
{
public:
	CClay();
	virtual ~CClay();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;

	/**
	* @brief	���H�t���O�Z�b�g
	* @param	flag	�t���O��ON/OFF
	*/
	void SetProcessedFlag(bool flag) { m_bProcessed = flag; }

	/**
	* @brief	���H�t���O�擾
	* @return	bool	true/���H�ς�.false/�����H
	*/
	bool GetProcessedFlag() { return m_bProcessed; }

private:
	// ���H�ς݂�
	bool	m_bProcessed;
};