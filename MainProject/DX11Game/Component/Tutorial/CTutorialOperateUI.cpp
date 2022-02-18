/**
*
* @file		CTutorialOperateUI.cpp
* @brief	�`���[�g���A������UI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/12	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Tutorial/CTutorialOperateUI.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const Vector3	TEX_SIZE1 = Vector3(300.0f, 300.0f, 0.0f);
	const Vector3	TEX_SIZE2 = Vector3(300.0f, 380.0f, 0.0f);
	const Vector3	TEX_SIZE3 = Vector3(300.0f, 200.0f, 0.0f);
	const Vector3	TEX_SIZE4 = Vector3(300.0f, 380.0f, 0.0f);
}

/**
* @brief	�R���X�g���N�^
*/
CTutorialOperateUI::CTutorialOperateUI()
{

}


/**
* @brief	�f�X�g���N�^
*/
CTutorialOperateUI::~CTutorialOperateUI()
{

}


/**
* @brief	������
*/
void CTutorialOperateUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("TutorialOperateUI");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
	// �X�v���C�g�ǉ�
	const auto& sprite = obj->AddComponent<CSpriteRenderer>().lock();
	m_spSprite = sprite;
}


/**
* @brief	�j����
*/
void CTutorialOperateUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTutorialOperateUI::Update()
{

}


/**
* @brief	�e�N�X�`���Z�b�g
* @param	nStageNo	�X�e�[�W�ԍ�
*/
void CTutorialOperateUI::SetTexture(int nStageNo)
{
	const auto& sprite = m_spSprite.lock();
	switch (nStageNo)
	{
	case 0:	sprite->SetTexture(ETexture::TutorialGuide1);
			sprite->SetDrawSize(TEX_SIZE1);					break;
	case 1:	sprite->SetTexture(ETexture::TutorialGuide2);	
			sprite->SetDrawSize(TEX_SIZE2);					break;
	case 2:	sprite->SetTexture(ETexture::TutorialGuide3);	
			sprite->SetDrawSize(TEX_SIZE3);					break;
	case 3:	sprite->SetTexture(ETexture::TutorialGuide4);	
			sprite->SetDrawSize(TEX_SIZE4);					break;
	default:												break;
	}
}