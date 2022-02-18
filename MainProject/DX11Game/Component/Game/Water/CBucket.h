#pragma once
/**
*
* @file		CBucket.h
* @brief	�o�P�c�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/17  �����J�n
* @date		2021/12/17	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �o�P�c�N���X */
class CBucket final : public CScriptBase
{
public:
	CBucket();
	virtual ~CBucket();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;

	/**
	* @brief	���t���O�Z�b�g
	* @param	flag	�t���O��ON/OFF
	*/
	void SetWaterFlag(bool flag) { m_bHasWater = flag; }

	/**
	* @brief	���t���O�擾
	* @return	bool	true/���������Ă���,false/���������Ă��Ȃ�
	*/
	bool GetWaterFlag() { return m_bHasWater; }

	// �����b�V���I�u�W�F�N�g
	std::weak_ptr<CGameObject>	m_spWaterObj;

private:
	// ���������Ă��邩
	bool	m_bHasWater;
};