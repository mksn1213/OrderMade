/**
*
* @file		CTitleFlower.cpp
* @brief	�^�C�g���ԃN���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/10	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Title/CTitleFlower.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Effect/CEffectManager.h>

/** �}�N����` */
namespace
{
	const int EFFECT_PLAY_INTERVAL = 240;	// �G�t�F�N�g�Đ��Ԋu
	const int EFFECT_PLAY_INTERVAL2 = 60;	// �G�t�F�N�g�Đ��Ԋu
	const int MODEL_CHANGE_INTERVAL = 30;	// ���f���ύX�Ԋu
}

/**
* @brief	�R���X�g���N�^
*/
CTitleFlower::CTitleFlower()
	: m_nModelNum((int)EModelType::Flower_W)
	, m_nFrame(0)
	, m_nFrame2(0)
	, m_nFrame3(0)
	, m_bChange(false)
{
	
}


/**
* @brief	�f�X�g���N�^
*/
CTitleFlower::~CTitleFlower()
{

}


/**
* @brief	������
*/
void CTitleFlower::OnCreate()
{
	// �X�N���v�g������
	CScriptBase::OnCreate();

	// ���f���ǉ�
	const auto& renderer = m_spGameObject.lock()->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Flower_W);
	m_spRenderer = renderer;
	m_nModelNum = (int)EModelType::Flower_W;
}


/**
* @brief	�j����
*/
void CTitleFlower::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTitleFlower::Update()
{
	// �G�t�F�N�g�Đ�
	if (m_nFrame > EFFECT_PLAY_INTERVAL)
	{
		EFFECT_MANAGER->Play(EEffectType::Grow, m_spTransform.lock()->GetPosition());
		m_nFrame = 0;
		m_bChange = true;
	}
	m_nFrame++;
	
	if (m_nFrame2 > EFFECT_PLAY_INTERVAL2)
	{
		EFFECT_MANAGER->Play(EEffectType::GrowAction, m_spTransform.lock()->GetPosition()+Vector3::up()*5);
		m_nFrame2 = 0;
	}
	m_nFrame2++;

	if (m_bChange)
	{
		if (m_nFrame3 > MODEL_CHANGE_INTERVAL)
		{
			m_nModelNum++;
			if (m_nModelNum > (int)EModelType::Flower_B)
			{
				m_nModelNum = (int)EModelType::Flower_W;
			}
			m_spRenderer.lock()->SetModel((EModelType)m_nModelNum);
			m_nFrame3 = 0;
			m_bChange = false;
		}
		m_nFrame3++;
	}
}