/**
*
* @file		CPauseButton.cpp
* @brief	�|�[�Y�{�^���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/GameSystem/CPauseButton.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const Vector3 TEX_SIZE = Vector3(300.0f, 150.0f, 1.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CPauseButton::CPauseButton()
{

}


/**
* @brief	�f�X�g���N�^
*/
CPauseButton::~CPauseButton()
{

}


/**
* @brief	������
*/
void CPauseButton::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("PauseButton");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::PauseButton);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CPauseButton::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CPauseButton::Update()
{

}