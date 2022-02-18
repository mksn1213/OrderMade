#pragma once
/**
*
* @file		CIconUI.h
* @brief	�A�C�R��UI�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/28	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <System/Resource/TextureID.h>

class CColor;
class CMeshRenderer;
/** �A�C�R��UI�N���X */
class CIconUI final : public CScriptBase
{
public:
	CIconUI();
	virtual ~CIconUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetIconTexture(ETexture type);
	void SetIconTexture(CColor color);

	/**
	* @brief	�ړ��t���OON
	* @param	�ړ�����
	*/
	void MoveON(float distance)
	{
		m_bMoveFlag = true;
		m_fRemainingDistance += distance;
	}

private:
	// ���b�V�������_���[
	std::weak_ptr<CMeshRenderer>	m_spRenderer;
	// �ړ��t���O
	bool							m_bMoveFlag;
	// �ړ���
	float							m_fRemainingDistance;
};