#pragma once
/**
*
* @file		CSceneTitle.h
* @brief	�^�C�g���V�[���N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
* @date		2021/12/03	�x�[�X�N���X�̕ύX
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneBase.h>


/** �^�C�g���V�[���N���X */
class CSceneTitle final : public CSceneBase
{
public:
	CSceneTitle();
	virtual ~CSceneTitle();

	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
};