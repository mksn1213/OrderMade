#pragma once
/**
*
* @file		CTransform.h
* @brief	�g�����X�t�H�[���N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/29	�����J�n
* @date		2021/12/10	�e�q�֌W�������쐬
*
*/

/** �C���N���[�h�� */
#include <System/Component/CComponent.h>
#include <System/Utility/Vector3.h>
#include <list>
#include <memory>

/**
* @enum		EDirection
* @brief	����
*/
enum EDirection
{
	Front=0,	// �O��
	Back,		// ���
	Up,			// ���
	Down,		// ����
	Right,		// �E
	Left,		// ��
};

// �O��`
class CGameObject;

/** �g�����X�t�H�[���N���X */
class CTransform final: public CComponent
{
public:
	CTransform();
	virtual ~CTransform();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetParent(std::weak_ptr<CGameObject> spParent, EDirection dir, float fLocalPos);
	void SetParent(std::weak_ptr<CGameObject> spParent, EDirection dir, float fLocalPos, EDirection dir2, float fLocalPos2);

	std::weak_ptr<CGameObject> GetParent() { return m_spParent; }
	void AddChild(std::weak_ptr<CGameObject> spChild);
	std::list<std::weak_ptr<CGameObject>> GetChildList() { return m_spChildList; }

	void UpdateMatrix();
	XMFLOAT4X4& GetWorldMatrix()			{ return m_mtxWorld; }
	void SetWorld(XMFLOAT4X4& mWorld)		{ m_mtxWorld = mWorld; }
	XMFLOAT4X4& GetLocalMatrix()			{ return m_mtxLocalWorld; }
	void SetLocalMatrix(XMFLOAT4X4& mLocal) { m_mtxLocalWorld = mLocal; }

	void SetPosition(Vector3 pos)	{ m_position = pos; }
	void SetRotation(Vector3 rot)	{ m_rotation = rot; }
	void SetScale(Vector3 scale)	{ m_scale = scale; }
	void SetLocalPosition(EDirection dir, float fLocalPos, bool add = false);

	Vector3 GetPosition()			{ return m_position; }
	Vector3 GetRotation()			{ return m_rotation; }
	Vector3 GetScale()				{ return m_scale; }
	
	void ReplaceChildAll(std::weak_ptr<CGameObject> parent);
	void ReplaceChild(std::weak_ptr<CGameObject> parent, bool forward);
	void ReleaseRelationship(std::weak_ptr<CGameObject> childObj);
	static void SetParentChildRelation(std::weak_ptr<CGameObject> parent, std::weak_ptr<CGameObject> child, EDirection dir = EDirection::Front, float fLocalPos = 0.0f);
	static void SetParentChildRelation(std::weak_ptr<CGameObject> parent, std::weak_ptr<CGameObject> child, EDirection dir, float fLocalPos, EDirection dir2, float fLocalPos2);

protected:
	// ���W
	Vector3 m_position;
	// ��]
	Vector3 m_rotation;
	//�@�X�P�[��
	Vector3 m_scale;

private:
	// �}�g���b�N�X
	XMFLOAT4X4								m_mtxWorld;
	// ���[�J���}�g���b�N�X
	XMFLOAT4X4								m_mtxLocalWorld;
	// �e�̃Q�[���I�u�W�F�N�g
	std::weak_ptr<CGameObject>				m_spParent;
	// �q�̃Q�[���I�u�W�F�N�g���X�g
	std::list<std::weak_ptr<CGameObject>>	m_spChildList;

public:
	// �R���|�[�l���gID
	static const EComponentType comID;
};