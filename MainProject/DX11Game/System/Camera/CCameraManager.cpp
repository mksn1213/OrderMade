/**
*
* @file		CCameraManager.cpp
* @brief	�J�����Ǘ��N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/01/21	�����J�n
*
*/

/** �C���N���[�h */
#include <System/Camera/CCameraManager.h>
#include <System/Camera/CCamera2D.h>
#include <System/Camera/CLightCamera.h>

/**
* @brief	����������
*/
HRESULT CCameraManager::Init()
{
	HRESULT hr = S_OK;

	// ���C���J�����쐬
	m_nMainCameraNo = Create<CCamera>();
	// �L����
	m_list.front()->Enable(true);

	// �V���h�E�}�b�v�p�J����
	Create<CCamera2D>();
	Create<CLightCamera>();

	return hr;
}


/**
* @brief	�I������
*/
void CCameraManager::Uninit()
{
	for (CCamera* pCamera : m_list)
	{
		delete pCamera;
	}
}


/**
* @brief	�X�V����
*/
void CCameraManager::Update()
{
	for (CCamera* pCamera : m_list)
	{
		// �L���������ꍇ�X�V
		if (pCamera->IsEnable())
		{
			pCamera->Update();
		}
	}
}


/**
* @brief	�J�����擾
* @param	nNo			�J�����ԍ�
* @return	CCamera*	�J�����I�u�W�F�N�g
*/
CCamera* CCameraManager::Get(int nNo)
{
	// ���ݗL���ȃJ�����ԍ���ݒ�
	if (nNo <= -1)	nNo = m_nMainCameraNo;

	// �w�肳�ꂽ�ԍ����͈͓����ǂ���
	if (m_list.size() <= nNo)	return nullptr;

	// �J�����擾
	CameraList::iterator it = m_list.begin();
	while (nNo--)
	{
		++it;
	}
	return *it;
}
