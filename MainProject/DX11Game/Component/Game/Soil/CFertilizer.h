#pragma once
/**
*
* @file		CFertilizer.h
* @brief	�엿�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/16  �����J�n
* @date		2021/12/20	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <System/Utility/CColor.h>

/** �O��` */
class CMeshRenderer;

/** �엿�N���X */
class CFertilizer final : public CScriptBase
{
public:
	CFertilizer();
	virtual ~CFertilizer();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;

	void SetColor(CColor::EColor color);

	/**
	* @brief	�F���擾
	* @return	CColor		�F���
	*/
	CColor GetColor() { return m_eColor; }

private:
	// �F���
	CColor m_eColor;
	// ���b�V�������_���[
	std::weak_ptr<CMeshRenderer>	m_spRenderer;
};