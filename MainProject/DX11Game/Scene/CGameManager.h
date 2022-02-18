#pragma once
/**
*
* @file		CGameManager.h
* @brief	�Q�[���Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/12	�����J�n
* @date		2022/01//30	�V���O���g���p��
*
*/

/** �C���N���[�h�� */
#include <System/Utility/Singleton.h>
#include <System/CTimer.h>
#include <memory>

#define GAME_MANAGER	(CGameManager::GetInstance())

/** �O��` */
class CGameObject;
class CTimeUpUI;
class CSpriteRenderer;

/** �Q�[���Ǘ��N���X */
class CGameManager final : public Singleton<CGameManager>
{
public:
	CGameManager();
	~CGameManager();
	
	HRESULT Init()		override;
	void	Uninit()	override;
	void	Update();
	void	Draw();

	/**
	* @brief	�X�R�A���Z
	* @param	score	���Z����X�R�A
	*/
	void AddScore(int score) { m_nScore += score; }

	/**
	* @brief	�X�R�A�擾
	* @return	int		���݂̃X�R�A
	*/
	int GetScore() { return m_nScore; }

	/**
	* @brief	���Ԏ擾
	* @return	int		�c�莞��
	*/
	int GetTime() { return m_pTimer->GetTime(); }

	/**
	* @brief	�|�[�Y�����ǂ���
	* @return	bool	�|�[�Y����(true/�|�[�Y��,false/�|�[�Y���ł͂Ȃ�)
	*/
	bool IsPause() { return m_bIsPause; }

	/**
	* @brief	�Q�[�����I��������
	* @return	bool	�Q�[���I��������(true/�I��,false/�Q�[����)
	*/
	bool IsGameFin() { return m_bGameFin; }

private:
	// �X�R�A
	int			m_nScore;
	// ��������
	CTimer*		m_pTimer;
	// �|�[�Y��ON/OFF
	bool		m_bIsPause;
	// �Q�[���I���t���O
	bool		m_bGameFin;
	// �Q�[���J�n�t���O
	bool		m_bGameStart;
	// �J�E���g�_�E���p
	int			m_nFrame;
	// �|�[�Y���̑I��p
	bool		m_bSelect;
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// �|�[�Y�I�u�W�F�N�g
	std::weak_ptr<CGameObject>		m_spPauseUIObj;
	// �I��UI�I�u�W�F�N�g
	std::shared_ptr<CGameObject>	m_spFinUIObj;
	// �I��UI�X�N���v�g
	std::weak_ptr<CTimeUpUI>		m_spFinUIScript;
};