/**
*
* @file		CButton.cpp
* @brief	�{�^���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Title/CButton.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const Vector3	TEX_SIZE = Vector3(300.0f, 150.0f, 1.0f);
	const float		INCREASE = 0.02f;
}

/**
* @brief	�R���X�g���N�^
*/
CButton::CButton()
	: m_fAlpha(0.0f)
	, m_bIsUp(true)
{

}


/**
* @brief	�f�X�g���N�^
*/
CButton::~CButton()
{

}


/**
* @brief	������
*/
void CButton::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	//�^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("Button");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Button);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CButton::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V
*/
void CButton::Update()
{
	if (m_bIsUp)
	{
		m_fAlpha += INCREASE;
		if (m_fAlpha >= 1.0f)	m_bIsUp = false;
	}
	else
	{
		m_fAlpha -= INCREASE;
		if (m_fAlpha <= 0.0f)	m_bIsUp = true;
	}
	m_spSprite.lock()->SetAlpha(m_fAlpha);
}