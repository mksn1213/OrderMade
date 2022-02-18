#pragma once
/**
*
* @file		CObject.h
* @brief	�S�ẴI�u�W�F�N�g�̊�{�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/09/29	�����J�n
*			2021/11/28	���N���X�̔�剻�ɑΉ����č\����啝�ɕύX
*
*/

/** �C���N���[�h�� */
#include <string>

/** �O��` */
class CItem;

/** �I�u�W�F�N�g�N���X */
template <class T>
class CObject
{
public:
	CObject() {}
	~CObject() {}

	// ���g�̔j��
	virtual void Destroy() {}
	
	/**
	* @brief	���O�擾
	* @return	std::string		���O
	*/
	std::string GetName() { return m_name; }

	/**
	* @brief	���O�Z�b�g
	* @return	name	�Z�b�g���閼�O
	*/
	void SetName(std::string name) { m_name = name; }

	// ���g��weak�|�C���^
	std::weak_ptr<T> m_self;

protected:
	// �I�u�W�F�N�g������
	virtual void OnCreate() {}
	// �I�u�W�F�N�g�j����
	virtual void OnDestroy() {}

private:
	// ���O
	std::string m_name;
};

