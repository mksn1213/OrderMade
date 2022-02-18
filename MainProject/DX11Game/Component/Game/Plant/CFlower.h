#pragma once
/**
*
* @file		CFlower.h
* @brief	�ԃN���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/09	�����J�n
* @date		2021/12/19	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <System/Utility/CColor.h>

/** �ԃN���X */
class CFlower final : public CScriptBase
{
public:
	CFlower();
	virtual ~CFlower();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)	override;

	/**
	* @brief	�F�̃Z�b�g
	* @param	color		�Z�b�g����F���
	*/
	void SetColor(CColor color);

	/**
	* @brief	�F���̎擾
	* @return	CColor	�F���
	*/
	CColor GetColor() { return m_eColor; }

private:
	CColor m_eColor;
};