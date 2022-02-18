/**
*
* @file		CScoreUI.h
* @brief	�X�R�A�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/25	�����J�n
* @date		2021/12/22	�R���|�[�l���g�ɕύX
* @date		2021/12/30	CScore����CScoreUI�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/GameSystem/CScoreUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CGameManager.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const float NUMBER_SPACE	= 30.0f;	// �`��Ԋu
	const int	NUMBER_FRAME_X	= 10;		// ���t���[����
	const int	NUMBER_FRAME_Y	= 1;		// �c�t���[����
	const int	PERFORM_TIME	= 30;		// ���o����
}

/**
* @brief	�R���X�g���N�^
*/
CScoreUI::CScoreUI()
	: m_uOldScore(0)
	, m_nFrame(0)
	, m_bPerform(false)
{

}


/**
* @brief	�f�X�g���N�^
*/
CScoreUI::~CScoreUI()
{

}


/**
* @brief	������
*/
void CScoreUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Sprite");

	// ���O�ݒ�
	obj->SetName("ScoreUI");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Game_Score);
	sprite->SetDrawSize(Vector3(200.0f, 100.0f, 1.0f));
	m_spSprite = sprite;

	// �X�R�A�X�v���C�g�ǉ�
	unsigned drawScore = 0;
	for (int i = 0; i < 4; ++i)
	{
		auto renderer = obj->AddComponent<CSpriteRenderer>().lock();
		renderer->SetTexture(ETexture::Game_Number);
		renderer->SetDrawSize(Vector3(30.0f, 45.0f, 1.0f));
		renderer->SetColor(Vector3::zero());
		renderer->SetTexSize(Vector3(1.0f / NUMBER_FRAME_X, 1.0f / NUMBER_FRAME_Y, 0.0f));
		renderer->SetLocalPos(Vector3(-NUMBER_SPACE * 1.5f + i * NUMBER_SPACE, 0.0f, 0.0f));
		unsigned n = drawScore % 10;
		drawScore /= 10;
		int u = n % NUMBER_FRAME_X;
		int v = n / NUMBER_FRAME_X;
		renderer->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));		
		m_spRenderer[i] = renderer;
	}

	// �V�[���^�C�v�ۑ�
	m_eSceneType = SCENE_MANAGER->GetScene()->GetSceneType();
}


/**
* @brief	�j����
*/
void CScoreUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CScoreUI::Update()
{
	// �`���[�g���A���V�[���������ꍇ�I��
	if (m_eSceneType == ESceneType::SceneTutorial)	return;

	// �X�R�A�擾
	unsigned drawScore = GAME_MANAGER->GetScore();

	// �X�R�A���ϓ������ꍇ
	if (drawScore != m_uOldScore)	m_bPerform = true;

	// �e�N�X�`�����W�X�V
	for (int i = 3; i >= 0; --i)
	{
		unsigned n = drawScore % 10;
		drawScore /= 10;
		int u = n % NUMBER_FRAME_X;
		int v = n / NUMBER_FRAME_X;
		m_spRenderer[i].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	}

	// ���o�֘A
	if (m_bPerform)
	{
		if (m_nFrame < PERFORM_TIME)
		{
			// �F�ύX + �T�C�Y�ύX
			for (int i = 0; i < 4; ++i)
			{
				m_spRenderer[i].lock()->SetColor(Vector3::up() * 0.7f);
				if (m_nFrame < PERFORM_TIME / 2)
				{
					auto size = m_spRenderer[i].lock()->GetDrawSize();
					size *= 1.02f;
					m_spRenderer[i].lock()->SetDrawSize(size);
				}
				else
				{
					auto size = m_spRenderer[i].lock()->GetDrawSize();
					size *= 0.98f;
					m_spRenderer[i].lock()->SetDrawSize(size);
				}
			}
			m_nFrame++;
		}
		// ���o�I��
		else
		{
			// �F�ύX
			for (int i = 0; i < 4; ++i)
			{
				m_spRenderer[i].lock()->SetColor(Vector3::zero());
			}
			m_bPerform = false;
			m_nFrame = 0;
		}
	}

	// �O�̃X�R�A�ۑ�
	m_uOldScore = GAME_MANAGER->GetScore();
}
