/**
*
* @file		CTitleLogo.cpp
* @brief	�^�C�g�����S�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Title/CTitleLogo.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/**
* @brief	�R���X�g���N�^
*/
CTitleLogo::CTitleLogo()
{

}


/**
* @brief	�f�X�g���N�^
*/
CTitleLogo::~CTitleLogo()
{

}


/**
* @brief	������
*/
void CTitleLogo::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("TitleLogo");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::TitleLogo);
	sprite->SetDrawSize(Vector3(600.0f, 300.0f, 1.0f));
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CTitleLogo::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTitleLogo::Update()
{

}