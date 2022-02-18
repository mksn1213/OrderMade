#pragma once
/**
*
* @file		CFertilizerBag.h
* @brief	�엿�܃N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/16	�����J�n
* @date		2021/12/11	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <System/Utility/CColor.h>

/** �엿�܃N���X */
class CFertilizerBag final : public CScriptBase
{
public:
	CFertilizerBag();
	virtual ~CFertilizerBag();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;

	void SetColor(CColor::EColor color);
	std::weak_ptr<CGameObject> Create();

private:
	// �F���
	CColor m_eColor;
};