#pragma once
/**
*
* @file		CLight.h
* @brief	���C�g�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	�����J�n
* @date		2022/01/21	���C�g�}�l�[�W���[���쐬
*
*/

/** �C���N���[�h */
#include <System/Defines.h>

/** ���C�g�N���X */
class CLight
{
public:
	CLight();
	virtual ~CLight();

	virtual void Update();

	/**
	* @brief	�f�B�t���[�Y�擾
	* @return	XMFLOAT4	�f�B�t���[�Y
	*/
	const XMFLOAT4& GetDiffuse() const { return m_diffuse; }

	/**
	* @brief	�A���r�G���g�擾
	* @return	XMFLOAT4	�A���r�G���g
	*/
	const XMFLOAT4& GetAmbient() const { return m_ambient; }

	/**
	* @brief	�X�y�L�����擾
	* @return	XMFLOAT4	�X�y�L����
	*/
	const XMFLOAT4& GetSpecular() const { return m_specular; }


	/**
	* @brief	�����擾
	* @return	XMFLOAT3	����
	*/
	const XMFLOAT3& GetDirection() const { return m_direction; }

	/**
	* @brief	�L��ON/OFF
	* @param	enable	�L��/����(true/�L�� false/����)
	*/
	void Enable(bool enable) { m_bIsEnable = enable; }

	/**
	* @brief	�L�����ǂ���
	* @return	bool	�L��/����(true/�L�� false/����)
	*/
	bool IsEnable() const { return m_bIsEnable; }

	/**
	* @brief	�����Z�b�g
	* @param	XMFLOAT3	����
	*/
	void SetDirection(XMFLOAT3 direction) 
	{ 
		XMStoreFloat3(&m_direction, XMVector3Normalize(XMLoadFloat3(&direction)));
	}

private:
	XMFLOAT4 m_diffuse;
	XMFLOAT4 m_ambient;
	XMFLOAT4 m_specular;
	XMFLOAT3 m_direction;
	bool	 m_bIsEnable;
};