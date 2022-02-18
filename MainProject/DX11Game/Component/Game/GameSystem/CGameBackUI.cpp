/**
*
* @file		CGameBackUI.cpp
* @brief	�Q�[���ɖ߂�UI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/GameSystem/CGameBackUI.h>
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
CGameBackUI::CGameBackUI()
	: m_bIsSelect(true)
	, m_fAlpha(0.0f)
	, m_bIsUp(true)
{

}


/**
* @brief	�f�X�g���N�^
*/
CGameBackUI::~CGameBackUI()
{

}


/**
* @brief	������
*/
void CGameBackUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("GameBackUI");
	// �R���|�[�l���gID
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::BackGame);
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CGameBackUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CGameBackUI::Update()
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