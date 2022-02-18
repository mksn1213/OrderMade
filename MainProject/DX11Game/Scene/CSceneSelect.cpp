/**
*
* @file		CSceneSelect.cpp
* @brief	�Z���N�g�V�[���N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneSelect.h>
#include <Scene/CSceneGame.h>
#include <System/Factory/CStageFactory.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Scene/CSceneManager.h>
#include <System/Camera/CCameraManager.h>
#include <System/Sound/CSound.h>
#include <System/CInput.h>
#include <System/Renderer/CSpriteRenderer.h>

// �R���|�[�l���g
#include <Component/Game/Field/CField.h>
#include <Component/Select/CSelectGate.h>
#include <Component/Select/CSelectUserGuideUI.h>

/** �}�N����` */
namespace
{
	// �J�������W
	const XMFLOAT3	CAMERA_POS			= XMFLOAT3(0.0f, 70.0f, -70.0f);
	// �J���������_
	const XMFLOAT3	CAMERA_TARGET_POS	= XMFLOAT3(0.0f, 30.0f, 0.0f);
	// �Q�[�g���W
	const Vector3	TITLE_GATE_POS		= Vector3(-90.0f, 0.0f, 40.0f);
	const Vector3	TUTORIAL_GATE_POS	= Vector3(0.0f, 0.0f, 40.0f);
	const Vector3	GAME1_GATE_POS		= Vector3(90.0f, 0.0f, 40.0f);
	// ����K�C�h���W
	const Vector3	GUIDE_POS			= Vector3(0.0f, -310.0f, 0.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CSceneSelect::CSceneSelect()
{
	// �V�[���^�C�v�Z�b�g
	SetSceneType(SceneSelect);
}


/**
* @brief	�f�X�g���N�^
*/
CSceneSelect::~CSceneSelect()
{

}


/**
* @brief	����������
*/
void CSceneSelect::Init()
{
	// �J�������W�Z�b�g
	CAMERA->Get(0)->SetParameter(CAMERA_POS, CAMERA_TARGET_POS, Vector3::up());
	CAMERA->Get(0)->Chase(true);

	// �t�B�[���h����
	const auto& field = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	field->AddComponent<CField>();

	// �X�e�[�W����
	CStageFactory::Init(m_eSceneType);

	// �Q�[�g����
	const auto& titleGate = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	titleGate->m_spTransform.lock()->SetPosition(TITLE_GATE_POS);
	const auto& titleGateCom = titleGate->AddComponent<CSelectGate>().lock();
	titleGateCom->SetGateType(CSelectGate::GateTitle);

	const auto& tutorialGate = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	tutorialGate->m_spTransform.lock()->SetPosition(TUTORIAL_GATE_POS);
	const auto& tutorialGateCom = tutorialGate->AddComponent<CSelectGate>().lock();
	tutorialGateCom->SetGateType(CSelectGate::GateTutorial);

	const auto& gameGate = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	gameGate->m_spTransform.lock()->SetPosition(GAME1_GATE_POS);
	const auto& gameGateCom = gameGate->AddComponent<CSelectGate>().lock();
	gameGateCom->SetGateType(CSelectGate::GateGame1);

	// ����K�C�h
	const auto& guideObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	guideObj->m_spTransform.lock()->SetPosition(GUIDE_POS);
	guideObj->AddComponent<CSelectUserGuideUI>();

	// �T�E���h�Đ�
	SOUND_MANAGER->Play(BGM_SELECT);
}


/**
* @brief	�I������
*/
void CSceneSelect::Uninit()
{
	SOUND_MANAGER->Stop(BGM_SELECT);
}


/**
* @brief	�X�V����
*/
void CSceneSelect::Update()
{
}


/**
* @brief	�`�揈��
*/
void CSceneSelect::Draw()
{
}
