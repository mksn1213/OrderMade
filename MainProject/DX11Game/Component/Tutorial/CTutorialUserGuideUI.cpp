/**
*
* @file		CTutorialUserGuideUI.cpp
* @brief	�������UI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Tutorial/CTutorialUserGuideUI.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const Vector3 TEX_SIZE = Vector3(1280.0f, 100.0f, 1.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CTutorialUserGuideUI::CTutorialUserGuideUI()
{

}


/**
* @brief	�R���X�g���N�^
*/
CTutorialUserGuideUI::~CTutorialUserGuideUI()
{

}


/**
* @brief	������
*/
void CTutorialUserGuideUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("UserGuideUI");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::TutorialUserGuide);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CTutorialUserGuideUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTutorialUserGuideUI::Update()
{

}