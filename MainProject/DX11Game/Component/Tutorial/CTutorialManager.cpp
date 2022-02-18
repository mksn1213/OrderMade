/**
*
* @file		CTutorialManager.cpp
* @brief	�`���[�g���A���Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Tutorial/CTutorialManager.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneTutorial.h>
#include <System/GameObject/CGameObjectManager.h>

// �R���|�[�l���g
#include <Component/Tutorial/CTutorialMessageUI.h>
#include <Component/Tutorial/CTutorialOperateUI.h>
#include <Component/Tutorial/CTutorialClearUI.h>

/** �}�N����`*/
namespace
{
	const Vector3 TEX_POS1 = Vector3(900.0f, 0.0f, 0.0f);
	const Vector3 TEX_POS2 = Vector3(450.0f, -50.0f, 0.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CTutorialManager::CTutorialManager()
{

}


/**
* @brief	�f�X�g���N�^
*/
CTutorialManager::~CTutorialManager()
{

}


/**
* @brief	����������
*/
HRESULT CTutorialManager::Init()
{
	// �ϐ�������
	m_bIsFin = false;
	m_bIsCreate = false;

	// �`���[�g���A������UI
	const auto& operateObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS2).lock();
	m_spOperateCom = operateObj->AddComponent<CTutorialOperateUI>();

	// �`���[�g���A�����b�Z�[�WUI
	const auto& messageObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS1).lock();
	m_spMessageCom = messageObj->AddComponent<CTutorialMessageUI>();

	return S_OK;
}


/**
* @brief	�I������
*/
void CTutorialManager::Uninit()
{

}


/**
* @brief	�X�V����
*/
void CTutorialManager::Update()
{
	// �`���[�g���A���I���t���O���������ꍇ
	if (m_bIsFin)
	{
		if (!m_bIsCreate)
		{
			// �N���AUI����
			const auto& obj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
			obj->AddComponent<CTutorialClearUI>();
			m_bIsCreate = true;
		}
	}
}


/**
* @brief	�`�揈��
*/
void CTutorialManager::Draw()
{

}


/**
* @brief	�X�e�[�W�ԍ��Z�b�g
* @param	nStageNo	�X�e�[�W�ԍ�
*/
void CTutorialManager::SetStageNo(int nStageNo)
{
	m_nStageNo = nStageNo;
	m_spMessageCom.lock()->SetTexture(m_nStageNo);
	m_spOperateCom.lock()->SetTexture(m_nStageNo);
}