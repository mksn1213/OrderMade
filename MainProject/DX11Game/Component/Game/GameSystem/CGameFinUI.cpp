/**
*
* @file		CGameFinUI.cpp
* @brief	�Q�[���I��UI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/GameSystem/CGameFinUI.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const Vector3	TEX_SIZE = Vector3(300.0f, 150.0f, 1.0f);
	const float		INCREASE = 0.05f;
}

/**
* @brief	�R���X�g���N�^
*/
CGameFinUI::CGameFinUI()
	: m_bIsSelect(false)
	, m_fAlpha(0.0f)
	, m_bIsUp(true)
{

}


/**
* @brief	�f�X�g���N�^
*/
CGameFinUI::~CGameFinUI()
{

}


/**
* @brief	������
*/
void CGameFinUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("GameFinUI");
	// �R���|�[�l���gID
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::GameFin);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CGameFinUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CGameFinUI::Update()
{
	if (m_bIsSelect)
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
	}
	else
	{
		m_fAlpha = 1.0f;
	}
	m_spSprite.lock()->SetAlpha(m_fAlpha);
}