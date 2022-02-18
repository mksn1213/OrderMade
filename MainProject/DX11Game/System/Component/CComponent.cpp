/**
*
* @file		CComponent.cpp
* @brief	コンポーネントクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/28	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CComponent.h>

/**
* @brief	コンストラクタ
* @param	pObject		アタッチしているゲームオブジェクト
*/
CComponent::CComponent(std::weak_ptr<CGameObject> spObj)
	: m_spGameObject(spObj)
{

}


/**
* @brief	デストラクタ
*/
CComponent::~CComponent()
{

}
