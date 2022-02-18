#pragma once
/**
*
* @file		CStageFactory.h
* @brief	�X�e�[�W�t�@�N�g���N���X
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	�����J�n
* @date		2021/12/08	csv�t�@�C���̓ǂݍ��݂�ǂݍ��ݗp�̊֐��ōs���悤�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Defines.h>
#include <string>
#include <System/Utility/Vector3.h>
#include <System/GameObject/ObjectIDData.h>
#include <Scene/CSceneBase.h>

/** �O��` */
class CGameObject;

/** �X�e�[�W�t�@�N�g���N���X */
class CStageFactory
{
public:
	CStageFactory();
	~CStageFactory();

	static void Init(ESceneType scene, int nStageNo = 0);
	static void Uninit();
	static void CreateStage(const std::string& fileName);
	static std::weak_ptr<CGameObject> CreateGameObject(EObjectType type, Vector3 pos = Vector3::zero());
private:
};