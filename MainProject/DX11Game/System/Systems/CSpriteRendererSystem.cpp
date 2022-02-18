/**
*
* @file		CSpriteRendererSystem.cpp
* @brief	�X�v���C�g�`��V�X�e���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CSpriteRendererSystem.h>
#include <System/Renderer/CSpriteRenderer.h>
#include <System/GameObject/CGameObject.h>
#include <algorithm>

/**
* @brief	�R���X�g���N�^
*/
CSpriteRendererSystem::CSpriteRendererSystem()
{

}


/**
* @brief	�f�X�g���N�^
*/
CSpriteRendererSystem::~CSpriteRendererSystem()
{

}


/**
* @brief	����������
*/
void CSpriteRendererSystem::OnCreate()
{

}


/**
* @brief	�폜������
*/
void CSpriteRendererSystem::OnDestroy()
{

}


/**
* @brief	�`�揈��
*/
void CSpriteRendererSystem::OnDraw(ID3D11DeviceContext* pDC)
{
	std::for_each(m_pComponentList.begin(), m_pComponentList.end(),
		[&pDC](CSpriteRenderer* renderer)
		{
			if (renderer->m_spGameObject.lock()->IsActive())	renderer->Draw(pDC);
		});
}