/**
*
* @file		CFence.cpp
* @brief	��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/01/11	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Field/CFence.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>

/**
* @brief	�R���X�g���N�^
*/
CFence::CFence()
{

}


/**
* @brief	�f�X�g���N�^
*/
CFence::~CFence()
{

}


/**
* @brief	������
*/
void CFence::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Stationary");

	// ���O�ݒ�
	obj->SetName("Fence");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �����_���[�ǉ�
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Fence1);
	
	// �R���C�_�[�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(40.0f, 20.0f, 10.0f), Vector3::up()*10.0f);
	collider->m_pMainScript = this;
}


/**
* @brief	�j����
*/
void CFence::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CFence::Update()
{

}