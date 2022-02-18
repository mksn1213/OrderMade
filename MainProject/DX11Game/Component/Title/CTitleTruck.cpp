/**
*
* @file		CTitleTruck.cpp
* @brief	�^�C�g���g���b�N�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/10	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Title/CTitleTruck.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Effect/CEffectManager.h>
#include <random>

/** �}�N����` */
namespace
{
	const float SPEED		= 0.5f;			// �ړ����x
	const float START_POS	= -300.0f;		// �n�_
	const float END_POS		= 300.0f;		// �I�_
	const int	EFFECT_PLAY_INTERVAL = 10;	// �G�t�F�N�g�Đ��Ԋu
}

/**
* @brief	�R���X�g���N�^
*/
CTitleTruck::CTitleTruck()
	: m_nFrame(0)
{

}


/**
* @brief	�f�X�g���N�^
*/
CTitleTruck::~CTitleTruck()
{

}


/**
* @brief	������
*/
void CTitleTruck::OnCreate()
{
	// �X�N���v�g������
	CScriptBase::OnCreate();

	// ���f���ǉ�
	const auto& renderer = m_spGameObject.lock()->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ShipTruck);

	m_spTransform.lock()->SetRotation(Vector3(0.0f, 270.0f, 0.0f));

	// �ԃI�u�W�F�N�g����
	const auto& flowerObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& flowerRenderer = flowerObj->AddComponent<CModelRenderer>().lock();
	int num = (int)EModelType::Flower_W;
	num += rand() % 7;
	flowerRenderer->SetModel((EModelType)num);
	m_spRenderer = flowerRenderer;

	// ���A���I�u�W�F�N�g����
	const auto& pottedObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& pottedRenderer = pottedObj->AddComponent<CModelRenderer>().lock();
	pottedRenderer->SetModel(EModelType::Potted);
	CTransform::SetParentChildRelation(pottedObj, flowerObj, EDirection::Up, 3.0f);
	CTransform::SetParentChildRelation(m_spGameObject, pottedObj, EDirection::Up, 10.0f, EDirection::Back, 10.0f);
}


/**
* @brief	�j����
*/
void CTitleTruck::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTitleTruck::Update()
{
	// �G�t�F�N�g�Đ�
	if (m_nFrame > EFFECT_PLAY_INTERVAL)
	{
		EFFECT_MANAGER->Play(EEffectType::Smoke, m_spTransform.lock()->GetPosition()+Vector3::left()*10);
		m_nFrame = 0;
	}
	m_nFrame++;

	// �ړ�����
	const auto& trans = m_spTransform.lock();
	auto pos = trans->GetPosition();
	pos->x += SPEED;
	// �I�_�܂ōs�����ꍇ
	if (pos->x >= END_POS)
	{
		pos->x = START_POS;
		// ���f���̕ύX
		int num = (int)EModelType::Flower_W;
		num += rand() % 7;
		m_spRenderer.lock()->SetModel((EModelType)num);
	}
	trans->SetPosition(pos);
}