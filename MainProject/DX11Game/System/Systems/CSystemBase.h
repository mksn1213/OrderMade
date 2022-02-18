#pragma once
/**
*
* @file		CSystemBase.h
* @brief	�V�X�e���x�[�X�N���X
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	�����J�n
*
*/

/** �C���N���[�h�� */
#include <list>
#include <System/Component/ComponentIDData.h>
#include <d3d11.h>

/** �V�X�e���x�[�X�N���X */
class CSystemBase
{
public:
	CSystemBase();
	virtual ~CSystemBase();

	virtual void OnCreate() {}
	virtual void OnDestroy(){}
	virtual void OnUpdate() {}
	virtual void OnDraw(ID3D11DeviceContext* pDC)	{}
	virtual void ListClear() {}

	/**
	* @brief	�R���|�[�l���gID�Z�b�g
	* @param	typeID	�R���|�[�l���gID
	*/
	void SetTypeID(int typeID) { m_eComponentTypeID = typeID; }

	/**
	* @brief	�R���|�[�l���gID�擾
	* @return	int	�R���|�[�l���gID
	*/
	int GetTypeID() { return m_eComponentTypeID; }

private:
	int m_eComponentTypeID;
};