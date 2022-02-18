
/**
*
* @file		CSceneTitle.cpp
* @brief	�^�C�g���V�[���N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneTitle.h>
#include <System/Factory/CStageFactory.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneSelect.h>
#include <System/Camera/CCameraManager.h>
#include <System/Sound/CSound.h>
#include <System/CInput.h>

// �R���|�[�l���g
#include <Component/Game/Field/CField.h>
#include <Component/Title/CTitleTruck.h>
#include <Component/Title/CTitleFlower.h>
#include <Component/Title/CTitleLogo.h>
#include <Component/Title/CButton.h>
#include <Component/Title/COptionUI.h>

/** �}�N����` */
namespace
{
	// �J�������W
	const XMFLOAT3 CAMERA_POS		 = XMFLOAT3(-15.0f, 40.0f, -90.0f);
	// �J���������_
	const XMFLOAT3 CAMERA_TARGET_POS = XMFLOAT3(35.0f, 10.0f, 0.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CSceneTitle::CSceneTitle()
{
	// �V�[���^�C�v�Z�b�g
	SetSceneType(SceneTitle);
}


/**
* @brief	�f�X�g���N�^
*/
CSceneTitle::~CSceneTitle()
{

}


/**
* @brief	������
*/
void CSceneTitle::Init()
{
	// �J�������W�Z�b�g
	CAMERA->Get(0)->SetParameter(CAMERA_POS, CAMERA_TARGET_POS, Vector3::up());

	// �t�B�[���h����
	const auto& field = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	field->AddComponent<CField>();

	// �X�e�[�W����
	CStageFactory::Init(m_eSceneType);

	// �Q�[�g�I�u�W�F�N�g����
	const auto& gateObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& renderer = gateObj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ShipGate);

	// �g���b�N�I�u�W�F�N�g����
	for (int i = 0; i < 3; ++i)
	{
		const auto& truckObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(-500.0f + 200.0f * i, 0.0f, 30.0f)).lock();
		truckObj->AddComponent<CTitleTruck>();
	}

	// �ԃI�u�W�F�N�g����
	const auto& flowerObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(0.0f, 0.0f, -20.0f)).lock();
	flowerObj->AddComponent<CTitleFlower>();

	// �^�C�g�����S����
	const auto& titleObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(300.0f, 200.0f, 0.0f)).lock();
	titleObj->AddComponent<CTitleLogo>();

	// �^�C�g���{�^������
	const auto& buttonObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(440.0f, -250.0f, 0.0f)).lock();
	buttonObj->AddComponent<CButton>();

	// �I�v�V����UI����
	//const auto& optionObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	//optionObj->AddComponent<COptionUI>();
	//optionObj->m_spTransform.lock()->SetPosition(Vector3(440.0f, -270.0f, 0.0f));

	// �T�E���h�Đ�
	SOUND_MANAGER->Play(BGM_TITLE);
}


/**
* @brief	�I������
*/
void CSceneTitle::Uninit()
{
	SOUND_MANAGER->Stop(BGM_TITLE);
}


/**
* @brief	�X�V����
*/
void CSceneTitle::Update()
{	
	// �{�^���v�b�V���ŃV�[���J��
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		const auto& scene = SCENE_MANAGER;
		// �t�F�[�h����������I��
		if (scene->GetFadeState() != CFade::EFade::FADE_NONE)	return;

		// SE�Đ�
		SOUND_MANAGER->Play(SE_CLICK);

		// ���̃V�[���Z�b�g
		scene->SetNextScene<CSceneSelect>();
	}
}


/**
* @brief	�`�揈��
*/
void CSceneTitle::Draw()
{

}
