/**
*
* @file		CActionGaugeBaseUI.cpp
* @brief	�A�N�V�����Q�[�W�x�[�XUI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/26	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/GameUI/CActionGaugeBaseUI.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CMeshRenderer.h>

/**
* @brief	�R���X�g���N�^
*/
CActionGaugeBaseUI::CActionGaugeBaseUI()
{

}


/**
* @brief	�f�X�g���N�^
*/
CActionGaugeBaseUI::~CActionGaugeBaseUI()
{

}


/**
* @brief	������
*/
void CActionGaugeBaseUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Billboard");

	// ���O�ݒ�
	obj->SetName("ActionGaugeBaseUI");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	m_spTransform.lock()->SetScale(Vector3(11.0f/1.5f, 1.5f, 1.0f));

	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CMeshRenderer>().lock();
	renderer->MakeBillboard();
	renderer->SetBaseTexture(ETexture::ActionGaugeBase);
}


/**
* @brief	�j����
*/
void CActionGaugeBaseUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CActionGaugeBaseUI::Update()
{

}