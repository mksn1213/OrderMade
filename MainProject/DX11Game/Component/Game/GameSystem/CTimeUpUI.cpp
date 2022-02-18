/**
*
* @file		CTimeUpUI.cpp
* @brief	�^�C���A�b�vUI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/01/13	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/GameSystem/CTimeUpUI.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const float INCREASE_ALPHA = 0.01f;		// �A���t�@�l�̑�����
}

/**
* @brief	�R���X�g���N�^
*/
CTimeUpUI::CTimeUpUI()
	: m_fAlpha(0.0f)
{

}


/**
* @brief	�f�X�g���N�^
*/
CTimeUpUI::~CTimeUpUI()
{

}


/**
* @brief	������
*/
void CTimeUpUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Sprite");

	// ���O�ݒ�
	obj->SetName("TimeUpUI");

	// �R���|�[�l���gID
	SetID(Script);

	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::TimeUp);
	sprite->SetDrawSize(Vector3(400.0f, 200.0f, 1.0f));
	sprite->SetAlpha(0.0f);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CTimeUpUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTimeUpUI::Update()
{
	// ���X�ɕs������
	m_fAlpha += INCREASE_ALPHA;
	if (m_fAlpha >= 1.0f)	m_fAlpha = 1.0f;
	m_spSprite.lock()->SetAlpha(m_fAlpha);
}