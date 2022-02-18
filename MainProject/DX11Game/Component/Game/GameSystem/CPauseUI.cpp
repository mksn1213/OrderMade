/**
*
* @file		CPauseUI.cpp
* @brief	�|�[�YUI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/GameSystem/CPauseUI.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Scene/CGameManager.h>
#include <System/CInput.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>
#include <Component/Game/GameSystem/CGameBackUI.h>
#include <Component/Game/GameSystem/CGameFinUI.h>

/** �}�N����` */
namespace
{
	const Vector3 TEX_SIZE = Vector3(1280.0f, 720.0f, 1.0f);
	const Vector3 TEX_POS1 = Vector3(200.0f, 250.0f, 0.0f);
	const Vector3 TEX_POS2 = Vector3(-200.0f, 250.0f, 0.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CPauseUI::CPauseUI()
	: m_bBackGame(true)
{

}


/**
* @brief	�f�X�g���N�^
*/
CPauseUI::~CPauseUI()
{

}


/**
* @brief	������
*/
void CPauseUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Sprite");

	// ���O�ݒ�
	obj->SetName("PauseUI");

	// �R���|�[�l���gID
	SetID(Script);

	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Pause);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;

	// �Q�[���ɖ߂�UI����
	const auto& backObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS2).lock();
	const auto& backCom = backObj->AddComponent<CGameBackUI>();
	backCom.lock()->SetSelect(true);
	m_spSelectObj[0] = backObj;

	// �Q�[���I��UI����
	const auto& finObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS1).lock();
	const auto& finCom = finObj->AddComponent<CGameFinUI>();
	finCom.lock()->SetSelect(false);
	m_spSelectObj[1] = finObj;
}


/**
* @brief	�j����
*/
void CPauseUI::OnDestroy()
{
	CScriptBase::OnDestroy();
	m_spSelectObj[0].lock()->Destroy();
	m_spSelectObj[0].reset();
	m_spSelectObj[1].lock()->Destroy();
	m_spSelectObj[1].reset();
}


/**
* @brief	�X�V����
*/
void CPauseUI::Update()
{
	m_spSelectObj[0].lock()->Update();
	m_spSelectObj[1].lock()->Update();
}


/**
* @brief	�I��
* @param	bSelect		true/�I��1 , false/�I��2
*/
void CPauseUI::Select(bool bSelect)
{
	if (bSelect)
	{
		m_spSelectObj[0].lock()->GetComponent<CGameBackUI>().lock()->SetSelect(true);
		m_spSelectObj[1].lock()->GetComponent<CGameFinUI>().lock()->SetSelect(false);
	}
	else
	{
		m_spSelectObj[0].lock()->GetComponent<CGameBackUI>().lock()->SetSelect(false);
		m_spSelectObj[1].lock()->GetComponent<CGameFinUI>().lock()->SetSelect(true);
	}
}