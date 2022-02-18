#pragma once
/**
*
* @file		CModelManager.h
* @brief	モデル管理クラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	実装開始
* @date		2022/01/15	シングルトン継承
*
*/

/** インクルード部 */
#include <System/Renderer/AssimpModel.h>
#include <System/Resource/ModelTypeID.h>
#include <System/Utility/Singleton.h>

#define MODEL_MANAGER (CModelManager::GetInstance())

/** モデル管理クラス */
class CModelManager :public Singleton<CModelManager>
{
public:
	// TODO : 必要な時に各モデルを読み込むように変更する
	CModelManager();
	virtual ~CModelManager();

	HRESULT Init()		final;
	void	Uninit()	final;

	HRESULT LoadModelAll();
	void	ReleaseModelAll();

	/**
	* @brief	モデルの取得
	* @param	type			モデルタイプ
	* @return	CAssimpModel*	取得するモデル
	*/
	CAssimpModel* GetModel(EModelType type) { return m_pModels[static_cast<int>(type)]; }
	
	/**
	* @brief	生成済みのモデルにカメラ、ライトをセットする
	* @param	camera		セットするカメラ
	* @param	light		セットするライト
	*/
	// TODO : モデルを生成したときに一緒にセットできるように変更したい
	//void SetCameraLight(CCamera* camera, CLight* light)
	//{
	//	for (int i = 0; i < static_cast<int>(EModelType::MaxModel); ++i)
	//	{
	//		m_pModels[i]->SetCamera(camera);
	//		m_pModels[i]->SetLight(light);
	//	}
	//}

private:
	CAssimpModel* m_pModels[static_cast<int>(EModelType::MaxModel)];
};