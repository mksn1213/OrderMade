/**
*
* @file		CTutorialClearUI.cpp
* @brief	�`���[�g���A���N���AUI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/16	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Tutorial/CTutorialClearUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneTutorial.h>
#include <Component/Tutorial/CTutorialManager.h>
#include <System/GameObject/CGameObjectManager.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>
#include <Component/Tutorial/CTutorialFinUI.h>

/** �}�N����` */
namespace
{
	const Vector3	TEX_POS   = Vector3(900.0f, 0.0f, 0.0f);
	const Vector3	TEX_SIZE  = Vector3(300.0f, 300.0f, 1.0f);
	const int		FIN_FRAME = 120;
}

/**
* @brief	�R���X�g���N�^
*/
CTutorialClearUI::CTutorialClearUI()
	: m_nFrame(0)
	, m_bIsCreate(false)
{

}


/**
* @brief	�f�X�g���N�^
*/
CTutorialClearUI::~CTutorialClearUI()
{

}


/**
* @brief	������
*/
void CTutorialClearUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("TutorialClearUI");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetDrawSize(TEX_SIZE);
	sprite->SetTexture(ETexture::TutorialOK);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CTutorialClearUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTutorialClearUI::Update()
{
	if (m_nFrame > FIN_FRAME)
	{
		auto stageNo = TUTORIAL_MANAGER->GetStageNo();
		if (stageNo != 3)
		{
			auto scene = SCENE_MANAGER->SetNextScene<CSceneTutorial>();
			scene->SetStageNo(stageNo + 1);
			m_nFrame = 0;
		}
		else
		{
			if (!m_bIsCreate)
			{
				const auto& obj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS).lock();
				obj->AddComponent<CTutorialFinUI>();
				m_bIsCreate = true;
			}
		}
	}
	m_nFrame++;
}