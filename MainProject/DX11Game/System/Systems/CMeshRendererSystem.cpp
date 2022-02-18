/**
*
* @file		CMeshRendererSystem.cpp
* @brief	���b�V���`��V�X�e���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CMeshRendererSystem.h>
#include <System/Renderer/CMeshRenderer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Graphics/CGraphics.h>
#include <algorithm>

/**
* @brief	�R���X�g���N�^
*/
CMeshRendererSystem::CMeshRendererSystem()
{

}


/**
* @brief	�f�X�g���N�^
*/
CMeshRendererSystem::~CMeshRendererSystem()
{

}


/**
* @brief	����������
*/
void CMeshRendererSystem::OnCreate()
{

}


/**
* @brief	�폜������
*/
void CMeshRendererSystem::OnDestroy()
{

}


/**
* @brief	�`�揈��
*/
void CMeshRendererSystem::OnDraw(ID3D11DeviceContext* pDC)
{
	std::for_each(m_pComponentList.begin(), m_pComponentList.end(),
		[&pDC](CMeshRenderer* renderer)
		{
			if(renderer->m_spGameObject.lock()->IsActive())	renderer->Draw(pDC);
		});
}