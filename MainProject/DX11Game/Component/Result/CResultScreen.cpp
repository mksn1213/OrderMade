/**
*
* @file		CResultScreen.cpp
* @brief	���U���g��ʃN���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Result/CResultScreen.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/**
* @brief	�R���X�g���N�^
*/
CResultScreen::CResultScreen()
{

}


/**
* @brief	�f�X�g���N�^
*/
CResultScreen::~CResultScreen()
{

}


/**
* @brief	������
*/
void CResultScreen::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Sprite");

	// ���O�ݒ�
	obj->SetName("ResultScreen");

	// �R���|�[�l���gID
	SetID(Script);

	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::ResultScene);
	sprite->SetDrawSize(Vector3(1280.0f, 720.0f, 1.0f));
}


/**
* @brief	�j����
*/
void CResultScreen::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CResultScreen::Update()
{

}
