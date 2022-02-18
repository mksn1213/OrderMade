/**
*
* @file		COptionUI.cpp
* @brief	�I�v�V����UI�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Title/COptionUI.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/**
* @brief	�R���X�g���N�^
*/
COptionUI::COptionUI()
{

}


/**
* @brief	�f�X�g���N�^
*/
COptionUI::~COptionUI()
{

}


/**
* @brief	������
*/
void COptionUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	//�^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("OptionUI");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Option);
	sprite->SetDrawSize(Vector3(300.0f, 150.0f, 1.0f));
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void COptionUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V
*/
void COptionUI::Update()
{

}


