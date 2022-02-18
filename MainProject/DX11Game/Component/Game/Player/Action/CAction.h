#pragma once
/**
*
* @file		CAction.h
* @brief	�A�N�V�����x�[�X�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/26	�����J�n
* @date		2021/12/16	�R���|�[�l���g�ɕύX
* @date		2022/01/30	CScriptBase���p��
*
*/

/** �C���N���[�h�� */
#include <System/Component/CScriptBase.h>
#include <System/Component/CTransform.h>

class CGameObject;
class CTimer;
/** �A�N�V�����x�[�X�N���X */
class CAction :public CScriptBase
{
public:
	CAction();
	virtual ~CAction();

	virtual void EndProcess() {}
	bool IsUpdate();

	/**
	* @brief	�A�N�V�������s���I�u�W�F�N�g�̃Z�b�g
	* @param	spTargetObj		�A�N�V�����̑ΏۃI�u�W�F�N�g
	* @param	spTargetItem	�A�N�V�����̑ΏۃA�C�e���I�u�W�F�N�g
	*/
	void SetTarget(std::weak_ptr<CGameObject> spTargetObj, std::weak_ptr<CGameObject> spTargetItem)
	{
		m_spTargetObject = spTargetObj;
		m_spTargetItem = spTargetItem;
	}

protected:
	// �A�N�V�����̏I��������s���^�C�}�[
	CTimer* m_pTimer;

	// �A�N�V�����̑ΏۃI�u�W�F�N�g
	std::weak_ptr<CGameObject>	m_spTargetObject;

	// �A�N�V�����̑ΏۃA�C�e��
	std::weak_ptr<CGameObject>	m_spTargetItem;

	// �A�N�V�����Q�[�W�I�u�W�F�N�g
	std::weak_ptr<CGameObject>	m_spActionGauge;

	void CreateActionGauge(int time, EDirection dir, float distance, EDirection dir2 = EDirection::Front, float distance2 = 0.0f);
	void DeleteActionGauge();

public:
	// �R���|�[�l���gID
	static const EComponentType comID;
};
