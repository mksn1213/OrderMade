/**
*
* @file		CModelRenderer.cpp
* @brief	���f���`��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Renderer/CModelRenderer.h>
#include <System/Component/CTransform.h>
#include <System/Renderer/AssimpModel.h>
#include <System/Resource/CModelManager.h>
#include <System/GameObject/CGameObject.h>
#include <System/Graphics/CGraphics.h>
#include <System/Systems/CModelRendererSystem.h>
#include <Scene/CSceneManager.h>

/** �ÓI�����o */
const EComponentType CModelRenderer::comID = EComponentType::ModelRenderer;

/**
* @brief	�R���X�g���N�^
*/
CModelRenderer::CModelRenderer()
	: m_pModel(nullptr)
{
	SetID(ModelRenderer);
}


/**
* @brief	�f�X�g���N�^
*/
CModelRenderer::~CModelRenderer()
{
	if (m_pModel != nullptr)
	{
		m_pModel = nullptr;
	}
}


/**
* @brief	������
*/
void CModelRenderer::OnCreate()
{
	// �����_���[������
	CRenderer::OnCreate();
	// �V�F�[�_�[�Z�b�g
	m_spGameObject.lock()->SetShader(AssimpVS, AssimpPS);
	// �V�X�e�����X�g�Ɋi�[
	CModelRendererSystem* pSystem = SCENE_MANAGER->GetSystem<CModelRendererSystem>(EComponentType::ModelRenderer);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	�j����
*/
void CModelRenderer::OnDestroy()
{
	// �V�X�e�����珜�O
	CModelRendererSystem* pSystem = SCENE_MANAGER->GetSystem<CModelRendererSystem>(EComponentType::ModelRenderer);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	�X�V����
*/
void CModelRenderer::Update()
{

}


/**
* @brief	�`��
*/
void CModelRenderer::Draw(ID3D11DeviceContext* pDC)
{
	if (m_pModel != nullptr)
	{
		m_pModel->m_spGameObject = m_spGameObject;
		m_pModel->Draw(pDC, m_spTransform.lock()->GetWorldMatrix(), eOpacityOnly);
	}
}


/**
* @brief	���f���̃Z�b�g
* @param	model	�Z�b�g���郂�f���^�C�v
*/
void CModelRenderer::SetModel(EModelType model)
{
	m_pModel = MODEL_MANAGER->GetModel(model);
	m_pModel->m_spGameObject = m_spGameObject;
}