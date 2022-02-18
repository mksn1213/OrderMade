#pragma once
/**
*
* @file		CStageFactory.h
* @brief	ステージファクトリクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	実装開始
* @date		2021/12/08	csvファイルの読み込みを読み込み用の関数で行うように変更
*
*/

/** インクルード部 */
#include <System/Defines.h>
#include <string>
#include <System/Utility/Vector3.h>
#include <System/GameObject/ObjectIDData.h>
#include <Scene/CSceneBase.h>

/** 前定義 */
class CGameObject;

/** ステージファクトリクラス */
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