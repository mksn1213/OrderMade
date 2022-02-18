/**
*
* @file		CActionGaugeUI.cpp
* @brief	�A�N�V�����Q�[�WUI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/26	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Player/Action/GameUI/CActionGaugeUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>

// �R���|�[�l���g
#include <System/Renderer/CMeshRenderer.h>

/**
* @brief	�R���X�g���N�^
*/
CActionGaugeUI::CActionGaugeUI()
{

}


/**
* @brief	�f�X�g���N�^
*/
CActionGaugeUI::~CActionGaugeUI()
{

}


/**
* @brief	������
*/
void CActionGaugeUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Billboard");

	// ���O�ݒ�
	obj->SetName("ActionGaugeUI");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	m_spTransform.lock()->SetScale(Vector3(0.0f, 1.0f, 1.0f));

	// �����_���[�ǉ�
	const auto& renderer = m_spGameObject.lock()->AddComponent<CMeshRenderer>().lock();
	renderer->MakeBillboard();
	renderer->SetBaseTexture(ETexture::ActionGauge);
}


/**
* @brief	�j����
*/
void CActionGaugeUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CActionGaugeUI::Update()
{
	// �T�C�Y�X�V
	auto scale = m_spTransform.lock()->GetScale();
	scale->x += m_fIncrease/1.5f;
	m_spTransform.lock()->SetScale(scale);

	// ���[�J�����W�X�V
	m_spTransform.lock()->SetLocalPosition(EDirection::Right, m_fIncrease / 1.5f, true);
}