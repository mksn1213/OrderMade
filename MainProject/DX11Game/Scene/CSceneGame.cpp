/**
*
* @file		CSceneGame.cpp
* @brief	�Q�[���V�[���N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneGame.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Scene/CSceneManager.h>
#include <System/Factory/CStageFactory.h>
#include <Scene/CGameManager.h>
#include <Scene/CSceneResult.h>
#include <System/Camera/CCameraManager.h>
#include <System/Sound/CSound.h>
#include <System/CInput.h>

// �R���|�[�l���g
#include <Component/Game/Field/CField.h>
#include <Component/Game/GameSystem/CScoreUI.h>
#include <Component/Game/GameSystem/CTimerUI.h>
#include <Component/Game/GameSystem/CColorUI.h>
#include <Component/Game/GameSystem/CPauseButton.h>

namespace
{
	// �J�������W
	const XMFLOAT3 CAMERA_POS = XMFLOAT3(0.0f, 130.0f, -90.0f);
	// �J���������_
	const XMFLOAT3 CAMERA_TARGET_POS	= XMFLOAT3(0.0f, 0.0f, 10.0f);
	// ���U���g�V�[���Ɉڍs����܂ł̎���
	const int SCENE_CHNAGE_INTERVAL = 180;
	// �J���[UI���W
	const Vector3 COLOR_POS = Vector3(550.0f, 200.0f, 0.0f);
	// �|�[�YUI���W
	const Vector3 PAUSE_POS = Vector3(500.0f, -300.0f, 0.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CSceneGame::CSceneGame()
	: m_nFrame(0)
{
	// �V�[���^�C�v�Z�b�g
	SetSceneType(SceneGame);
}


/**
* @brief	�f�X�g���N�^
*/
CSceneGame::~CSceneGame()
{

}


/**
* @brief	����������
*/
void CSceneGame::Init()
{
	// �J�������W�Z�b�g
	CAMERA->Get(0)->SetParameter(CAMERA_POS, CAMERA_TARGET_POS, Vector3::up());
	CAMERA->Get(0)->Chase(false);

	// �Q�[���Ǘ�����
	GAME_MANAGER->CreateInstance();

	// �t�B�[���h����
	const auto& field = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(0.0f, 0.0f, 0.0f));
	field.lock()->AddComponent<CField>();

	// �X�e�[�W����
	CStageFactory::Init(m_eSceneType);

	// �X�R�AUI�I�u�W�F�N�g����
	const auto& scoreObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(SCREEN_WIDTH / 2 - 120.0f, SCREEN_HEIGHT / 2 - 70.0f, 0.0f));
	scoreObj.lock()->AddComponent<CScoreUI>();

	// �^�C�}�[UI�I�u�W�F�N�g����
	const auto& timerObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(-SCREEN_WIDTH / 2 + 120.0f, SCREEN_HEIGHT / 2 - 70.0f, 0.0f));
	timerObj.lock()->AddComponent<CTimerUI>();

	// �J���[UI����
	const auto& colorObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(COLOR_POS).lock();
	colorObj->AddComponent<CColorUI>();

	// �|�[�Y�{�^��UI����
	const auto& pauseObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(PAUSE_POS).lock();
	pauseObj->AddComponent<CPauseButton>();
}


/**
* @brief	�I������
*/
void CSceneGame::Uninit()
{
	// BGM�X�g�b�v
	SOUND_MANAGER->Stop(BGM_GAME);

	// �X�e�[�W�����I��
	CStageFactory::Uninit();

	// �Q�[���Ǘ��폜
	GAME_MANAGER->DestroyInstance();
}


/**
* @brief	�X�V����
*/
void CSceneGame::Update()
{
	// �Q�[���Ǘ��X�V
	GAME_MANAGER->Update();

	// �Q�[���I����V�[���J��
	if (GAME_MANAGER->IsGameFin())
	{
		if (m_nFrame > SCENE_CHNAGE_INTERVAL)
		{
			const auto& scene = SCENE_MANAGER;
			// �t�F�[�h����������I��
			if (scene->GetFadeState() != CFade::EFade::FADE_NONE)	return;
			// ���̃V�[���Z�b�g
			auto nextScene = scene->SetNextScene<CSceneResult>();
			nextScene->SetScore(GAME_MANAGER->GetScore());
			m_nFrame = 0;
		}
		m_nFrame++;
	}
}


/**
* @brief	�`�揈��
*/
void CSceneGame::Draw()
{
	// �Q�[���Ǘ��`��
	GAME_MANAGER->Draw();
}
