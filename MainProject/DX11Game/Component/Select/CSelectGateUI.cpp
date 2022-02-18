/**
*
* @file		CSelectGateUI.cpp
* @brief	�Z���N�g�Q�[�gUI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Select/CSelectGateUI.h>
#include <System/GameObject/CGameObject.h>

/**
* @brief	�R���X�g���N�^
*/
CSelectGateUI::CSelectGateUI()
{

}


/**
* @brief	�f�X�g���N�^
*/
CSelectGateUI::~CSelectGateUI()
{

}


/**
* @brief	������
*/
void CSelectGateUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Billboard");

	// ���O�ݒ�
	obj->SetName("SelectGateUI");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	m_spTransform.lock()->SetScale(Vector3(20.0f, 10.0f, 1.0f));

	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CMeshRenderer>().lock();
	renderer->MakeBillboard();
	m_spRenderer = renderer;
}


/**
* @brief	�j����
*/
void CSelectGateUI::OnDestroy()
{

}


/**
* @brief	�X�V����
*/
void CSelectGateUI::Update()
{

}


/**
* @brief	�e�N�X�`���Z�b�g
* @param	type	�Q�[�g�^�C�v
*/
void CSelectGateUI::SetTexture(CSelectGate::EGateType type)
{
	switch (type)
	{
	case CSelectGate::GateTitle:		m_spRenderer.lock()->SetBaseTexture(ETexture::GateTitle);		break;
	case CSelectGate::GateTutorial:		m_spRenderer.lock()->SetBaseTexture(ETexture::GateTutorial);	break;
	case CSelectGate::GateGame1:		m_spRenderer.lock()->SetBaseTexture(ETexture::GateGame);		break;
	default:																							break;
	}
}
