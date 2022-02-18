/**
*
* @file		CModelRendererSystem.cpp
* @brief	���f���`��V�X�e���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Systems/CModelRendererSystem.h>
#include <System/Renderer/CModelRenderer.h>
#include <System/GameObject/CGameObject.h>
#include <System/Graphics/CGraphics.h>
#include <algorithm>

/**
* @brief	�R���X�g���N�^
*/
CModelRendererSystem::CModelRendererSystem()
{

}


/**
* @brief	�f�X�g���N�^
*/
CModelRendererSystem::~CModelRendererSystem()
{

}


/**
* @brief	����������
*/
void CModelRendererSystem::OnCreate()
{
}


/**
* @brief	�폜������
*/
void CModelRendererSystem::OnDestroy()
{
}


/**
* @brief	�`�揈��
*/
void CModelRendererSystem::OnDraw(ID3D11DeviceContext* pDC)
{
	// �V���h�E�}�b�v
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_OFF);
	float color[] = { 1,1,1,1 };
	GRAPHICS->SetShadowRenderTarget(color);
	GRAPHICS->SetShadowDepthStencilView();

	// �e�N�X�`���֏�������
	std::for_each(m_pComponentList.begin(), m_pComponentList.end(),
		[&pDC](CModelRenderer* renderer)
	{
		const auto& obj = renderer->m_spGameObject.lock();
		obj->SaveShaderKind();
		obj->SetShader(DepthWriteVS, DepthWritePS);
		if (obj->IsActive())	renderer->Draw(pDC);
	});

	// �ʏ�`��
	GRAPHICS->SetDepthStencilState(CGraphics::DEPTHSTENCIL_ON);
	GRAPHICS->SetRenderTargetDefault();
	GRAPHICS->SetDepthStencilViewDefault();

	std::for_each(m_pComponentList.begin(),m_pComponentList.end(),
		[&pDC](CModelRenderer* renderer)
		{
			const auto& obj = renderer->m_spGameObject.lock();
			obj->SetShader(obj->GetVSKindBuffer(), obj->GetPSKindBuffer());
			if (obj->IsActive())	renderer->Draw(pDC);
			obj->SetShader(AssimpVS, AssimpPS);
		});
}