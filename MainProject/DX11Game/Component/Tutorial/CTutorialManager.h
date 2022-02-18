#pragma once
/**
*
* @file		CTutorialManager.h
* @brief	�`���[�g���A���Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Utility/Singleton.h>
#include <memory>

#define TUTORIAL_MANAGER	(CTutorialManager::GetInstance())

/** �O��` */
class CTutorialMessageUI;
class CTutorialOperateUI;

/** �`���[�g���A���Ǘ��N���X */
class CTutorialManager final : public Singleton<CTutorialManager>
{
public:
	CTutorialManager();
	~CTutorialManager();

	HRESULT Init()		override;
	void	Uninit()	override;
	void	Update();
	void	Draw();

	/**
	* @brief	�X�e�[�W�ԍ��Z�b�g
	* @param	nStageNo	�X�e�[�W�ԍ�
	*/
	void SetStageNo(int nStageNo);

	/**
	* @brief	�X�e�[�W�ԍ��擾
	* @param	int		�X�e�[�W�ԍ�
	*/
	int GetStageNo() { return m_nStageNo; }

	/**
	* @brief	�I��
	*/
	void Fin() { m_bIsFin = true; }

private:
	// ���b�Z�[�WUI�I�u�W�F�N�g
	std::weak_ptr<CTutorialMessageUI>	m_spMessageCom;
	// ����UI�I�u�W�F�N�g
	std::weak_ptr<CTutorialOperateUI>	m_spOperateCom;
	// �X�e�[�W�ԍ�
	int		m_nStageNo;
	// �I���t���O
	bool	m_bIsFin;
	// �����t���O
	bool	m_bIsCreate;
};

