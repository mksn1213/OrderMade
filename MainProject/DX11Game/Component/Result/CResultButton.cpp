/**
*
* @file		CResultButton.cpp
* @brief	���U���g�{�^���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Result/CResultButton.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/**
* @brief	�R���X�g���N�^
*/
CResultButton::CResultButton()
{

}


/**
* @brief	�f�X�g���N�^
*/
CResultButton::~CResultButton()
{

}



/**
* @brief	������
*/
void CResultButton::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Sprite");

	// ���O�ݒ�
	obj->SetName("ResultButton");

	// �R���|�[�l���gID
	SetID(Script);

	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Button);
	sprite->SetDrawSize(Vector3(300.0f, 200.0f, 1.0f));
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CResultButton::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CResultButton::Update()
{

}
