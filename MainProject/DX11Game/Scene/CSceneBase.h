#pragma once
/**
*
* @file		CSceneBase.h
* @brief	�V�[���x�[�X�N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
* @date		2021/12/03	
*
*/

/** �C���N���[�h�� */
#include <Scene/SceneTypeID.h>
#include <System/Systems/CSystemBase.h>
#include <vector>

/** �V�[���N���X */
class CSceneBase
{
public:
	CSceneBase();
	virtual ~CSceneBase();

	virtual void Init()		= 0;
	virtual void Uninit()	= 0;
	virtual void Update()	= 0;
	virtual void Draw()		= 0;

	/**
	* @brief	�V�[���^�C�v�Z�b�g
	* @param	type	�V�[���^�C�v
	*/
	void		SetSceneType(ESceneType type)	{ m_eSceneType = type; }
	
	/**
	* @brief	�V�[���^�C�v�擾
	* @return	ESceneType	�V�[���^�C�v
	*/
	ESceneType	GetSceneType()					{ return m_eSceneType; }

protected:
	// �V�[���^�C�v
	ESceneType	m_eSceneType;
};