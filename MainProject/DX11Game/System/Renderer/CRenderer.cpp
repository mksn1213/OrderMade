/**
*
* @file		CRenderer.cpp
* @brief	�`��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Renderer/CRenderer.h>
#include <System/GameObject/CGameObject.h>

/**
* @brief	�R���X�g���N�^
*/
CRenderer::CRenderer()
{
}


/**
* @brief	�f�X�g���N�^
*/
CRenderer::~CRenderer()
{

}


/**
* @brief	������
*/
void CRenderer::OnCreate()
{
	// �g�����X�t�H�[�����擾
	m_spTransform = m_spGameObject.lock()->GetComponent<CTransform>();
}


/**
* @brief	�j����
*/
void CRenderer::OnDestroy()
{

}


/**
* @brief	�X�V����
*/
void CRenderer::Update()
{

}
