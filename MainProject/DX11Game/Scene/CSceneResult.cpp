/**
*
* @file		CSceneResult.cpp
* @brief	リザルトシーンクラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/11	実装開始
*
*/

/** インクルード部 */
#include <Scene/CSceneResult.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/GameObject/CGameObject.h>
#include <Scene/CSceneSelect.h>
#include <Scene/CSceneManager.h>
#include <System/Camera/CCameraManager.h>
#include <System/Sound/CSound.h>
#include <System/CInput.h>

// コンポーネント
#include <Component/Title/CButton.h>
#include <Component/Result/CResultScreen.h>
#include <System/Renderer/CSpriteRenderer.h>
#include <Component/Result/CResultScore.h>

/** マクロ定義 */
namespace
{
	// カメラ座標
	const XMFLOAT3 CAMERA_POS = XMFLOAT3(0.0f, 20.0f, -50.0f);
	// カメラ注視点
	const XMFLOAT3 CAMERA_TARGET_POS = XMFLOAT3(0.0f, 10.0f, 0.0f);
}

/**
* @brief	コンストラクタ
*/
CSceneResult::CSceneResult()
	: m_nScore(0)
{
	// シーンタイプセット
	SetSceneType(SceneResult);
}


/**
* @brief	デストラクタ
*/
CSceneResult::~CSceneResult()
{

}



/**
* @brief	初期化処理
*/
void CSceneResult::Init()
{
	// カメラ座標セット
	CAMERA->Get(0)->SetParameter(CAMERA_POS, CAMERA_TARGET_POS, Vector3::up());

	// リザルト画面作成
	const auto& screenObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	screenObj->AddComponent<CResultScreen>();

	// ボタン生成
	const auto& buttonObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3::down() * 200.0f).lock();
	buttonObj->AddComponent<CButton>();
	
	// スコア生成
	const auto& scoreObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& scoreCom = scoreObj->AddComponent<CResultScore>().lock();
	scoreCom->SetScore(m_nScore);

	// BGM再生
	SOUND_MANAGER->Play(BGM_RESULT);
}


/**
* @brief	終了処理
*/
void CSceneResult::Uninit()
{
	// BGM停止
	SOUND_MANAGER->Stop(BGM_RESULT);
}


/**
* @brief	更新処理
*/
void CSceneResult::Update()
{
	// ボタンプッシュでシーン遷移
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		const auto& scene = SCENE_MANAGER;
		// フェード中だったら終了
		if (scene->GetFadeState() != CFade::EFade::FADE_NONE)	return;

		// 次のシーンセット
		scene->SetNextScene<CSceneSelect>();
	}
}


/**
* @brief	描画処理
*/
void CSceneResult::Draw()
{
}