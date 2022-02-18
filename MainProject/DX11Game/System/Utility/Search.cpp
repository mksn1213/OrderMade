/**
*
* @file		Search.cpp
* @brief	検索関数群実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/20	実装開始
*
*/

/** インクルード部 */
#include <System/Utility/Search.h>
#include <System/GameObject/CGameObject.h>

/**
* @brief	指定したタグを持ったゲームオブジェクトをリストから検索
* @param	list	検索するリスト
* @param	tag		検索するタグ
* @return	std::weak_ptr<CGameObject>		見つかったゲームオブジェクト
*/
std::weak_ptr<CGameObject> SearchExistsList(std::list<std::weak_ptr<CGameObject>> list, std::string tag)
{
	std::weak_ptr<CGameObject> obj;
	// リストから検索
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		// 指定したタグを持っているものを検索
		if (it->lock()->GetTag() == tag)
		{
			obj = it->lock();
			return obj;
		}
	}
	return obj;
}
