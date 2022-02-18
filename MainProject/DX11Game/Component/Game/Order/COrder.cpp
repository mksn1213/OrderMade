/**
*
* @file		COrder.cpp
* @brief	�����N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	�����J�n
* @date		2021/12/21	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Order/COrder.h>
#include <System/CTimer.h>
#include <System/Renderer/CSpriteRenderer.h>
#include <Component/Game/Order/COrderManager.h>
#include <Scene/CSceneManager.h>

// �����p
#include <System/GameObject/CGameObjectManager.h>
#include <Component/Game/Order/GameUI/COrderBoardUI.h>

/** �}�N����` */
namespace
{
	const int	TIME				= 60 * 45;	// ������������
	const float CREATE_INTERVAL_X	= 150.0f;	// UI��X�����Ԋu
	const float CREATE_SPACE_Y		= 150.0f;
}

/** �ÓI�����o */
const EComponentType COrder::comID = EComponentType::Order;

/**
* @brief	�R���X�g���N�^
*/
COrder::COrder()
	: m_pTimer(nullptr)
{
}


/**
* @brief	�f�X�g���N�^
*/
COrder::~COrder()
{
	SAFE_DELETE(m_pTimer);
}


/**
* @brief	������
*/
void COrder::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �^�O�ݒ�
	obj->SetTag("Order");
	// ���O�ݒ�
	obj->SetName("Order");
	// �R���|�[�l���gID�ݒ�
	SetID(Order);
	// �^�C�}�[����
	m_pTimer = new CTimer(TIME);
}


/**
* @brief	�j����
*/
void COrder::OnDestroy()
{
	// �X�v���C�g�I�u�W�F�N�g�폜
	m_spSpriteObject.lock()->Destroy();
}


/**
* @brief	�X�V����
*/
void COrder::Update()
{
	// �f�B�]���u�p�����[�^�X�V
	m_spSpriteRenderer.lock()->SetParam(m_pTimer->GetTime() / (float)TIME);
}


/**
* @brief	�X�V�o���邩�ǂ���
* @return	bool	�X�V�̉�
*/
bool COrder::IsUpdate()
{
	// �X�V�o���Ȃ���ΏI��
	if (!m_pTimer->Update())	return false;
	// �X�V
	Update();
	return true;
}


/**
* @brief	UI�̐���
*/
void COrder::CreateUI()
{
	// ����������W�̌v�Z
	int num = ORDER_MANAGER->GetOrderQuantity() + 1;
	Vector3 createPos(-SCREEN_WIDTH / 2 + num * CREATE_INTERVAL_X, SCREEN_HEIGHT / 2 + CREATE_SPACE_Y, 1.0f);

	// ����UI����
	const auto& boardUIObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(createPos).lock();
	const auto& boardUICom = boardUIObj->AddComponent<COrderBoardUI>().lock();
	boardUICom->SetOrder(m_orderData);
	m_spSpriteObject = boardUIObj;
	m_spSpriteRenderer = m_spSpriteObject.lock()->GetComponent<CSpriteRenderer>().lock();

	// �}���`�e�N�X�`���p�V�F�[�_�[�Z�b�g
	m_spSpriteObject.lock()->SetShader(EVertexShaderKind::Simple2DVS, EPixelShaderKind::MultiTexturePS);

	// �����f�[�^����e�N�X�`�����Z�b�g
	SetOrderTexture();
}


/**
* @brief	�����f�[�^����Ɏg�p����e�N�X�`�����Z�b�g
*/
void COrder::SetOrderTexture()
{
	// ���A���̗L��
	const auto& renderer = m_spSpriteRenderer.lock();
	if (m_orderData.m_bPotted)	renderer->SetMultiTexture(ETexture::OrderPotted_true);
	else						renderer->SetMultiTexture(ETexture::OrderPotted_false);

	// �����i�K
	if (m_orderData.m_eKind == EObjectType::Sprout)			renderer->SetMultiTexture(ETexture::OrderPlant_Sprout, 1);
	else if (m_orderData.m_eKind == EObjectType::Flower)	renderer->SetMultiTexture(ETexture::OrderPlant_Flower, 1);

	// �f�B�]���u�e�N�X�`���Z�b�g
	renderer->SetEffectTexture(ETexture::Dissolve2);
}
