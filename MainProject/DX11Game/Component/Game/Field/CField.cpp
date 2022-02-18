/**
*
* @file		CField.cpp
* @brief	�t�B�[���h�N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/15  �����J�n
* @date		2021/12/05	�R���|�[�l���g�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Field/CField.h>
#include <System/GameObject/CGameObject.h>
#include <System/Renderer/CMeshRenderer.h>

/**
* @brief	�R���X�g���N�^
*/
CField::CField()
{

}


/**
* @brief	�f�X�g���N�^
*/
CField::~CField()
{

}


/**
* @brief	������
*/
void CField::OnCreate()
{
	// �X�N���v�g������
	CScriptBase::OnCreate();

	// �����_���[�R���|�[�l���g�ǉ�
	const auto& renderer = m_spGameObject.lock()->AddComponent<CMeshRenderer>().lock();
	m_spTransform.lock()->SetScale(Vector3(400.0f, 1.0f, 400.0f));
	renderer->MakePlane(10.0f);
	renderer->SetBaseTexture(ETexture::Field);
}


/**
* @brief	�j����
*/
void CField::OnDestroy()
{
	CScriptBase::OnDestroy();
}

/**
* @brief	�X�V����
*/
void CField::Update()
{
}