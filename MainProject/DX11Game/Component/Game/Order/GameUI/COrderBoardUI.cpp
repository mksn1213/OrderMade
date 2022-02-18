/**
*
* @file		COrderBoardUI.cpp
* @brief	����(�Ŕ�)UI�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Order/GameUI/COrderBoardUI.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Order/COrderData.h>
#include <System/Sound/CSound.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const float FALL_SPEED		= 10.0f;	// �����X�s�[�h
	const float MOVE_SPEED_X	= 5.0f;		// X�����ړ��X�s�[�h
}

/**
* @brief	�R���X�g���N�^
*/
COrderBoardUI::COrderBoardUI()
	: m_bMoveFlag(false)
	, m_fRemainingDistance(0.0f)
	, m_bIsPlaySound(false)
{

}


/**
* @brief	�f�X�g���N�^
*/
COrderBoardUI::~COrderBoardUI()
{

}


/**
* @brief	������
*/
void COrderBoardUI::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Sprite");

	// ���O�ݒ�
	obj->SetName("OrderBoardUI");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �X�v���C�g�Z�b�g
	const auto& sprite = obj->AddComponent<CSpriteRenderer>();
	m_spSprite = sprite;
	m_spSprite.lock()->SetDrawSize(Vector3(100.0f, 120.0f, 1.0f));
}


/**
* @brief	�j����
*/
void COrderBoardUI::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void COrderBoardUI::Update()
{
	// �����ړ�����
	auto pos = m_spTransform.lock()->GetPosition();
	if (pos->y >= -SCREEN_HEIGHT / 2 + m_spSprite.lock()->GetDrawSize()->y / 2)
	{
		pos->y -= FALL_SPEED;
	}
	else
	{
		// ��x�̂�SE���Đ�
		if (!m_bIsPlaySound)
		{
			SOUND_MANAGER->SetVolume(SE_ORDER_IN, 4.5f);
			SOUND_MANAGER->Play(SE_ORDER_IN);
			m_bIsPlaySound = true;
		}
	}

	// ���l�߈ړ�����
	if (m_bMoveFlag)
	{
		pos->x -= MOVE_SPEED_X;
		m_fRemainingDistance -= MOVE_SPEED_X;
		// �c��ړ��ʂ��Ȃ��Ȃ�����I��
		if (m_fRemainingDistance <= 0.0f)
		{
			m_fRemainingDistance = 0.0f;
			m_bMoveFlag = false;
		}
	}

	// ���W���f
	m_spTransform.lock()->SetPosition(pos);
}


/**
* @brief	�����f�[�^����Ɏg�p����e�N�X�`�����Z�b�g����
* @param	data	�����f�[�^
*/
void COrderBoardUI::SetOrder(COrderData data)
{
	switch (data.m_eColor)
	{
	case CColor::EColor::White:		m_spSprite.lock()->SetTexture(ETexture::OrderBoard_White);		break;
	case CColor::EColor::Cyan:		m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Cyan);		break;
	case CColor::EColor::Magenta:	m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Magenta);	break;
	case CColor::EColor::Yellow:	m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Yellow);		break;
	case CColor::EColor::Red:		m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Red);		break;
	case CColor::EColor::Green:		m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Green);		break;
	case CColor::EColor::Blue:		m_spSprite.lock()->SetTexture(ETexture::OrderBoard_Blue);		break;
	default:																						break;
	}
}