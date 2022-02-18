/**
*
* @file		CSelectUserGuideUI.cpp
* @brief	����K�C�hUI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Select/CSelectUserGuideUI.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const Vector3 TEX_SIZE = Vector3(1280, 100.0f, 1.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CSelectUserGuideUI::CSelectUserGuideUI()
{

}


/**
* @brief	�f�X�g���N�^
*/
CSelectUserGuideUI::~CSelectUserGuideUI()
{

}


/**
* @brief	������
*/
void CSelectUserGuideUI::OnCreate()
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
	sprite->SetTexture(ETexture::SelectUserGuide);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CSelectUserGuideUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CSelectUserGuideUI::Update()
{

}