#pragma once
/**
*
* @file		CSceneManager.h
* @brief	シーン管理クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
* @date		2021/12/03	テンプレート構造に変更
* @date		2022/01/16	シングルトン継承
* @date		2022/01/29	コンポーネントをタイプ別で一括更新するように変更
*
*/

/** インクルード部 */
#include <System/Utility/Singleton.h>
#include <Scene/CSceneBase.h>
#include <iostream>
#include <vector>

#include <System/Systems/CSystemBase.h>
#include <System/CFade.h>
#include <System/GameObject/CGameObject.h>

#define SCENE_MANAGER (CSceneManager::GetInstance())

/** シーン管理クラス */
class CSceneManager final : public Singleton<CSceneManager>
{
public:
	CSceneManager();
	virtual ~CSceneManager();

	HRESULT Init()		override;
	void	Uninit()	override;
	void	Update();
	void	Draw();
	
	/**
	* @brief	シーン生成
	* @return	T*		生成したシーン
	*/
	template <class T>
	T* CreateScene()
	{
		// インスタンス化
		T* pScene = new T;
		return pScene;
	}

	/**
	* @brief	次のシーンをセット
	* @detail	シーン生成後シーン遷移開始
	*/
	template <class T>
	T* SetNextScene()
	{
		// 次のシーンが既にセットされている場合終了
		if (m_pNextScene != nullptr) return nullptr;
		// 次のシーン生成
		auto pNextScene = CreateScene<T>();
		m_pNextScene = pNextScene;
		// フェードアウト開始
		m_spFade->GetComponent<CFade>().lock()->StartFadeOut();

		return pNextScene;
	}

	/**
	* @brief	現在のシーン取得
	* @return	CSceneBase*		現在のシーン
	*/
	CSceneBase* GetScene() { return m_pCurrentScene; }

	/**
	* @brief	フェードの状態取得
	* @return	EFade	フェード状態
	*/
	CFade::EFade GetFadeState() { return m_spFadeScript.lock()->GetFadeState(); }

	/**
	* @brief	システム更新のON/OFF
	* @param	bON		true/ON , false/OFF
	*/
	void SystemStop(bool bON) { m_bIsStop = bON; }

	/**
	* @brief	フェードスクリプト取得
	* @return	std::weak_ptr<CFade>	フェードスクリプト
	*/
	std::weak_ptr<CFade> GetFadeScript() { return m_spFadeScript; }

	void SetSceneChange();

	// システムの追加
	template <class T>
	void AddSystem(EComponentType typeID);
	// システムの取得
	template <class T>
	T* GetSystem(EComponentType typeID);

private:
	// 現在のシーン
	CSceneBase*						m_pCurrentScene;
	// 次のシーン
	CSceneBase*						m_pNextScene;
	// 更新のON/OFF
	bool							m_bIsStop;
	// フェードオブジェクト
	std::shared_ptr<CGameObject>	m_spFade;
	// フェードスクリプト
	std::weak_ptr<CFade>			m_spFadeScript;
	// フェードスプライト
	std::weak_ptr<CSpriteRenderer>	m_spFadeSprite;
	// システムリスト
	std::vector<std::shared_ptr<CSystemBase>>	m_spSystemList;
};

/**
* @brief	システムの追加
* @param	typeID	コンポーネントID
*/
template <class T>
void CSceneManager::AddSystem(EComponentType typeID)
{
	// 生成
	std::shared_ptr<T> spSystem = std::make_shared<T>();
	// システムIDのセット
	spSystem->SetTypeID(typeID);
	// リストに追加
	m_spSystemList.push_back(spSystem);
	// 生成時処理
	spSystem->OnCreate();
}

/**
* @brief	システムの取得
* @param	typeID	コンポーネントID
* @return	T*	システム
*/
template <class T>
T* CSceneManager::GetSystem(EComponentType typeID)
{
	for (auto system : m_spSystemList)
	{
		// コンポーネントIDを判定
		if (system->GetTypeID() == typeID)
		{
			T* buffer = static_cast<T*>(system.get());
			return buffer;
		}
	}
	return nullptr;
}