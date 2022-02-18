/**
*
* @file		CFade.cpp
* @brief	�t�F�[�h�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/01/14	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/CFade.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const float INCREASE = 0.01f;
}

/**
* @brief	�R���X�g���N�^
*/
CFade::CFade()
	: m_eFadeState(EFade::FADE_IN)
	, m_fParam(1.0f)
{

}


/**
* @brief	�f�X�g���N�^
*/
CFade::~CFade()
{

}


/**
* @brief	������
*/
void CFade::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Sprite");

	// ���O�ݒ�
	obj->SetName("Fade");

	// �R���|�[�l���gID
	SetID(Script);

	// �X�v���C�g�ǉ�
	const auto& renderer = obj->AddComponent<CSpriteRenderer>().lock();
	renderer->SetTexture(ETexture::Fade);
	renderer->SetEffectTexture(ETexture::Dissolve);
	renderer->SetDrawSize(Vector3(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f));
	m_spRenderer = renderer;

	// �V�F�[�_�[�Z�b�g
	m_spGameObject.lock()->SetShader(Simple2DVS, DissolvePS);
}


/**
* @brief	�j����
*/
void CFade::OnDestroy()
{
}


/**
* @brief	�X�V����
*/
void CFade::Update()
{
	if (m_eFadeState == EFade::FADE_NONE)	return;
	
	// �t�F�[�h�C������
	if (m_eFadeState == EFade::FADE_IN)
	{
		m_fParam -= INCREASE;
		if (m_fParam < 0.0f)
		{
			m_fParam = 0.0f;
			// �t�F�[�h�I��
			m_eFadeState = EFade::FADE_NONE;
		}
	}
	// �t�F�[�h�A�E�g����
	else
	{
		m_fParam += INCREASE;
		if (m_fParam > 1.0f)
		{
			m_fParam = 1.0f;
			// �V�[���؂�ւ�
			SCENE_MANAGER->SetSceneChange();
			// �t�F�[�h�C���J�n
			m_eFadeState = EFade::FADE_IN;
		}
	}
}


/**
* @brief	�t�F�[�h�A�E�g�J�n
*/
void CFade::StartFadeOut()
{
	m_eFadeState = EFade::FADE_OUT;
}