/**
*
* @file		Main.cpp
* @brief	メイン関数実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
* @date		2022/01/15	構成の変更
*
*/

/** インクルード部 */
#include <System/Main.h>
#include <System/Defines.h>
#include <System/DirectX.h>

#include <System/CInput.h>
#include <System/CDebugProc.h>
#include <System/Sound/CSound.h>
#include <System/CPolygon.h>
#include <System/Graphics/CGraphics.h>
#include <System/Resource/CModelManager.h>
#include <System/Resource/CTextureManager.h>
#include <System/Renderer/CMeshRenderer.h>
#include <Scene/CSceneManager.h>
#include <System/Graphics/ShaderList.h>
#include <System/Camera/CCameraManager.h>
#include <System/Light/CLightManager.h>
#include <System/Effect/CEffectManager.h>

#define ASSERT_FAILED(fn) do {\
hr = fn; \
if(FAILED(hr)) { \
	MessageBox(nullptr, "Init failed : "#fn, "Error", MB_OK); \
	return hr; \
}} while(0)

/**
* @brief	初期化処理
*/
HRESULT Init(HWND hWnd)
{
	HRESULT hr = S_OK;
	// DirectX初期化
	ASSERT_FAILED(InitDX(hWnd, true));
	// 入力初期化
	ASSERT_FAILED(CInput::Init());
	// サウンド管理作成
	ASSERT_FAILED(CSoundManager::CreateInstance());
	// デバッグ初期化
	ASSERT_FAILED(CDebugProc::Init());
	// シェーダー初期化
	ASSERT_FAILED(InitShaderResource());
	// カメラ管理作成
	ASSERT_FAILED(CCameraManager::CreateInstance());
	// ライト管理作成
	ASSERT_FAILED(CLightManager::CreateInstance());
	// グラフィッククラス生成
	ASSERT_FAILED(CGraphics::CreateInstance());
	// ポリゴンクラス作成
	ASSERT_FAILED(CPolygon::CreateInstance());
	// エフェクト管理作成
	ASSERT_FAILED(CEffectManager::CreateInstance());
	// モデル管理作成
	ASSERT_FAILED(CModelManager::CreateInstance());
	// メッシュ初期化
	ASSERT_FAILED(CMeshRenderer::InitMesh());
	// テクスチャ管理作成
	ASSERT_FAILED(CTextureManager::CreateInstance());
	// シーン管理作成
	ASSERT_FAILED(CSceneManager::CreateInstance());
	return hr;
}


/**
* @brief	終了処理
*/
void Uninit()
{
	// シーン管理削除
	CSceneManager::DestroyInstance();
	// テクスチャ管理削除
	CTextureManager::DestroyInstance();
	// メッシュ終了
	CMeshRenderer::UninitMesh();
	// モデル管理削除
	CModelManager::DestroyInstance();
	// エフェクト管理削除
	CEffectManager::DestroyInstance();
	// ポリゴンクラス削除
	CPolygon::DestroyInstance();
	// グラフィッククラス削除
	CGraphics::DestroyInstance();
	// ライト管理削除
	CLightManager::DestroyInstance();
	// カメラ管理削除
	CCameraManager::DestroyInstance();
	// シェーダー終了
	UninitShaderResource();
	// デバッグ終了
	CDebugProc::Uninit();
	// サウンド管理削除
	CSoundManager::DestroyInstance();
	// 入力終了
	CInput::Uninit();
	// DirectX終了
	UninitDX();
}


/**
* @brief	更新処理
*/
void Update()
{
	// 入力処理更新
	CInput::Update();
	// デバッグ文字列
	CDebugProc::Start();
	//CDebugProc::Print("FPS:%d\n\n", GetFPSCount());
	// カメラ更新
	CAMERA->Update();
	// ライト更新
	LIGHT->Update();
	// シーン更新
	SCENE_MANAGER->Update();
	// サウンド更新
	SOUND_MANAGER->Update();
}


/**
* @brief	描画処理
*/
void Draw()
{
	// 初期描画
	GRAPHICS->BeginDraw();
	// シーン描画
	SCENE_MANAGER->Draw();
	// デバッグ表示
	CDebugProc::Draw();
	// バックバッファとフロントバッファの入れ替え
	GRAPHICS->EndDraw();
}
