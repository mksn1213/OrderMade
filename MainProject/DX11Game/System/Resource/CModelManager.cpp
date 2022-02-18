/**
*
* @file		CModelManager.cpp
* @brief	���f���Ǘ��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	�����J�n
* @date		2022/01/15	�V���O���g���p��
*
*/

/** �C���N���[�h�� */
#include <System/Resource/CModelManager.h>
#include <System/Utility/CSVLoader.h>
#include <System/Graphics/CGraphics.h>
#include <System/Defines.h>

/**
* @brief	�R���X�g���N�^
*/
CModelManager::CModelManager()
{

}


/**
* @brief	�f�X�g���N�^
*/
CModelManager::~CModelManager()
{

}


/**
* @brief	����������
*/
HRESULT CModelManager::Init()
{
	HRESULT hr;
	// ���f���ǂݍ���
	hr = LoadModelAll();
	
	return hr;
}


/**
* @brief	�I������
*/
void CModelManager::Uninit()
{
	// ���f�����
	ReleaseModelAll();
}


/**
* @brief	�S���f���ǂݍ���
* @return	HRESUL		�ǂݍ��݂̐���
*/
HRESULT CModelManager::LoadModelAll()
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDC = GetDeviceContext();

	// �S���f���̃t�@�C���p�X�ǂݍ���
	std::vector<std::string> pathData = LoadStrDataFromCSV("data/csv/path/ModelPath.csv", 1, 1);

	// ���f���ǂݍ���
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
* @brief	�S���f�����
*/
void CModelManager::ReleaseModelAll()
{
	// ���f���̉��
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