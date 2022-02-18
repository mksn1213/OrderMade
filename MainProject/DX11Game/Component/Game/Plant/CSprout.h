#pragma once
/**
*
* @file		CSprout.h
* @brief	��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/08	�����J�n
* @date		2021/12/19	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <System/Utility/CColor.h>

/** ��N���X */
class CSprout final : public CScriptBase
{
public:
	CSprout();
	virtual ~CSprout();

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
	* @return	CColor		�F���
	*/
	CColor GetColor() { return m_eColor; }

private:
	CColor m_eColor;
};