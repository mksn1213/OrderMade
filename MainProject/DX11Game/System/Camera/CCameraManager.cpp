/**
*
* @file		CCameraManager.cpp
* @brief	カメラ管理クラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/21	実装開始
*
*/

/** インクルード */
#include <System/Camera/CCameraManager.h>
#include <System/Camera/CCamera2D.h>
#include <System/Camera/CLightCamera.h>

/**
* @brief	初期化処理
*/
HRESULT CCameraManager::Init()
{
	HRESULT hr = S_OK;

	// メインカメラ作成
	m_nMainCameraNo = Create<CCamera>();
	// 有効化
	m_list.front()->Enable(true);

	// シャドウマップ用カメラ
	Create<CCamera2D>();
	Create<CLightCamera>();

	return hr;
}


/**
* @brief	終了処理
*/
void CCameraManager::Uninit()
{
	for (CCamera* pCamera : m_list)
	{
		delete pCamera;
	}
}


/**
* @brief	更新処理
*/
void CCameraManager::Update()
{
	for (CCamera* pCamera : m_list)
	{
		// 有効だった場合更新
		if (pCamera->IsEnable())
		{
			pCamera->Update();
		}
	}
}


/**
* @brief	カメラ取得
* @param	nNo			カメラ番号
* @return	CCamera*	カメラオブジェクト
*/
CCamera* CCameraManager::Get(int nNo)
{
	// 現在有効なカメラ番号を設定
	if (nNo <= -1)	nNo = m_nMainCameraNo;

	// 指定された番号が範囲内かどうか
	if (m_list.size() <= nNo)	return nullptr;

	// カメラ取得
	CameraList::iterator it = m_list.begin();
	while (nNo--)
	{
		++it;
	}
	return *it;
}
