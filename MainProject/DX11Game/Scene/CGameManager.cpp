/**
*
* @file		CGameManager.cpp
* @brief	�Q�[���Ǘ��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Scene/CGameManager.h>
#include <Component/Game/Order/COrderManager.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Component/Game/GameSystem/CPauseUI.h>
#include <Scene/CSceneManager.h>
#include <System/Systems/CTransformSystem.h>
#include <System/Systems/CSpriteRendererSystem.h>
#include <System/Systems/CScriptSystem.h>
#include <System/Sound/CSound.h>
#include <Component/Game/GameSystem/CTimeUpUI.h>
#include <System/Renderer/CSpriteRenderer.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneSelect.h>
#include <System/CInput.h>

/** �}�N����` */
namespace
{
	const int		TIME			= 60 * 120;						// �Q�[������
	const int		COUNTDOWN_TIME	= 60 * 3;						// �J�E���g�_�E������
	const Vector3	TEX_SIZE		= Vector3(50.0f, 100.0f, 1.0f);	// �e�N�X�`���T�C�Y
	const int		NUMBER_FRAME_X	= 10;							// ���t���[����
	const int		NUMBER_FRAME_Y	= 1;							// �c�t���[����
}

/**
* @brief	�R���X�g���N�^
*/
CGameManager::CGameManager()
{

}


/**
* @brief	�f�X�g���N�^
*/
CGameManager::~CGameManager()
{

}


/**
* @brief	����������
*/
HRESULT CGameManager::Init()
{
	// �������ԃZ�b�g
	m_pTimer = new CTimer(TIME);

	// �����Ǘ�����
	ORDER_MANAGER->CreateInstance();

	// �ϐ�������
	m_nScore	= 0;
	m_bIsPause	= false;
	m_bGameFin	= false;
	m_bGameStart = false;
	m_nFrame	= COUNTDOWN_TIME;
	m_bSelect = true;

	// �J�E���g�_�E��
	const auto& obj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& renderer = obj->AddComponent<CSpriteRenderer>().lock();
	renderer->SetDrawSize(TEX_SIZE);
	renderer->SetTexture(ETexture::Game_Number);
	unsigned drawSec = COUNTDOWN_TIME / 60 % 60;
	unsigned n = drawSec % 10;
	drawSec /= 10;
	int u = n % NUMBER_FRAME_X;
	int v = n / NUMBER_FRAME_X;
	renderer->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
	renderer->SetTexSize(Vector3(1.0f / NUMBER_FRAME_X, 1.0f / NUMBER_FRAME_Y, 0.0f));
	m_spSprite = renderer;

	// �I��UI����
	const auto& obj2 = std::make_shared<CGameObject>();
	obj2->m_self = obj2;
	obj2->Init();
	obj2->AddComponent<CTimeUpUI>();
	obj2->SetActive(false);
	m_spFinUIObj = obj2;

	// �ʂōX�V���邽�߁A�ŏ��ɃR���|�[�l���g��ێ����Ă���
	m_spFinUIScript = obj2->GetComponent<CTimeUpUI>();

	// SE�{�����[���Z�b�g
	SOUND_MANAGER->SetVolume(SE_PAUSE, 5.0f);

	return S_OK;
}


/**
* @brief	�I������
*/
void CGameManager::Uninit()
{
	// �I��UI�j��
	m_spFinUIObj.reset();

	// �����Ǘ��폜
	ORDER_MANAGER->DestroyInstance();

	// �^�C�}�[�폜
	if (m_pTimer != nullptr)
	{
		delete m_pTimer;
		m_pTimer = nullptr;
	}
}


/**
* @brief	�X�V����
*/
void CGameManager::Update()
{
	if (!m_bGameStart)
	{
		// �t�F�[�h���łȂ��ꍇ�X�V
		if (SCENE_MANAGER->GetFadeState() == CFade::EFade::FADE_NONE)
		{
			if (m_nFrame % 60 == 0)
			{
				if (m_nFrame <= 0)
				{
					// BGM�Đ�
					SOUND_MANAGER->Play(BGM_GAME);
					m_spSprite.lock()->m_spGameObject.lock()->SetActive(false);
					m_bGameStart = true;
					return;
				}
				SOUND_MANAGER->Play(SE_CLICK);
			}
			m_nFrame--;
			unsigned n = m_nFrame / 60 % 60 % 10;
			int u = n % NUMBER_FRAME_X;
			int v = n / NUMBER_FRAME_X;
			float a = u / (float)NUMBER_FRAME_X;
			m_spSprite.lock()->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X + 0.1f, v / (float)NUMBER_FRAME_Y, 0.0f));
		}
		return;
	}

	// �Q�[�����I�����Ă���ꍇ�A�I��UI�X�V���ďI��
	if (m_bGameFin)
	{
		m_spFinUIScript.lock()->Update();
		return;
	}

	// �{�^���v�b�V���Ń|�[�Y��ON/OFF
	if (CInput::GetKeyTrigger(VK_P))
	{
		if (!m_spPauseUIObj.lock())
		{
			// �|�[�YUI����
			const auto& pauseObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
			pauseObj->AddComponent<CPauseUI>();
			m_spPauseUIObj = pauseObj;
			// �|�[�YON
			m_bIsPause = true;
			// �V�X�e���̍X�VOFF
			SCENE_MANAGER->SystemStop(true);
		}
	}

	// �|�[�Y���͍X�V���Ȃ�
	if (!m_bIsPause)
	{
		// �������ԍX�V
		if (!m_pTimer->Update())
		{
			// �X�V�ł��Ȃ���΃Q�[���I��
			m_bGameFin = true;
			// �I��UI�I�u�W�F�N�g���A�N�e�B�u��Ԃ�
			m_spFinUIObj->SetActive(true);
			// �V�X�e���̍X�VOFF
			SCENE_MANAGER->SystemStop(true);
			return;
		}

		// �����X�V
		ORDER_MANAGER->Update();
	}
	else
	{
		// �|�[�Y���̓R���|�[�l���g�V�X�e�����~�߂�̂ł����ōX�V��������
		if (m_spPauseUIObj.lock())
		{
			m_spPauseUIObj.lock()->Update();
		}

		if (CInput::GetKeyTrigger(VK_A))
		{
			m_spPauseUIObj.lock()->GetComponent<CPauseUI>().lock()->Select(true);
			m_bSelect = true;
		}
		else if (CInput::GetKeyTrigger(VK_D))
		{
			m_spPauseUIObj.lock()->GetComponent<CPauseUI>().lock()->Select(false);
			m_bSelect = false;
		}

		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			if (m_bSelect)
			{
				// SE�Đ�
				SOUND_MANAGER->Play(SE_PAUSE);

				// �|�[�Y���̏ꍇ
				if (m_bIsPause)
				{
					m_spPauseUIObj.lock()->Destroy();
					m_spPauseUIObj.reset();
					// �|�[�YOFF
					m_bIsPause = false;
					// �V�X�e���̍X�VON
					SCENE_MANAGER->SystemStop(false);
				}
			}
			else
			{
				// SE�Đ�
				SOUND_MANAGER->Play(SE_PAUSE);

				// �Z���N�g�V�[��
				SCENE_MANAGER->SetNextScene<CSceneSelect>();
			}
		}
	}
}


/**
* @brief	�`�揈��
*/
void CGameManager::Draw()
{
	// �����Ǘ��`��
	ORDER_MANAGER->Draw();
}
