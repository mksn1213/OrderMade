/**
*
* @file		CIconUI.cpp
* @brief	�A�C�R��UI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/28	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>
#include <System/Utility/CColor.h>

// �R���|�[�l���g
#include <System/Renderer/CMeshRenderer.h>

/** �}�N����` */
namespace
{
	const float MOVE_SPEED_X = 1.0f;
}

/**
* @brief	�R���X�g���N�^
*/
CIconUI::CIconUI()
	: m_bMoveFlag(false)
	, m_fRemainingDistance(0.0f)
{

}


/**
* @brief	�f�X�g���N�^
*/
CIconUI::~CIconUI()
{

}


/**
* @brief	������
*/
void CIconUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	
	// �^�O�ݒ�
	obj->SetTag("Billboard");

	// ���O�ݒ�
	obj->SetName("IconUI");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	m_spTransform.lock()->SetScale(Vector3(3.5f, 3.5f, 1.0f));

	// �����_���[�ǉ�
	const auto& renderer = m_spGameObject.lock()->AddComponent<CMeshRenderer>().lock();
	renderer->MakeBillboard();
	m_spRenderer = renderer;
}


/**
* @brief	�j����
*/
void CIconUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CIconUI::Update()
{
	// �A�C�R���ړ�����
	if (m_bMoveFlag)
	{
		auto localMatrix = m_spTransform.lock()->GetLocalMatrix();
		if (m_fRemainingDistance > 0.0f)
		{
			localMatrix._41 += MOVE_SPEED_X;
			m_fRemainingDistance -= MOVE_SPEED_X;
			// �c��ړ��ʂ��Ȃ��Ȃ�����I��
			if (m_fRemainingDistance <= 0.0f)
			{
				m_fRemainingDistance = 0.0f;
				m_bMoveFlag = false;
			}
		}
		else
		{
			localMatrix._41 -= MOVE_SPEED_X;
			m_fRemainingDistance += MOVE_SPEED_X;
			// �c��ړ��ʂ��Ȃ��Ȃ�����I��
			if (m_fRemainingDistance >= 0.0f)
			{
				m_fRemainingDistance = 0.0f;
				m_bMoveFlag = false;
			}
		}
		m_spTransform.lock()->SetLocalMatrix(localMatrix);
	}
}


/**
* @brief	�A�C�R���̃e�N�X�`���Z�b�g
* @param	type
*/
void CIconUI::SetIconTexture(ETexture type)
{
	m_spRenderer.lock()->SetBaseTexture(type);
}


/**
* @brief	�A�C�R���̃e�N�X�`���Z�b�g
* @param	color
*/
void CIconUI::SetIconTexture(CColor color)
{
	if		(color.colorType == CColor::EColor::Red)	m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Red);
	else if (color.colorType == CColor::EColor::Green)	m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Green);
	else if (color.colorType == CColor::EColor::Blue)	m_spRenderer.lock()->SetBaseTexture(ETexture::Icon_Blue);
}