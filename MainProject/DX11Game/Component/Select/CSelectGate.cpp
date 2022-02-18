/**
*
* @file		CSelectGate.cpp
* @brief	�Z���N�g�Q�[�g�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Select/CSelectGate.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneTitle.h>
#include <Scene/CSceneGame.h>
#include <Scene/CSceneTutorial.h>
#include <System/GameObject/CGameObjectManager.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/CPlayerTarget.h>
#include <Component/Select/CSelectGateUI.h>

/**
* @brief	�R���X�g���N�^
*/
CSelectGate::CSelectGate()
	: m_eType(GateTitle)
{

}


/**
* @brief	�R���X�g���N�^
*/
CSelectGate::~CSelectGate()
{

}


/**
* @brief	������
*/
void CSelectGate::OnCreate()
{
	const auto& obj = m_spGameObject.lock();
	
	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Stationary");

	// ���O�̐ݒ�
	obj->SetName("SelectGate");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ShipGate);

	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(40.0f, 40.0f, 10.0f), Vector3(0.0f, 20.0f, 0.0f));
	collider->m_pMainScript = this;
}


/**
* @brief	�j����
*/
void CSelectGate::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V
*/
void CSelectGate::Update()
{

}


/**
* @brief	�����蔻��
* @param	collider	����̃R���C�_�[
*/
void CSelectGate::OnCollision(std::weak_ptr<CCollider> collider)
{
	// �^�[�Q�b�g�ɑI������Ă���ꍇ�`���ς���
	if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)
	{
		// �^�[�Q�b�g�����ɑ��݂��Ă����ꍇ�I��
		const auto& target = collider.lock()->m_spGameObject.lock()->GetComponent<CPlayerTarget>().lock();
		if (target->IsTarget())	return;
		// �^�[�Q�b�g�̌���
		target->TargetON();
		// �V�F�[�_�[�ύX
		const auto& obj = m_spGameObject.lock();
		obj->SetShader(EVertexShaderKind::AssimpVS, EPixelShaderKind::AssimpTargetPS);
	}
}


/**
* @brief	�s�����������邩�ǂ��� �� ����Ώ��������s����
* @details	���肪�A�C�e���������Ă���ꍇ�̏���
* @param	collider		����̃R���C�_�[
* @return	bool			�����̗L��
*/
bool CSelectGate::ExistsProcess(std::weak_ptr<CCollider> collider)
{
	// �t�F�[�h����������I��
	const auto& scene = SCENE_MANAGER;
	if (scene->GetFadeState() != CFade::EFade::FADE_NONE)	return false;

	// �Q�[�g�^�C�v�ɂ���ĕ���
	switch (m_eType)
	{
	case CSelectGate::GateTitle:	scene->SetNextScene<CSceneTitle>();		break;
	case CSelectGate::GateTutorial:	scene->SetNextScene<CSceneTutorial>();	break;
	case CSelectGate::GateGame1:	scene->SetNextScene<CSceneGame>();		break;
	default:
		break;
	}
	return false;
}


/**
* @brief	�Q�[�g�^�C�v�Z�b�g
* @param	type	�Q�[�g�^�C�v
*/
void CSelectGate::SetGateType(EGateType type)
{
	m_eType = type;

	// UI����
	const auto& obj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	obj->m_spTransform.lock()->SetPosition(m_spTransform.lock()->GetPosition() + Vector3::up() * 50.0f);
	const auto& com = obj->AddComponent<CSelectGateUI>().lock();
	com->SetTexture(m_eType);
}