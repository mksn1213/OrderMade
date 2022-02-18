#pragma once
/**
*
* @file		CSceneResult.h
* @brief	���U���g�V�[���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneBase.h>

/**  ���U���g�V�[���N���X */
class CSceneResult final : public CSceneBase
{
public:
	CSceneResult();
	virtual ~CSceneResult();

	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;

	/**
	* @brief	�X�R�A�Z�b�g
	* @param	nScore	�X�R�A
	*/
	void SetScore(int nScore) { m_nScore = nScore; }

private:
	int m_nScore;
};