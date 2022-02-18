/**
*
* @file		CResultScore.cpp
* @brief	���U���g�X�R�A�N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/17	�����J�n
*
*/

/** �C���N���[�h�� */
#include <Component/Result/CResultScore.h>
#include <System/GameObject/CGameObject.h>

// �R���|�[�l���g
#include <System/Renderer/CSpriteRenderer.h>

/** �}�N����` */
namespace
{
	const float NUMBER_SPACE = 60.0f;	// �`��Ԋu
	const int	NUMBER_FRAME_X = 10;	// ���t���[����
	const int	NUMBER_FRAME_Y = 1;		// �c�t���[����
}

/**
* @brief	�R���X�g���N�^
*/
CResultScore::CResultScore()
{

}


/**
* @brief	�f�X�g���N�^
*/
CResultScore::~CResultScore()
{

}


/**
* @brief	������
*/
void CResultScore::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �^�O�ݒ�
	obj->SetTag("Sprite");
	// ���O�ݒ�
	obj->SetName("ResultScore");
	// �R���|�[�l���gID�ݒ�
	SetID(Script);
}


/**
* @brief	�j����
*/
void CResultScore::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	�X�V����
*/
void CResultScore::Update()
{

}


/**
* @brief	�X�R�A�Z�b�g
* @param	nScore	�X�R�A
*/
void CResultScore::SetScore(int nScore)
{
	const auto& obj = m_spGameObject.lock();

	// �X�v���C�g�ǉ�
	for (int i = 3; i >= 0; --i)
	{
		auto renderer = obj->AddComponent<CSpriteRenderer>().lock();
		renderer->SetTexture(ETexture::Game_Number);
		renderer->SetDrawSize(Vector3(60.0f, 90.0f, 1.0f));
		renderer->SetColor(Vector3::zero());
		renderer->SetTexSize(Vector3(1.0f / NUMBER_FRAME_X, 1.0f / NUMBER_FRAME_Y, 0.0f));
		renderer->SetLocalPos(Vector3(-NUMBER_SPACE * 1.5f + i * NUMBER_SPACE, 0.0f, 0.0f));
		unsigned n = nScore % 10;
		nScore /= 10;
		int u = n % NUMBER_FRAME_X;
		int v = n / NUMBER_FRAME_X;
		renderer->SetTexPos(Vector3(u / (float)NUMBER_FRAME_X, v / (float)NUMBER_FRAME_Y, 0.0f));
		m_spRenderer[i] = renderer;
	}
}