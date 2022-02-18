/**
*
* @file		CTrashBox.cpp
* @brief	���ݔ��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/30	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Trash/CTrashBox.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CModelRenderer.h>
#include <Component/Game/Player/Action/CPutAction.h>
#include <Component/Game/Player/CPlayer.h>

/**
* @brief	�R���X�g���N�^
*/
CTrashBox::CTrashBox()
{

}


/**
* @brief	�f�X�g���N�^
*/
CTrashBox::~CTrashBox()
{

}


/**
* @brief	������
*/
void CTrashBox::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �^�O�ݒ�
	obj->SetTag("Stationary");

	// ���O�ݒ�
	obj->SetName("TrashBox");

	// �R���|�[�l���gID�ݒ�
	SetID(Script);

	// �R���|�[�l���g�ǉ�
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Box, Vector3(20.0f, 20.0f, 20.0f));
	collider->m_pMainScript = this;

	// ���f���̃Z�b�g
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::TrashBox);
}


/**
* @brief	�j����
*/
void CTrashBox::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CTrashBox::Update()
{

}


/**
* @brief	�����蔻��
* @param	collider		����̃R���C�_�[
*/
void CTrashBox::OnCollision(std::weak_ptr<CCollider> collider)
{

}


/**
* @brief	�s�����������邩�ǂ��� �� ����Ώ��������s����
* @details	���肪�A�C�e���������Ă���ꍇ�̏���
* @param	collider		����̃R���C�_�[
* @param	item			�A�C�e���̃Q�[���I�u�W�F�N�g
* @return	bool			�����̗L��
*/
bool CTrashBox::ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)
{
	// �o�P�c�������ꍇ�I��
	if (itemObj.lock()->GetObjectID() == EObjectType::Bucket)	return false;

	// �A�C�e���̃����[�X
	const auto& playerObj = collider.lock()->m_spTransform.lock()->GetParent().lock();
	playerObj->GetComponent<CPlayer>().lock()->ReleaseItem();

	itemObj.lock()->Destroy();

	return false;
}
