/**
*
* @file		CAction.cpp
* @brief	�A�N�V�����x�[�X�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/26	�����J�n
* @date		2021/12/16	�R���|�[�l���g�ɕύX
* @date		2021/12/28	�A�N�V�����Q�[�WUI���������쐬
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/CAction.h>
#include <System/CTimer.h>
#include <System/Defines.h>

#include <System/GameObject/CGameObjectManager.h>
#include <Component/Game/Player/Action/GameUI/CActionGaugeUI.h>
#include <Component/Game/Player/Action/GameUI/CActionGaugeBaseUI.h>

/** �ÓI�����o */
const EComponentType CAction::comID = EComponentType::Action;

/**
* @brief	�R���X�g���N�^
*/
CAction::CAction()
	: m_pTimer(nullptr)
{

}


/**
* @brief	�f�X�g���N�^
*/
CAction::~CAction()
{
	SAFE_DELETE(m_pTimer);
}


/**
* @brief	�X�V�o���邩
* @return	bool	�X�V�̉�(true/�X�V�\ , false/�I��)
*/
bool CAction::IsUpdate()
{
	// �^�C�}�[�̍X�V
	if (!m_pTimer->Update())	return false;
	return true;
}


/**
* @brief	�A�N�V�����Q�[�WUI����
* @param	time		�A�N�V�����ɂ����鎞��
* @param	dir			�����������
* @param	distance	�������鋗��
*/
void CAction::CreateActionGauge(int time, EDirection dir, float distance, EDirection dir2, float distance2)
{
	// �A�N�V�����Q�[�WUI�̐���
	m_spActionGauge = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& gaugeBaseCom = m_spActionGauge.lock()->AddComponent<CActionGaugeBaseUI>().lock();

	const auto& gaugeObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& gaugeCom = gaugeObj->AddComponent<CActionGaugeUI>().lock();
	gaugeCom->SetActionTime(time);

	// �e�q�֌W�����
	CTransform::SetParentChildRelation(m_spGameObject, m_spActionGauge, dir, distance, dir2, distance2);
	CTransform::SetParentChildRelation(m_spActionGauge, gaugeObj, EDirection::Front, 0.05f,EDirection::Left,10.0f/1.5f);
}


/**
* @brief	�A�N�V�����Q�[�WUI�폜
*/
void CAction::DeleteActionGauge()
{
	m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(m_spActionGauge);
	m_spActionGauge.lock()->Destroy();
}