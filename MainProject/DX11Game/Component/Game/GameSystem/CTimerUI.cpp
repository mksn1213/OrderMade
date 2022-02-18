/**
*
* @file		CTimerUI.cpp
* @brief	�^�C�}�[UI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/01/04	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/GameSystem/CTimerUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CGameManager.h>
#include <cmath>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const float NUMBER_SPACE	= 30.0f;	// �`��Ԋu
	const int	NUMBER_FRAME_X	= 10;		// ���t���[����
	const int	NUMBER_FRAME_Y	= 1;		// �c�t���[����
	const int	PERFORM_TIME = 30;			// ���o����
	const int	TIME_REMAINING = 10;		// �c�莞��
}

/**
* @brief	�R���X�g���N�^
*/
CTimerUI::CTimerUI()
	: m_nFrame(0)
	, m_bPerform(false)
{

}


/**
* @brief	�f�X�g���N�^
*/
CTimerUI::~CTimerUI()
{
}


/**
* @brief	������
*/
void CTimerUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Sprite");

	// ���O�ݒ�
	obj->SetName("TimerUI");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �X�v���C�g�Z�b�g
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetTexture(ETexture::Game_Timer);
	sprite->SetDrawSize(Vector3(200.0f, 100.0f, 1.0f));
	m_spSprite = sprite;

	// ���ԃX�v���C�g�ǉ�
	const auto& dot = obj->AddComponent<CSpriteRenderer>().lock();
	dot->SetTexture(ETexture::Game_Dot);
	dot->SetDrawSize(Vector3(30.0f, 45.0f, 1.0f));
	dot->SetColor(Vector3::zero());
	for (int i = 0; i < 4; ++i)
	{
		auto renderer = obj->AddComponent<CSpriteRenderer>().lock();
		renderer->SetTexture(ETexture::Game_Number);
		renderer->SetDrawSize(Vector3(30.0f, 45.0f, 1.0f));
		renderer->SetColor(Vector3::zero());
		renderer->SetTexSize(Vector3(1.0f / NUMBER_FRAME_X, 1.0f / NUMBER_FRAME_Y, 0.0f));
		m_spRenderer[i] = renderer;
	}
	m_spRenderer[0].lock()->SetLocalPos(Vector3(-NUMBER_SPACE * 2, 0.0f, 0.0f));
	m_spRenderer[1].lock()->SetLocalPos(Vector3(-NUMBER_SPACE, 0.0f, 0.0f));
	m_spRenderer[2].lock()->SetLocalPos(Vector3( NUMBER_SPACE, 0.0f, 0.0f));
	m_spRenderer[3].lock()->SetLocalPos(Vector3( NUMBER_SPACE * 2, 0.0f, 0.0f));
	
	int time;
	m_eSceneType = SCENE_MANAGER->GetScene()->GetSceneType();
	if (m_eSceneType == ESceneType::SceneTutorial)	time = 120 * 60;
	else time = GAME_MANAGER->GetTime();
	
	//-----��
	unsigned drawMinute = time / (60 * 60);
	unsigned n = drawMinute % 10;
	drawMinute /= 10;
	int u = n % NUMBER_FRAME_X;
	int v = n / NUMBER_FRAME_X;
	m_spRenderer[1].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	n = drawMinute % 10;
	drawMinute /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[0].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));

	//-----�b
	unsigned drawSec = time / 60 % 60;
	n = drawSec % 10;
	drawSec /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[3].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	n = drawSec % 10;
	drawSec /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[2].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
}


/**
* @brief	�j����
*/
void CTimerUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTimerUI::Update()
{
	// �`���[�g���A���V�[���������ꍇ�I��
	if (m_eSceneType == ESceneType::SceneTutorial)	return;

	// �e�N�X�`�����W�X�V
	int time = GAME_MANAGER->GetTime();
	// �w�肵���c�莞�Ԃ��牉�o�J�n
	if (time / 60 <= TIME_REMAINING && time / 60.0f == time / 60)	m_bPerform = true;

	//-----��
	unsigned drawMinute = time / (60 * 60);
	unsigned n = drawMinute % 10;
	drawMinute /= 10;
	int u = n % NUMBER_FRAME_X;
	int v = n / NUMBER_FRAME_X;
	m_spRenderer[1].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	n = drawMinute % 10;
	drawMinute /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[0].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));

	//-----�b
	unsigned drawSec = time / 60 % 60;
	n = drawSec % 10;
	drawSec /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[3].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	n = drawSec % 10;
	drawSec /= 10;
	u = n % NUMBER_FRAME_X;
	v = n / NUMBER_FRAME_X;
	m_spRenderer[2].lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));

	// ���o�֘A
	if (m_bPerform)
	{
		if (m_nFrame < PERFORM_TIME)
		{
			// �F�ύX + �T�C�Y�ύX
			for (int i = 0; i < 4; ++i)
			{
				m_spRenderer[i].lock()->SetColor(Vector3::right() * 0.7f);
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
}