#pragma once
/**
*
* @file		CSelectGateUI.h
* @brief	�Z���N�g�Q�[�gUI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <Component/Select/CSelectGate.h>

/** �O��` */
class CMeshRenderer;

/** �Z���N�g�Q�[�gUI�N���X */
class CSelectGateUI final : public CScriptBase
{
public:
	CSelectGateUI();
	virtual ~CSelectGateUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetTexture(CSelectGate::EGateType type);

private:
	std::weak_ptr<CMeshRenderer>	m_spRenderer;
};