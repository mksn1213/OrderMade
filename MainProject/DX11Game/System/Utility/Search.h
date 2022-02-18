#pragma once
/**
*
* @file		Search.h
* @brief	検索関数群
* @author	SHONOSUKE MAKITA
* @date		2021/12/20	実装開始
*
*/

/** インクルード部 */
#include <iostream>
#include <list>
#include <string>

class CGameObject;

std::weak_ptr<CGameObject> SearchExistsList(std::list<std::weak_ptr<CGameObject>> list, std::string tag);

