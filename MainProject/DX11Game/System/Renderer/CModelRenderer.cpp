/**
*
* @file		CModelRenderer.cpp
* @brief	モデル描画クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	実装開始
*
*/

/** インクルード部 */
#include <System/Renderer/CModelRenderer.h>
#include <System/Component/CTransform.h>
#include <System/Renderer/AssimpModel.h>
#include <System/Resource/CModelManager.h>
#include <System/GameObject/CGameObject.h>
#include <System/Graphics/CGraphics.h>
#include <System/Systems/CModelRendererSystem.h>
#include <Scene/CSceneManager.h>

/** 静的メンバ */
const EComponentType CModelRenderer::comID = EComponentType::ModelRenderer;

/**
* @brief	コンストラクタ
*/
CModelRenderer::CModelRenderer()
	: m_pModel(nullptr)
{
	SetID(ModelRenderer);
}


/**
* @brief	デストラクタ
*/
CModelRenderer::~CModelRenderer()
{
	if (m_pModel != nullptr)
	{
		m_pModel = nullptr;
	}
}


/**
* @brief	生成時
*/
void CModelRenderer::OnCreate()
{
	// レンダラー初期化
	CRenderer::OnCreate();
	// シェーダーセット
	m_spGameObject.lock()->SetShader(AssimpVS, AssimpPS);
	// システムリストに格納
	CModelRendererSystem* pSystem = SCENE_MANAGER->GetSystem<CModelRendererSystem>(EComponentType::ModelRenderer);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	破棄時
*/
void CModelRenderer::OnDestroy()
{
	// システムから除外
	CModelRendererSystem* pSystem = SCENE_MANAGER->GetSystem<CModelRendererSystem>(EComponentType::ModelRenderer);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	更新処理
*/
void CModelRenderer::Update()
{

}


/**
* @brief	描画
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
* @brief	モデルのセット
* @param	model	セットするモデルタイプ
*/
void CModelRenderer::SetModel(EModelType model)
{
	m_pModel = MODEL_MANAGER->GetModel(model);
	m_pModel->m_spGameObject = m_spGameObject;
}