/**
*
* @file		CGameObjectManager.cpp
* @brief	�Q�[���I�u�W�F�N�g�Ǘ��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	�����J�n
* @date		2021/11/30	�I�u�W�F�N�g�Ǘ�����Q�[���I�u�W�F�N�g�Ǘ��ɕύX
* @date		2022/01/23	�V���O���g���p��
*
*/

/** �C���N���[�h�� */
#include <System/GameObject/CGameObjectManager.h>
#include <System/CDebugProc.h>
#include <System/Graphics/CGraphics.h>
#include <System/Texture/TextureFactory.h>
#include <System/Graphics/ShaderList.h>
#include <System/Renderer/CSpriteRenderer.h>

/**
* @brief	�R���X�g���N�^
*/
CGameObjectManager::CGameObjectManager()
{
	
}


/**
* @brief	�f�X�g���N�^
*/
CGameObjectManager::~CGameObjectManager()
{

}


/**
* @brief	������
*/
HRESULT CGameObjectManager::Init()
{
	m_spGameObjectList.clear();
	return S_OK;
}


/**
* @brief	�I������
*/
void CGameObjectManager::Uninit()
{
	// �I�u�W�F�N�g�S�č폜
	for (auto it = m_spGameObjectList.begin(); it != m_spGameObjectList.end();)
	{
		(*it)->RemoveComponentAll();
		it = m_spGameObjectList.erase(it);
	}
	m_spGameObjectList.clear();

	// �R���C�_�[���X�g�N���A
	CCollider::ClearList();
}