#pragma once
/**
*
* @file		CSceneTutorial.h
* @brief	�`���[�g���A���V�[���N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/10	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneBase.h>

/** �`���[�g���A���V�[���N���X */
class CSceneTutorial final : public CSceneBase
{
public:
	CSceneTutorial();
	virtual ~CSceneTutorial();

	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;

	/**
	* @brief	�X�e�[�W�ԍ��Z�b�g
	* @param	nStageNo	�X�e�[�W�ԍ�
	*/
	void SetStageNo(int nStageNo) { m_nStageNo = nStageNo; }

	/**
	* @brief	�X�e�[�W�ԍ��擾
	* @return	int		�X�e�[�W�ԍ�
	*/
	int GetStageNo() { return m_nStageNo; }

private:
	// �X�e�[�W�ԍ�
	int m_nStageNo;
};