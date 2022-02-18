/**
*
* @file		CLightManager.cpp
* @brief	���C�g�Ǘ��N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/22	�����J�n
*
*/

/** �C���N���[�h */
#include <System/Light/CLightManager.h>

/**
* @brief	����������
*/
HRESULT CLightManager::Init()
{
	HRESULT hr = S_OK;

	// ���C�����C�g����
	m_nMainLightNo = Create<CLight>();
	// �L����
	m_list.front()->Enable(true);

	// �T�u���C�g����
	Create<CLight>();
	Get(1)->SetDirection(XMFLOAT3(-1.0f, -1.0f, -1.0f));
	return hr;
}


/**
* @brief	�I������
*/
void CLightManager::Uninit()
{
	for (CLight* pLight : m_list)
	{
		delete pLight;
	}
}


/**
* @brief	�X�V����
*/
void CLightManager::Update()
{
	for (CLight* pLight : m_list)
	{
		// �L���������ꍇ�X�V
		if (pLight->IsEnable())
		{
			pLight->Update();
		}
	}
}


/**
* @brief	���C�g�擾
* @param	nNo			���C�g�ԍ�
* @return	CLight*		���C�g�I�u�W�F�N�g
*/
CLight* CLightManager::Get(int nNo)
{
	// ���ݗL���ȃJ�����ԍ���ݒ�
	if (nNo <= -1)	nNo = m_nMainLightNo;

	// �w�肳�ꂽ�ԍ����͈͓����ǂ���
	if (m_list.size() <= nNo)	return nullptr;

	// ���C�g�擾
	LightList::iterator it = m_list.begin();
	while (nNo--)
	{
		++it;
	}
	return *it;
}