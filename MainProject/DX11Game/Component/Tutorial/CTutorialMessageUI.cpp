/**
*
* @file		CTutorialMessageUI.cpp
* @brief	�`���[�g���A�����b�Z�[�WUI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Tutorial/CTutorialMessageUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const Vector3	TEX_SIZE	= Vector3(500.0f, 200.0f, 1.0f);
	const float		MOVE_SPEED	= 12.0f;
	const int		STAY_TIME	= 60;
}

/**
* @brief	�R���X�g���N�^
*/
CTutorialMessageUI::CTutorialMessageUI()
	: m_nFrame(0)
{

}


/**
* @brief	�f�X�g���N�^
*/
CTutorialMessageUI::~CTutorialMessageUI()
{

}


/**
* @brief	������
*/
void CTutorialMessageUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("TutorialMessageUI");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetDrawSize(TEX_SIZE);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CTutorialMessageUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTutorialMessageUI::Update()
{
	// �t�F�[�h���łȂ��ꍇ
	if (SCENE_MANAGER->GetFadeState() == CFade::EFade::FADE_NONE)
	{
		auto pos = m_spTransform.lock()->GetPosition();
		pos->x -= MOVE_SPEED;
		if (pos->x <= 0.0f)
		{
			if (m_nFrame < STAY_TIME)
			{
				pos->x = 0.0f;
			}
			m_nFrame++;
		}
		m_spTransform.lock()->SetPosition(pos);
	}
}


/**
* @brief	�e�N�X�`���Z�b�g
* @param	nStageNo	�X�e�[�W�ԍ�
*/
void CTutorialMessageUI::SetTexture(int nStageNo)
{
	switch (nStageNo)
	{
	case 0:	m_spSprite.lock()->SetTexture(ETexture::TutorialMessage1);	break;
	case 1:	m_spSprite.lock()->SetTexture(ETexture::TutorialMessage2);	break;
	case 2:	m_spSprite.lock()->SetTexture(ETexture::TutorialMessage3);	break;
	case 3:	m_spSprite.lock()->SetTexture(ETexture::TutorialMessage4);	break;
	default:															break;
	}
}