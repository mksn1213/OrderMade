/**
*
* @file		CSceneResult.cpp
* @brief	���U���g�V�[���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneResult.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneSelect.h>
#include <Scene/CSceneManager.h>
#include <System/Camera/CCameraManager.h>
#include <System/Sound/CSound.h>
#include <System/CInput.h>

// �R���|�[�l���g
#include <Component/Title/CButton.h>
#include <Component/Result/CResultScreen.h>
#include <System/Renderer/CSpriteRenderer.h>
#include <Component/Result/CResultScore.h>

/** �}�N����` */
namespace
{
	// �J�������W
	const XMFLOAT3 CAMERA_POS = XMFLOAT3(0.0f, 20.0f, -50.0f);
	// �J���������_
	const XMFLOAT3 CAMERA_TARGET_POS = XMFLOAT3(0.0f, 10.0f, 0.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CSceneResult::CSceneResult()
	: m_nScore(0)
{
	// �V�[���^�C�v�Z�b�g
	SetSceneType(SceneResult);
}


/**
* @brief	�f�X�g���N�^
*/
CSceneResult::~CSceneResult()
{

}



/**
* @brief	����������
*/
void CSceneResult::Init()
{
	// �J�������W�Z�b�g
	CAMERA->Get(0)->SetParameter(CAMERA_POS, CAMERA_TARGET_POS, Vector3::up());

	// ���U���g��ʍ쐬
	const auto& screenObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	screenObj->AddComponent<CResultScreen>();

	// �{�^������
	const auto& buttonObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3::down() * 200.0f).lock();
	buttonObj->AddComponent<CButton>();
	
	// �X�R�A����
	const auto& scoreObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& scoreCom = scoreObj->AddComponent<CResultScore>().lock();
	scoreCom->SetScore(m_nScore);

	// BGM�Đ�
	SOUND_MANAGER->Play(BGM_RESULT);
}


/**
* @brief	�I������
*/
void CSceneResult::Uninit()
{
	// BGM��~
	SOUND_MANAGER->Stop(BGM_RESULT);
}


/**
* @brief	�X�V����
*/
void CSceneResult::Update()
{
	// �{�^���v�b�V���ŃV�[���J��
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		const auto& scene = SCENE_MANAGER;
		// �t�F�[�h����������I��
		if (scene->GetFadeState() != CFade::EFade::FADE_NONE)	return;

		// ���̃V�[���Z�b�g
		scene->SetNextScene<CSceneSelect>();
	}
}


/**
* @brief	�`�揈��
*/
void CSceneResult::Draw()
{
}