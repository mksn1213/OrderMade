#pragma once
/**
*
* @file		CCamera.h
* @brief	�J�����N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	�����J�n
* @date		2022/01/21	�J�����}�l�[�W���[���쐬
*
*/

/** �C���N���[�h */
#include <System/Defines.h>
#include <System/Utility/Vector3.h>
#include <memory>

/** �O��` */
class CTransform;

/** �J�����N���X */
class CCamera
{
public:
	CCamera();
	virtual ~CCamera();

	virtual void Update();

protected:
	virtual XMMATRIX CalcProjection();

public:
	CCamera& operator=(const CCamera& camera)
	{
		m_pos	= camera.m_pos;
		m_look	= camera.m_look;
		m_up	= camera.m_up;
		m_screenSize	= camera.m_screenSize;
		m_fNearClip		= camera.m_fNearClip;
		m_fFarClip		= camera.m_fFarClip;
		m_fFov			= camera.m_fFov;
		return *this;
	}

	/**
	* @brief	���_�擾
	* @return	Vector3	�J�������_
	*/
	const Vector3& GetPos() const { return m_pos; }

	/**
	* @brief	�����_�擾
	* @return	Vector3	�J���������_
	*/
	const Vector3& GetLook() const { return m_look; }

	/**
	* @brief	����x�N�g���擾
	* @return	Vector3	�J��������x�N�g��
	*/
	const Vector3& GetUp() const { return m_up; }

	/**
	* @brief	�X�N���[���T�C�Y�擾
	* @return	XMFLOAT2	�X�N���[���T�C�Y
	*/
	const XMFLOAT2& GetScreenSize() const { return m_screenSize; }

	/**
	* @brief	�c����擾
	* @return	float	�c����
	*/
	float GetAspect()	const { return m_screenSize.x / m_screenSize.y; }
	
	/**
	* @brief	�O���N���b�v�����擾
	* @return	float	�O���N���b�v����
	*/
	float GetNearClip() const { return m_fNearClip; }

	/**
	* @brief	����N���b�v�����擾
	* @return	float	����N���b�v����
	*/
	float GetFarClip()	const { return m_fFarClip; }

	/**
	* @brief	����p�擾
	* @return	float	����p
	*/
	float GetFOV()		const { return m_fFov; }

	/**
	* @brief	�r���[�s��擾
	* @return	XMFLOAT4X4	�r���[�s��
	*/
	const XMFLOAT4X4& GetLookAt() const { return m_lookAt; }
	
	/**
	* @brief	�v���W�F�N�V�����s��擾
	* @return	XMFLOAT4X4	�v���W�F�N�V�����s��
	*/
	const XMFLOAT4X4& GetProjection() const { return m_projection; }
	
	
	/**
	* @brief	�r���[�s��擾(�v�Z�p)
	* @return	XMMATRIX	�r���[�s��
	*/
	const XMMATRIX& GetLookAtMatrix() const { return m_lookAtMatrix; }
	
	/**
	* @brief	�v���W�F�N�V�����s��擾(�v�Z�p)
	* @return	XMMATRIX	�v���W�F�N�V�����s��
	*/
	const XMMATRIX& GetProjectionMatrix() const { return m_projectionMatrix; }

	/**
	* @brief	�p�����[�^�Z�b�g
	* @param	pos		���_
	* @param	look	�����_
	* @param	up		����x�N�g��
	*/
	void SetParameter(Vector3 pos, Vector3 look, Vector3 up)
	{
		m_pos  = pos;
		m_look = look;
		m_up   = up;
	}

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
	* @brief	�Ώۂ�ǂ������邩
	* @param	chase	true/�ǂ������� , false/�ǂ������Ȃ�
	*/
	void Chase(bool chase) { m_bChase = chase; }

	/**
	* @brief	�ǂ�������^�[�Q�b�g�̃Z�b�g
	* @param	trans	�^�[�Q�b�g�̃g�����X�t�H�[��
	*/
	void SetChaseTarget(std::weak_ptr<CTransform> trans) { m_spTargetTrans = trans; }

	Vector3 CalcScreenPos(Vector3 worldPos);
	Vector3 CalcWorldPos(Vector3 screenPos);

private:
	bool		m_bIsEnable;
	XMFLOAT4X4	m_lookAt;
	XMFLOAT4X4	m_projection;
	XMMATRIX	m_lookAtMatrix;
	XMMATRIX	m_projectionMatrix;
	bool		m_bChase;
	std::weak_ptr<CTransform> m_spTargetTrans;
	
protected:
	Vector3		m_pos;
	Vector3		m_look;
	Vector3		m_up;
	XMFLOAT2	m_screenSize;
	float		m_fNearClip;
	float		m_fFarClip;
	float		m_fFov;
};
