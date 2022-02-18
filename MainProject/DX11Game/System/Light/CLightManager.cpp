/**
*
* @file		CLightManager.cpp
* @brief	ライト管理クラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	実装開始
*
*/

/** インクルード */
#include <System/Light/CLightManager.h>

/**
* @brief	初期化処理
*/
HRESULT CLightManager::Init()
{
	HRESULT hr = S_OK;

	// メインライト生成
	m_nMainLightNo = Create<CLight>();
	// 有効化
	m_list.front()->Enable(true);

	// サブライト生成
	Create<CLight>();
	Get(1)->SetDirection(XMFLOAT3(-1.0f, -1.0f, -1.0f));
	return hr;
}


/**
* @brief	終了処理
*/
void CLightManager::Uninit()
{
	for (CLight* pLight : m_list)
	{
		delete pLight;
	}
}


/**
* @brief	更新処理
*/
void CLightManager::Update()
{
	for (CLight* pLight : m_list)
	{
		// 有効だった場合更新
		if (pLight->IsEnable())
		{
			pLight->Update();
		}
	}
}


/**
* @brief	ライト取得
* @param	nNo			ライト番号
* @return	CLight*		ライトオブジェクト
*/
CLight* CLightManager::Get(int nNo)
{
	// 現在有効なカメラ番号を設定
	if (nNo <= -1)	nNo = m_nMainLightNo;

	// 指定された番号が範囲内かどうか
	if (m_list.size() <= nNo)	return nullptr;

	// ライト取得
	LightList::iterator it = m_list.begin();
	while (nNo--)
	{
		++it;
	}
	return *it;
}