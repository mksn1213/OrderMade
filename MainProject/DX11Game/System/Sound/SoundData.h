#pragma once
/**
*
* @file		SoundData.h
* @brief	�T�E���h�f�[�^
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	�����J�n
*
*/

/**
* @enum		EBGM
* @brief	BGM�^�C�v
*/
enum EBGM
{
	BGM_TITLE = 0,	// �^�C�g��
	BGM_SELECT,		// �Z���N�g
	BGM_GAME,		// �Q�[��
	BGM_RESULT,		// ���U���g

	MAX_BGM
};

/**
* @enum		ESE
* @brief	SE�^�C�v
*/
enum ESE
{
	SE_BAKE,		// �Ă���
	SE_CAR,			// ��
	SE_CLICK,		// �N���b�N
	SE_CURSOR,		// �J�[�\��
	SE_FERTILIZER,	// �엿
	SE_GAME_FINISH,	// �Q�[���I��
	SE_GAME_START,	// �Q�[���X�^�[�g
	SE_GROW,		// ����
	SE_ORDER_BREAK,	// �����j��	
	SE_ORDER_IN,	// ����
	SE_PLANT,		// ���A����
	SE_PAUSE,		// �|�[�Y
	SE_PUT,			// �u��
	SE_GIVEWATER,	// �����
	SE_SHIP,		// �o��
	SE_TAKE,		// ����
	SE_TRIM,		// ���`
	SE_WALK,		// ����
	SE_WELL_IN,		// ��˓���
	SE_WELL_OUT,	// ��ˏo��
	SE_WELL_PULLEY,	// ��ˊ���

	MAX_SE
};