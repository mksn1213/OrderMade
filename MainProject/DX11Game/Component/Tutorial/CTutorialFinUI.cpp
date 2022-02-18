/**
*
* @file		CTutorialFinUI.cpp
* @brief	�`���[�g���A���I��UI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Tutorial/CTutorialFinUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneSelect.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/CInput.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>
#include <Component/Title/CButton.h>

/** �}�N����` */
namespace
{
	const Vector3	TEX_SIZE	= Vector3(500.0f, 600.0f, 1.0f);
	const float		MOVE_SPEED	= 12.0f;
	const Vector3	TEX_POS		= Vector3(0.0f, -300.0f, 0.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CTutorialFinUI::CTutorialFinUI()
	: m_nFrame(0)
	, m_bIsCreate(false)
{

}


/**
* @brief	�f�X�g���N�^
*/
CTutorialFinUI::~CTutorialFinUI()
{

}


/**
* @brief	������
*/
void CTutorialFinUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("TutorialFinUI");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	sprite->SetDrawSize(TEX_SIZE);
	sprite->SetTexture(ETexture::TutorialFin);
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CTutorialFinUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTutorialFinUI::Update()
{
	auto pos = m_spTransform.lock()->GetPosition();
	pos->x -= MOVE_SPEED;
	if (pos->x <= 0.0f)
	{
		pos->x = 0.0f;
		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			SCENE_MANAGER->SetNextScene<CSceneSelect>();
		}
		if (!m_bIsCreate)
		{
			const auto& obj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(TEX_POS).lock();
			obj->AddComponent<CButton>();
			m_bIsCreate = true;
		}
	}
	m_spTransform.lock()->SetPosition(pos);
}