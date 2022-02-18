/**
*
* @file		CSceneManager.cpp
* @brief	シーン管理クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
* @date		2021/12/03	構造の変更
* @date		2022/01/16	シングルトン継承
* @date		2022/01/29	コンポーネントをタイプ別で一括更新するように変更
*
*/

/** インクルード部 */
#include <Scene/CSceneManager.h>
#include <Scene/CSceneTitle.h>
#include <Scene/CSceneGame.h>
#include <Scene/CSceneSelect.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Systems/CScriptSystem.h>
#include <System/Systems/CRigidbodySystem.h>
#include <System/Systems/CCollisionSystem.h>
#include <System/Systems/CTransformSystem.h>
#include <System/Systems/CMeshRendererSystem.h>
#include <System/Systems/CModelRendererSystem.h>
#include <System/Systems/CSpriteRendererSystem.h>
#include <System/Renderer/CSpriteRenderer.h>
#include <System/Graphics/CGraphics.h>
#include <System/Effect/CEffectManager.h>

/**
* @brief	コンストラクタ
*/
CSceneManager::CSceneManager()
{

}


/**
* @brief	デストラクタ
*/
CSceneManager::~CSceneManager()
{

}


/**
* @brief	初期化処理
*/
HRESULT CSceneManager::Init()
{
	// 初期シーンの生成
	m_pCurrentScene = CreateScene<CSceneTitle>();
	//m_pCurrentScene = CreateScene<CSceneSelect>();
	//m_pCurrentScene = CreateScene<CSceneGame>();
	m_pNextScene = nullptr;

	// 変数初期化
	m_bIsStop = false;

	// ゲームオブジェクト管理作成
	CGameObjectManager::CreateInstance();

	// システムの追加
	AddSystem<CScriptSystem>(EComponentType::Script);
	AddSystem<CRigidbodySystem>(EComponentType::Rigidbody);
	AddSystem<CCollisionSystem>(EComponentType::Collider);
	AddSystem<CTransformSystem>(EComponentType::Transform);
	AddSystem<CModelRendererSystem>(EComponentType::ModelRenderer);
	AddSystem<CMeshRendererSystem>(EComponentType::MeshRenderer);
	AddSystem<CSpriteRendererSystem>(EComponentType::SpriteRenderer);

	// 初期シーンの生成時処理
	m_pCurrentScene->Init();

	// フェード生成
	const auto& obj = std::make_shared<CGameObject>();
	obj->m_self = obj;
	obj->Init();
	obj->AddComponent<CFade>();
	m_spFade = obj;

	// フェードオブジェクトは別で管理するため、コンポーネントシステムから削除
	CTransformSystem* pTransSystem = SCENE_MANAGER->GetSystem<CTransformSystem>(EComponentType::Transform);
	if (pTransSystem != nullptr)	pTransSystem->RemoveList("Fade");
	CScriptSystem* pScriptSystem = SCENE_MANAGER->GetSystem<CScriptSystem>(EComponentType::Script);
	if (pScriptSystem != nullptr)	pScriptSystem->RemoveList("Fade");
	CSpriteRendererSystem* pSpriteSystem = SCENE_MANAGER->GetSystem<CSpriteRendererSystem>(EComponentType::SpriteRenderer);
	if (pSpriteSystem != nullptr)	pSpriteSystem->RemoveList("Fade");

	// フェードオブジェクトを別で更新、描画するため、最初にコンポーネントを保持しておく
	m_spFadeScript = obj->GetComponent<CFade>();
	m_spFadeSprite = obj->GetComponent<CSpriteRenderer>();

	return S_OK;
}


/**
* @brief	終了処理
*/
void CSceneManager::Uninit()
{
	// フェード破棄
	m_spFade.reset();

	// 現在のシーン終了
	m_pCurrentScene->Uninit();

	// ゲームオブジェクトマネージャー終了
	CGameObjectManager::DestroyInstance();

	// システムリスト終了
	for (auto it = m_spSystemList.begin(); it != m_spSystemList.end();)
	{
		(*it)->OnDestroy();
		it = m_spSystemList.erase(it);
	}
}


/**
* @brief	更新処理
*/
void CSceneManager::Update()
{
	// 現在シーンの更新
	m_pCurrentScene->Update();

	// フラグが立っていれば更新なし
	if (!m_bIsStop)
	{
		// システムリストの更新
		for (auto system : m_spSystemList)
		{
			system->OnUpdate();
		}
	}

	// エフェクト管理更新
	EFFECT_MANAGER->Update();

	// フェード更新
	m_spFadeScript.lock()->Update();
}


/**
* @brief	描画処理
*/
void CSceneManager::Draw()
{
	// デバイスコンテキスト取得
	auto pDC = GetDeviceContext();

	// 現在シーン描画
	m_pCurrentScene->Draw();

	// システムリストの描画
	for (auto system : m_spSystemList)
	{
		system->OnDraw(pDC);
	}

	// エフェクト管理描画
	EFFECT_MANAGER->Draw();
	
	// フェード描画
	m_spFadeSprite.lock()->Draw(pDC);
}


/**
* @brief	次のシーンへ遷移
*/
void CSceneManager::SetSceneChange()
{
	// 全てのエフェクトを止める
	EFFECT_MANAGER->StopAll();

	// 現在のシーン終了
	m_pCurrentScene->Uninit();

	// ゲームオブジェクトマネージャー終了
	GAMEOBJECT_MANAGER->Uninit();

	// システムクリア
	for (auto system : m_spSystemList)
	{
		system->ListClear();
	}

	// 現在のシーン削除
	delete m_pCurrentScene;

	// シーンの切り替え
	m_pCurrentScene = m_pNextScene;
	m_pNextScene = nullptr;

	// ゲームオブジェクトマネージャー初期化
	GAMEOBJECT_MANAGER->Init();

	// 新しいシーンの初期化
	m_pCurrentScene->Init();

	// 変数の初期化
	m_bIsStop = false;
}
