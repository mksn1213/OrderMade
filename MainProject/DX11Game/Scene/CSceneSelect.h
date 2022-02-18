#pragma once
/**
*
* @file		CSceneSelect.h
* @brief	�Z���N�g�V�[���N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
* @date		2021/12/03	�x�[�X�N���X�̕ύX
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneBase.h>

/** �Z���N�g�V�[���N���X */
class CSceneSelect final : public CSceneBase
{
public:
	CSceneSelect();
	virtual ~CSceneSelect();

	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
};