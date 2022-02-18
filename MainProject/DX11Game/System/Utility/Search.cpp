/**
*
* @file		Search.cpp
* @brief	�����֐��Q����
* @author	SHONOSUKE MAKITA
* @date		2021/12/20	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Utility/Search.h>
#include <System/GameObject/CGameObject.h>

/**
* @brief	�w�肵���^�O���������Q�[���I�u�W�F�N�g�����X�g���猟��
* @param	list	�������郊�X�g
* @param	tag		��������^�O
* @return	std::weak_ptr<CGameObject>		���������Q�[���I�u�W�F�N�g
*/
std::weak_ptr<CGameObject> SearchExistsList(std::list<std::weak_ptr<CGameObject>> list, std::string tag)
{
	std::weak_ptr<CGameObject> obj;
	// ���X�g���猟��
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		// �w�肵���^�O�������Ă�����̂�����
		if (it->lock()->GetTag() == tag)
		{
			obj = it->lock();
			return obj;
		}
	}
	return obj;
}
