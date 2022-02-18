/**
*
* @file		CShipTruck.cpp
* @brief	�o�׃g���b�N�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/07	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Order/CShipTruck.h>
#include <System/GameObject/CGameObject.h>
#include <System/Effect/CEffectManager.h>
#include <System/Sound/CSound.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>

/** �}�N����` */
namespace
{
	const float SPEED		= 1.5f;			// �ړ����x
	const float FIN_POS_X	= 300.0f;		// �I�����W
	const int	EFFECT_PLAY_INTERVAL = 5;	// �G�t�F�N�g�Đ��Ԋu
}

/**
* @brief	�R���X�g���N�^
*/
CShipTruck::CShipTruck()
	: m_bMove(false)
	, m_bShipping(false)
	, m_bFin(false)
	, m_gatePos(Vector3::zero())
	, m_bIsPlaySE(false)
	, m_nFrame(0)
{

}


/**
* @brief	�f�X�g���N�^
*/
CShipTruck::~CShipTruck()
{

}


/**
* @brief	������
*/
void CShipTruck::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Stationary");
	// ���O�ݒ�
	obj->SetName("ShipTruck");
	// �R���|�[�l���gID
	SetID(Script);
	// ���f���̃Z�b�g
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ShipTruck);
	// SE�{�����[���Z�b�g
	SOUND_MANAGER->SetVolume(SE_CAR, 3.0f);
}


/**
* @brief	�j����
*/
void CShipTruck::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CShipTruck::Update()
{
	// �ړ��t���O�������Ă���Έړ�
	if (m_bMove)
	{
		// SE�Đ�
		if (!m_bIsPlaySE)
		{
			SOUND_MANAGER->Play(SE_CAR);
			m_bIsPlaySE = true;
		}
		// �G�t�F�N�g�Đ�
		if (m_nFrame > EFFECT_PLAY_INTERVAL)
		{
			EFFECT_MANAGER->Play(EEffectType::Smoke, m_spTransform.lock()->GetPosition());
			m_nFrame = 0;
		}
		m_nFrame++;
		auto pos = m_spTransform.lock()->GetPosition();
		pos->x += SPEED;
		m_spTransform.lock()->SetPosition(pos);
		if (pos->x >= m_gatePos->x)	m_bMove = false;
	}

	// �o�׃t���O�������Ă���Έړ�
	if (m_bShipping)
	{
		// SE�Đ�
		if (!m_bIsPlaySE)
		{
			SOUND_MANAGER->Play(SE_CAR);
			m_bIsPlaySE = true;
		}
		// �G�t�F�N�g�Đ�
		if (m_nFrame > EFFECT_PLAY_INTERVAL)
		{
			EFFECT_MANAGER->Play(EEffectType::Smoke, m_spTransform.lock()->GetPosition());
			m_nFrame = 0;
		}
		m_nFrame++;
		auto pos = m_spTransform.lock()->GetPosition();
		pos->x += SPEED;
		m_spTransform.lock()->SetPosition(pos);
		if (pos->x >= m_gatePos->x + FIN_POS_X)
		{
			m_bFin = true;
			m_bShipping = false;
		}
	}
}