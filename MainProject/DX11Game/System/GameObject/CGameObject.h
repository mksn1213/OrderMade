#pragma once
/**
*
* @file		CGameObject.h
* @brief	ゲームオブジェクトクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/28	実装開始
* @date		2021/12/04	スマートポインタで管理するように変更
*
*/

/** インクルード部 */
#include <System/Object/CObject.h>
#include <System/Component/CComponent.h>
#include <System/GameObject/ObjectIDData.h>
#include <System/Graphics/ShaderList.h>
#include <list>
#include <memory>
#include <algorithm>

#include <System/Component/CTransform.h>
#include <System/Component/CCollider.h>
#include <System/Component/CScriptBase.h>
#include <System/Renderer/CRenderer.h>
#include <System/Renderer/CModelRenderer.h>

/** ゲームオブジェクトクラス */
class CGameObject final : public CObject<CGameObject>
{
public:
	CGameObject();
	virtual ~CGameObject();

	void Init();
	void Uninit();
	void Update();

	/**
	* @brief	コンポーネントの追加
	* @return	std::weak_ptr<T>	追加したコンポーネント
	*/
	template <class T>
	std::weak_ptr<T> AddComponent()
	{
		// 生成
		std::shared_ptr<T> spComponent = std::make_shared<T>();
		// 自身を格納
		spComponent->m_self = spComponent;
		// アタッチしているゲームオブジェクトをセット
		spComponent->SetGameObject(m_spGameObject.lock());
		// リストに格納
		m_spComponentList.push_back(spComponent);
		// 生成時処理
		spComponent->OnCreate();
		
		return spComponent;
	}

	/**
	* @brief	コンポーネントの取得
	* @return	std::weak_ptr<T>	取得するコンポーネント
	*/
	template <class T>
	std::weak_ptr<T> GetComponent()
	{
		std::weak_ptr<T> comTemp;
		for (auto& com : m_spComponentList)
		{
			// コンポーネントIDで判定
			if (com->GetID() == T::comID)
			{
				comTemp = std::static_pointer_cast<T>(com);
				return comTemp;
			}
		}
		return comTemp.lock();
	}
	
	/**
	* @brief	コンポーネントの削除
	* @return	bool	削除の成否
	*/
	template <class T>
	bool RemoveComponent()
	{
		for (auto it = m_spComponentList.begin(); it != m_spComponentList.end(); ++it)
		{
			// コンポーネントIDで判定
			if ((*it)->GetID() == T::comID)
			{
				// コンポーネントの削除
				(*it)->OnDestroy();
				m_spComponentList.erase(it);
				return true;
			}
		}
		return false;
	}

	/**
	* @brief	所持しているコンポーネント全て削除
	*/
	void RemoveComponentAll()
	{
		for (auto it = m_spComponentList.begin(); it != m_spComponentList.end();)
		{
			// 削除時処理
			(*it)->OnDestroy();
			// リストから削除
			it = m_spComponentList.erase(it);
		}
	}

	/**
	* @brief	使用するシェーダータイプセット
	* @param	EVertexShaderKind	頂点シェーダー
	* @param	EPixelShaderKind	ピクセルシェーダー
	*/
	void SetShader(EVertexShaderKind vertex, EPixelShaderKind pixel)
	{
		m_eVertexShader = vertex;
		m_ePixelShader = pixel;
	}

	/**
	* @brief	現在のシェーダータイプを一時保存
	*/
	void SaveShaderKind()
	{
		m_eVSKindBuffer = m_eVertexShader;
		m_ePSKindBuffer = m_ePixelShader;
	}

	/**
	* @brief	使用する頂点シェーダー取得
	* @return	EVertexShaderKind	頂点シェーダーのタイプ
	*/
	EVertexShaderKind GetVSKind() { return m_eVertexShader; }

	/**
	* @brief	使用するピクセルシェーダー取得
	* @return	EPixelShaderKind	ピクセルシェーダーのタイプ
	*/
	EPixelShaderKind GetPSKind() { return m_ePixelShader; }

	/**
	* @brief	使用する頂点シェーダー取得
	* @return	EVertexShaderKind	頂点シェーダーのタイプ
	*/
	EVertexShaderKind GetVSKindBuffer() { return m_eVSKindBuffer; }

	/**
	* @brief	使用するピクセルシェーダー取得
	* @return	EPixelShaderKind	ピクセルシェーダーのタイプ
	*/
	EPixelShaderKind GetPSKindBuffer() { return m_ePSKindBuffer; }

	/**
	* @brief	アクティブセット
	* @param	active		true/アクティブ化 , false/非アクティブ化
	*/
	void SetActive(bool active) { m_isActive = active; }

	/**
	* @brief	アクティブ状態かどうか
	* @return	true/アクティブ , false/非アクティブ
	*/
	bool IsActive() { return m_isActive; }

	/**
	* @brief	タグセット
	* @param	tag		タグ名
	*/
	void SetTag(std::string tag) { m_tag = tag; }
	
	/**
	* @brief	タグ取得
	* @return	std::string		タグ名
	*/
	const std::string& GetTag() { return m_tag; }

	/**
	* @brief	オブジェクトIDセット
	* @param	type	オブジェクトIDタイプ
	*/
	void SetObjectID(EObjectType type) { m_eObjectID = type; }
	
	/**
	* @brief	オブジェクトID取得
	* @return	EObjectType		オブジェクトID
	*/
	const EObjectType& GetObjectID() { return m_eObjectID; }

	void Destroy();

	std::weak_ptr<CTransform>		m_spTransform;
private:
	std::weak_ptr<CGameObject>		m_spGameObject;
	std::string						m_tag;
	bool							m_isActive;
	EObjectType						m_eObjectID;

	// シェーダタイプ
	EVertexShaderKind				m_eVertexShader;
	EPixelShaderKind				m_ePixelShader;
	// シェーダータイプ一時保存用
	EVertexShaderKind				m_eVSKindBuffer;
	EPixelShaderKind				m_ePSKindBuffer;

	// コンポーネントリスト
	std::list<std::shared_ptr<CComponent>>	m_spComponentList;
};

