#pragma once
/**
*
* @file		Search.h
* @brief	�����֐��Q
* @author	SHONOSUKE MAKITA
* @date		2021/12/20	�����J�n
*
*/

/** �C���N���[�h�� */
#include <iostream>
#include <list>
#include <string>

class CGameObject;

std::weak_ptr<CGameObject> SearchExistsList(std::list<std::weak_ptr<CGameObject>> list, std::string tag);

