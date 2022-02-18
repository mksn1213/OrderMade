/**
*
* @file		CColorUI.cpp
* @brief	�J���[UI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/GameSystem/CColorUI.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const Vector3 TEX_SIZE = Vector3(100.0f, 100.0f, 1.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CColorUI::CColorUI()
{

}


/**
* @brief	�f�X�g���N�^
*/
CColorUI::~CColorUI()
{

}


/**
* @brief	������
*/
void CColorUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("ColorUI");
	// �R���|�[�l���gID
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Color);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CColorUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CColorUI::Update()
{

}