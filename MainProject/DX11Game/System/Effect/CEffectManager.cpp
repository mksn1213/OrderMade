/**
*
* @file		CEffectManager.cpp
* @brief	エフェクト管理クラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/08	実装開始
*
*/

/** インクルード部 */
#include <System/Effect/CEffectManager.h>
#include <System/CInput.h>
#include <System/Camera/CCameraManager.h>

/** マクロ定義 */
namespace
{
	// エフェクトファイル名
	const char16_t* EffectFileName[MaxEffect] =
	{
		u"data/Effect/Smoke.efk",
		u"data/Effect/PlantSmoke.efk",
		u"data/Effect/OvenSmoke.efk",
		u"data/Effect/Fire.efk",
		u"data/Effect/Grow.efk",
		u"data/Effect/GrowAction.efk",
		u"data/Effect/Ship.efk",
		u"data/Effect/Water.efk"
	};
}

/**
* @brief	コンストラクタ
*/
CEffectManager::CEffectManager()
{

}


/**
* @brief	デストラクタ
*/
CEffectManager::~CEffectManager()
{

}


/**
* @brief	初期化処理
*/
HRESULT CEffectManager::Init()
{
	// Effekseer初期化
	m_renderer = EffekseerRendererDX11::Renderer::Create(GetDevice(), GetDeviceContext(), 8000);
	m_manager = Effekseer::Manager::Create(8000);
	// 描画モジュールの設定
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());
	// テクスチャ、モデル、カーブ、マテリアルローダーの設定する
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());
	m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
	m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
	// エフェクトのデータを読み込み
	for (int i = 0; i < MaxEffect; ++i)
	{
		m_effect[i] = Effekseer::Effect::Create(m_manager, EffectFileName[i]);
	}

	return S_OK;
}


/**
* @brief	終了処理
*/
void CEffectManager::Uninit()
{
	// Effekseer終了処理
	for (int i = 0; i < MaxEffect; ++i)
	{
		m_effect[i].Reset();
	}
	m_manager.Reset();
	m_renderer.Reset();
}


/**
* @brief	更新処理
*/
void CEffectManager::Update()
{
	CCamera* pCamera = CAMERA->Get();
	Vector3 cameraPos = pCamera->GetPos();
	Vector3 cameraLook = pCamera->GetLook();
	Vector3 cameraUp = pCamera->GetUp();
	Effekseer::Vector3D eye = ::Effekseer::Vector3D(cameraPos->x, cameraPos->y, cameraPos->z);
	Effekseer::Vector3D look = ::Effekseer::Vector3D(cameraLook->x, cameraLook->y, cameraLook->z);
	Effekseer::Vector3D up = ::Effekseer::Vector3D(cameraUp->x, cameraUp->y, cameraUp->z);
	// 投影行列を設定
	m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
		pCamera->GetFOV(), pCamera->GetAspect(), pCamera->GetNearClip(), pCamera->GetFarClip()));
	// カメラ行列を設定
	m_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(eye, look, up));
}


/**
* @brief	描画処理
*/
void CEffectManager::Draw()
{
	m_manager->Update();
	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();
}


/**
* @brief	再生
* @param	type	エフェクトタイプ
* @param	pos		エフェクト発生座標
*/
void CEffectManager::Play(EEffectType type, Vector3 pos)
{
	m_handle = m_manager->Play(m_effect[type], pos->x, pos->y, pos->z);
}


/**
* @brief	全てのエフェクトを止める
*/
void CEffectManager::StopAll()
{
	m_manager->StopAllEffects();
}