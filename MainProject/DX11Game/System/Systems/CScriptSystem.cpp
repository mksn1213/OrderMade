/**
*
* @file		CScriptSystem.cpp
* @brief	�X�N���v�g�V�X�e���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CScriptSystem.h>
#include <System/Component/CScriptBase.h>
#include <System/GameObject/CGameObject.h>
#include <algorithm>

/**
* @brief	�R���X�g���N�^
*/
CScriptSystem::CScriptSystem()
{

}


/**
* @brief	�f�X�g���N�^
*/
CScriptSystem::~CScriptSystem()
{

}


/**
* @brief	����������
*/
void CScriptSystem::OnCreate()
{

}


/**
* @brief	�폜������
*/
void CScriptSystem::OnDestroy()
{

}


/**
* @brief	�X�V������
*/
void CScriptSystem::OnUpdate()
{
	std::for_each(m_pComponentList.begin(),m_pComponentList.end(),
		[](CScriptBase* script)
		{
			if (script->m_spGameObject.lock()->IsActive())	script->Update();
		});
}
