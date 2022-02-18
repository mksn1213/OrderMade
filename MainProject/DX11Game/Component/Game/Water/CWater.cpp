/**
*
* @file		CWater.cpp
* @brief	���N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/09	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Water/CWater.h>
#include <System/GameObject/CGameObject.h>
#include <System/Renderer/CMeshRenderer.h>

/**
* @brief	�R���X�g���N�^
*/
CWater::CWater()
{

}


/**
* @brief	�f�X�g���N�^
*/
CWater::~CWater()
{

}


/**
* @brief	������
*/
void CWater::OnCreate()
{
	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �����_���[�R���|�[�l���g�ǉ�
	const auto& renderer = m_spGameObject.lock()->AddComponent<CMeshRenderer>().lock();
	renderer->MakePlane();
	renderer->SetBaseTexture(ETexture::Water);
}


/**
* @brief	�j����
*/
void CWater::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CWater::Update()
{
}
