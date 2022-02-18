#pragma once
/**
*
* @file		CComponent.h
* @brief	�R���|�[�l���g�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/11/28	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Object/CObject.h>
#include <System/Component/ComponentIDData.h>
#include <memory>

class CGameObject;
/** �R���|�[�l���g�N���X */
class CComponent :public CObject<CComponent>
{
public:
	CComponent() {}
	CComponent(std::weak_ptr<CGameObject> spObj);
	virtual ~CComponent();

	virtual void OnCreate()  {}
	virtual void OnDestroy() {}
	virtual void Update()	 {}
	
	void SetID(EComponentType id)	{ m_typeID = id; }
	EComponentType GetID() const	{ return m_typeID; }
	void SetGameObject(std::weak_ptr<CGameObject> spObj) { m_spGameObject = spObj; }

	// �A�^�b�`���Ă���Q�[���I�u�W�F�N�g
	std::weak_ptr<CGameObject> m_spGameObject;

private:
	// �R���|�[�l���g�^�C�vID
	EComponentType m_typeID;
};

