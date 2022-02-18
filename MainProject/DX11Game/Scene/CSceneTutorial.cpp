/**
*
* @file		CSceneTutorial.cpp
* @brief	�`���[�g���A���V�[���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/10	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneTutorial.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Factory/CStageFactory.h>
#include <Scene/CSceneManager.h>
#include <System/Camera/CCameraManager.h>
#include <Component/Tutorial/CTutorialManager.h>
#include <System/Sound/CSound.h>

// �R���|�[�l���g
#include <Component/Game/Field/CField.h>
#include <Component/Game/GameSystem/CScoreUI.h>
#include <Component/Game/GameSystem/CTimerUI.h>
#include <Component/Tutorial/CTutorialUserGuideUI.h>
#include <Component/Tutorial/CTutorialShipGate.h>
#include <Component/Game/GameSystem/CColorUI.h>

/** �}�N����` */
namespace
{
	// �J�������W
	const XMFLOAT3 CAMERA_POS			= XMFLOAT3(0.0f, 130.0f, -90.0f);
	// �J���������_
	const XMFLOAT3 CAMERA_TARGET_POS	= XMFLOAT3(0.0f, 0.0f, 10.0f);
	// ����K�C�h���W
	const Vector3 GUIDE_POS				= Vector3(0.0f, -310.0f, 0.0f);
	// �J���[UI���W
	const Vector3 COLOR_POS				= Vector3(550.0f, 200.0f, 0.0f);
	// �Q�[�g���W
	const Vector3 GATE_POS				= Vector3(0.0f, 0.0f, 40.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CSceneTutorial::CSceneTutorial()
	: m_nStageNo(0)
{
	// �V�[���^�C�v�Z�b�g
	SetSceneType(SceneTutorial);
}


/**
* @brief	�f�X�g���N�^
*/
CSceneTutorial::~CSceneTutorial()
{

}


/**
* @brief	����������
*/
void CSceneTutorial::Init()
{
	// �J�������W�Z�b�g
	CAMERA->Get(0)->SetParameter(CAMERA_POS, CAMERA_TARGET_POS, Vector3::up());
	CAMERA->Get(0)->Chase(false);

	// �`���[�g���A���Ǘ�����
	TUTORIAL_MANAGER->CreateInstance();
	TUTORIAL_MANAGER->SetStageNo(m_nStageNo);

	// �t�B�[���h����
	const auto& field = GAMEOBJECT_MANAGER->Instantiation<CGameObject>();
	field.lock()->AddComponent<CField>();

	// �X�e�[�W����
	CStageFactory::Init(m_eSceneType, m_nStageNo);

	// �X�R�AUI����
	const auto& scoreObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(SCREEN_WIDTH / 2 - 120.0f, SCREEN_HEIGHT / 2 - 70.0f, 0.0f)).lock();
	const auto& scoreCom = scoreObj->AddComponent<CScoreUI>().lock();

	// �^�C�}�[UI����
	const auto& timerObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(-SCREEN_WIDTH / 2 + 120.0f, SCREEN_HEIGHT / 2 - 70.0f, 0.0f)).lock();
	const auto& timerCom = timerObj->AddComponent<CTimerUI>().lock();

	// ����K�C�h����
	const auto& guideObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(GUIDE_POS).lock();
	guideObj->AddComponent<CTutorialUserGuideUI>();

	// �J���[UI����
	const auto& colorObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(COLOR_POS).lock();
	colorObj->AddComponent<CColorUI>();

	// �`���[�g���A���p�o�׃Q�[�g����
	const auto& gateObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(GATE_POS).lock();
	gateObj->AddComponent<CTutorialShipGate>();

	// BGM�Đ�
	SOUND_MANAGER->Play(BGM_GAME);
}


/**
* @brief	�I������
*/
void CSceneTutorial::Uninit()
{
	// BGM��~
	SOUND_MANAGER->Stop(BGM_GAME);

	// �X�e�[�W�����I��
	CStageFactory::Uninit();

	// �`���[�g���A���Ǘ��폜
	TUTORIAL_MANAGER->DestroyInstance();
}


/**
* @brief	�X�V����
*/
void CSceneTutorial::Update()
{
	// �`���[�g���A���Ǘ��X�V
	TUTORIAL_MANAGER->Update();
}


/**
* @brief	�`�揈��
*/
void CSceneTutorial::Draw()
{
	// �`���[�g���A���Ǘ��`��
	TUTORIAL_MANAGER->Draw();
}