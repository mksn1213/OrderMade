#pragma once
/**
*
* @file		CSceneGame.h
* @brief	�Q�[���V�[���N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
* @date		2021/12/03	�x�[�X�N���X�̕ύX
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneBase.h>

/** �Q�[���V�[���N���X */
class CSceneGame final : public CSceneBase
{
public:
	CSceneGame();
	virtual ~CSceneGame();
	
	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;

private:
	// �V�[���J�ڗp
	int m_nFrame;
};