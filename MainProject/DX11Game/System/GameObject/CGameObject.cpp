/**
*
* @file		CGameObject.cpp
* @brief	ゲームオブジェクトクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/28	実装開始
*
*/

/** インクルード部 */
#include <System/GameObject/CGameObject.h>
#include <System/Component/CTransform.h>
#include <System/GameObject/CGameObjectManager.h>

/**
* @brief	コンストラクタ
*/
CGameObject::CGameObject()
	: m_tag("None")
	, m_isActive(true)
	, m_eObjectID(EObjectType::None)
{
	
}


/**
* @brief	デストラクタ
*/
CGameObject::~CGameObject()
{

}


/**
* @brief	初期化
*/
void CGameObject::Init()
{
	m_spGameObject = m_self.lock();

	// トランスフォーム作成
	m_spTransform = AddComponent<CTransform>();
	m_spTransform.lock()->SetGameObject(m_spGameObject);
}


/**
* @brief	終了処理
*/
void CGameObject::Uninit()
{

}


/**
* @brief	更新処理
*/
void CGameObject::Update()
{
	std::for_each(m_spComponentList.begin(),m_spComponentList.end(),
		[](std::weak_ptr<CComponent> com)
	{
		com.lock()->Update();
	});
}


/**
* @brief	自身の削除
* @param	selfObj		自身のゲームオブジェクト
*/
void CGameObject::Destroy()
{
	// 子オブジェクトが存在する場合子オブジェクトも削除
	while (m_spTransform.lock()->GetChildList().size() > 0)
	{
		auto childObj = m_spTransform.lock()->GetChildList().begin()->lock();
		childObj->Destroy();
	}
	
	// 自身の削除
	GAMEOBJECT_MANAGER->DestroyGameObject(m_self);
}