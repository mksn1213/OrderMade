
/**
*
* @file		CSceneTitle.cpp
* @brief	タイトルシーンクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
*
*/

/** インクルード部 */
#include <Scene/CSceneTitle.h>
#include <System/Factory/CStageFactory.h>
#include <System/GameObject/CGameObjectManager.h>
#include <Scene/CSceneManager.h>
#include <Scene/CSceneSelect.h>
#include <System/Camera/CCameraManager.h>
#include <System/Sound/CSound.h>
#include <System/CInput.h>

// コンポーネント
#include <Component/Game/Field/CField.h>
#include <Component/Title/CTitleTruck.h>
#include <Component/Title/CTitleFlower.h>
#include <Component/Title/CTitleLogo.h>
#include <Component/Title/CButton.h>
#include <Component/Title/COptionUI.h>

/** マクロ定義 */
namespace
{
	// カメラ座標
	const XMFLOAT3 CAMERA_POS		 = XMFLOAT3(-15.0f, 40.0f, -90.0f);
	// カメラ注視点
	const XMFLOAT3 CAMERA_TARGET_POS = XMFLOAT3(35.0f, 10.0f, 0.0f);
}

/**
* @brief	コンストラクタ
*/
CSceneTitle::CSceneTitle()
{
	// シーンタイプセット
	SetSceneType(SceneTitle);
}


/**
* @brief	デストラクタ
*/
CSceneTitle::~CSceneTitle()
{

}


/**
* @brief	初期化
*/
void CSceneTitle::Init()
{
	// カメラ座標セット
	CAMERA->Get(0)->SetParameter(CAMERA_POS, CAMERA_TARGET_POS, Vector3::up());

	// フィールド生成
	const auto& field = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	field->AddComponent<CField>();

	// ステージ生成
	CStageFactory::Init(m_eSceneType);

	// ゲートオブジェクト生成
	const auto& gateObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& renderer = gateObj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ShipGate);

	// トラックオブジェクト生成
	for (int i = 0; i < 3; ++i)
	{
		const auto& truckObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(-500.0f + 200.0f * i, 0.0f, 30.0f)).lock();
		truckObj->AddComponent<CTitleTruck>();
	}

	// 花オブジェクト生成
	const auto& flowerObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(0.0f, 0.0f, -20.0f)).lock();
	flowerObj->AddComponent<CTitleFlower>();

	// タイトルロゴ生成
	const auto& titleObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(300.0f, 200.0f, 0.0f)).lock();
	titleObj->AddComponent<CTitleLogo>();

	// タイトルボタン生成
	const auto& buttonObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(Vector3(440.0f, -250.0f, 0.0f)).lock();
	buttonObj->AddComponent<CButton>();

	// オプションUI生成
	//const auto& optionObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	//optionObj->AddComponent<COptionUI>();
	//optionObj->m_spTransform.lock()->SetPosition(Vector3(440.0f, -270.0f, 0.0f));

	// サウンド再生
	SOUND_MANAGER->Play(BGM_TITLE);
}


/**
* @brief	終了処理
*/
void CSceneTitle::Uninit()
{
	SOUND_MANAGER->Stop(BGM_TITLE);
}


/**
* @brief	更新処理
*/
void CSceneTitle::Update()
{	
	// ボタンプッシュでシーン遷移
	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		const auto& scene = SCENE_MANAGER;
		// フェード中だったら終了
		if (scene->GetFadeState() != CFade::EFade::FADE_NONE)	return;

		// SE再生
		SOUND_MANAGER->Play(SE_CLICK);

		// 次のシーンセット
		scene->SetNextScene<CSceneSelect>();
	}
}


/**
* @brief	描画処理
*/
void CSceneTitle::Draw()
{

}
