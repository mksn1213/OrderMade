#pragma once
/**
*
* @file		CResultScore.h
* @brief	���U���g�X�R�A�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>

/** �O��` */
class CSpriteRenderer;

/** ���U���g�X�R�A�N���X */
class CResultScore final : public CScriptBase
{
public:
	CResultScore();
	virtual ~CResultScore();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetScore(int nScore);

private:
	// �X�R�A
	std::weak_ptr<CSpriteRenderer>	m_spRenderer[4];
};