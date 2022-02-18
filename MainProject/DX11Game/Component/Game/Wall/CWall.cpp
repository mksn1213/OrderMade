/**
*
* @file		CWall.cpp
* @brief	�ǃN���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	�����J�n
* @date		2021/12/10	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Wall/CWall.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>


/**
* @brief	�R���X�g���N�^
*/
CWall::CWall()
{

}


/**
* @brief	�f�X�g���N�^
*/
CWall::~CWall()
{

}


/**
* @brief	������
*/
void CWall::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Stationary");

	// ���O�ݒ�
	obj->SetName("Wall");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �R���|�[�l���g�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(20.0f, 20.0f, 20.0f));
	collider->m_pMainScript = this;

	// ���f���̃Z�b�g
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Wall);
}


/**
* @brief	�j����
*/
void CWall::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CWall::Update()
{

}


/**
* @brief	�����蔻��
* @param	collider		����̃R���C�_�[
*/
void CWall::OnCollision(std::weak_ptr<CCollider> collider)
{

}