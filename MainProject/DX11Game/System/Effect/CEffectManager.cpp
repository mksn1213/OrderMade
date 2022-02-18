/**
*
* @file		CEffectManager.cpp
* @brief	�G�t�F�N�g�Ǘ��N���X����
* @author	SHONOSUKE MAKITA
* @date		2022/02/08	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Effect/CEffectManager.h>
#include <System/CInput.h>
#include <System/Camera/CCameraManager.h>

/** �}�N����` */
namespace
{
	// �G�t�F�N�g�t�@�C����
	const char16_t* EffectFileName[MaxEffect] =
	{
		u"data/Effect/Smoke.efk",
		u"data/Effect/PlantSmoke.efk",
		u"data/Effect/OvenSmoke.efk",
		u"data/Effect/Fire.efk",
		u"data/Effect/Grow.efk",
		u"data/Effect/GrowAction.efk",
		u"data/Effect/Ship.efk",
		u"data/Effect/Water.efk"
	};
}

/**
* @brief	�R���X�g���N�^
*/
CEffectManager::CEffectManager()
{

}


/**
* @brief	�f�X�g���N�^
*/
CEffectManager::~CEffectManager()
{

}


/**
* @brief	����������
*/
HRESULT CEffectManager::Init()
{
	// Effekseer������
	m_renderer = EffekseerRendererDX11::Renderer::Create(GetDevice(), GetDeviceContext(), 8000);
	m_manager = Effekseer::Manager::Create(8000);
	// �`�惂�W���[���̐ݒ�
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());
	// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());
	m_manager->SetMaterialLoader(m_renderer->CreateMaterialLoader());
	m_manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
	// �G�t�F�N�g�̃f�[�^��ǂݍ���
	for (int i = 0; i < MaxEffect; ++i)
	{
		m_effect[i] = Effekseer::Effect::Create(m_manager, EffectFileName[i]);
	}

	return S_OK;
}


/**
* @brief	�I������
*/
void CEffectManager::Uninit()
{
	// Effekseer�I������
	for (int i = 0; i < MaxEffect; ++i)
	{
		m_effect[i].Reset();
	}
	m_manager.Reset();
	m_renderer.Reset();
}


/**
* @brief	�X�V����
*/
void CEffectManager::Update()
{
	CCamera* pCamera = CAMERA->Get();
	Vector3 cameraPos = pCamera->GetPos();
	Vector3 cameraLook = pCamera->GetLook();
	Vector3 cameraUp = pCamera->GetUp();
	Effekseer::Vector3D eye = ::Effekseer::Vector3D(cameraPos->x, cameraPos->y, cameraPos->z);
	Effekseer::Vector3D look = ::Effekseer::Vector3D(cameraLook->x, cameraLook->y, cameraLook->z);
	Effekseer::Vector3D up = ::Effekseer::Vector3D(cameraUp->x, cameraUp->y, cameraUp->z);
	// ���e�s���ݒ�
	m_renderer->SetProjectionMatrix(::Effekseer::Matrix44().PerspectiveFovLH(
		pCamera->GetFOV(), pCamera->GetAspect(), pCamera->GetNearClip(), pCamera->GetFarClip()));
	// �J�����s���ݒ�
	m_renderer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(eye, look, up));
}


/**
* @brief	�`�揈��
*/
void CEffectManager::Draw()
{
	m_manager->Update();
	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();
}


/**
* @brief	�Đ�
* @param	type	�G�t�F�N�g�^�C�v
* @param	pos		�G�t�F�N�g�������W
*/
void CEffectManager::Play(EEffectType type, Vector3 pos)
{
	m_handle = m_manager->Play(m_effect[type], pos->x, pos->y, pos->z);
}


/**
* @brief	�S�ẴG�t�F�N�g���~�߂�
*/
void CEffectManager::StopAll()
{
	m_manager->StopAllEffects();
}