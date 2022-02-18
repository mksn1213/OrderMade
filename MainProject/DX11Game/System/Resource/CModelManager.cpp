/**
*
* @file		CModelManager.cpp
* @brief	モデル管理クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	実装開始
* @date		2022/01/15	シングルトン継承
*
*/

/** インクルード部 */
#include <System/Resource/CModelManager.h>
#include <System/Utility/CSVLoader.h>
#include <System/Graphics/CGraphics.h>
#include <System/Defines.h>

/**
* @brief	コンストラクタ
*/
CModelManager::CModelManager()
{

}


/**
* @brief	デストラクタ
*/
CModelManager::~CModelManager()
{

}


/**
* @brief	初期化処理
*/
HRESULT CModelManager::Init()
{
	HRESULT hr;
	// モデル読み込み
	hr = LoadModelAll();
	
	return hr;
}


/**
* @brief	終了処理
*/
void CModelManager::Uninit()
{
	// モデル解放
	ReleaseModelAll();
}


/**
* @brief	全モデル読み込み
* @return	HRESUL		読み込みの成否
*/
HRESULT CModelManager::LoadModelAll()
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// 全モデルのファイルパス読み込み
	std::vector<std::string> pathData = LoadStrDataFromCSV("data/csv/path/ModelPath.csv", 1, 1);

	// モデル読み込み
	HRESULT hr = S_OK;
	int max = static_cast<int>(EModelType::MaxModel);
	for (int i = 0; i < max; ++i)
	{
		//SAFE_DELETE(m_pModels[i]);
		m_pModels[i] = new CAssimpModel();
		if (!m_pModels[i]->Load(pDevice, pDC, pathData.at(i)))
		{
			hr = E_FAIL;
			break;
		}
	}
	return hr;
}


/**
* @brief	全モデル解放
*/
void CModelManager::ReleaseModelAll()
{
	// モデルの解放
	int max = static_cast<int>(EModelType::MaxModel);
	for (int i = 0; i < max; ++i)
	{
		if (m_pModels[i])
		{
			m_pModels[i]->Release();
			delete m_pModels[i];
			m_pModels[i] = nullptr;
		}
	}
}