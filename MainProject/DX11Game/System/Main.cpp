/**
*
* @file		Main.cpp
* @brief	���C���֐�����
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
* @date		2022/01/15	�\���̕ύX
*
*/

/** �C���N���[�h�� */
#include <System/Main.h>
#include <System/Defines.h>
#include <System/DirectX.h>

#include <System/CInput.h>
#include <System/CDebugProc.h>
#include <System/Sound/CSound.h>
#include <System/CPolygon.h>
#include <System/Graphics/CGraphics.h>
#include <System/Resource/CModelManager.h>
#include <System/Resource/CTextureManager.h>
#include <System/Renderer/CMeshRenderer.h>
#include <Scene/CSceneManager.h>
#include <System/Graphics/ShaderList.h>
#include <System/Camera/CCameraManager.h>
#include <System/Light/CLightManager.h>
#include <System/Effect/CEffectManager.h>

#define ASSERT_FAILED(fn) do {\
hr = fn; \
if(FAILED(hr)) { \
	MessageBox(nullptr, "Init failed : "#fn, "Error", MB_OK); \
	return hr; \
}} while(0)

/**
* @brief	����������
*/
HRESULT Init(HWND hWnd)
{
	HRESULT hr = S_OK;
	// DirectX������
	ASSERT_FAILED(InitDX(hWnd, true));
	// ���͏�����
	ASSERT_FAILED(CInput::Init());
	// �T�E���h�Ǘ��쐬
	ASSERT_FAILED(CSoundManager::CreateInstance());
	// �f�o�b�O������
	ASSERT_FAILED(CDebugProc::Init());
	// �V�F�[�_�[������
	ASSERT_FAILED(InitShaderResource());
	// �J�����Ǘ��쐬
	ASSERT_FAILED(CCameraManager::CreateInstance());
	// ���C�g�Ǘ��쐬
	ASSERT_FAILED(CLightManager::CreateInstance());
	// �O���t�B�b�N�N���X����
	ASSERT_FAILED(CGraphics::CreateInstance());
	// �|���S���N���X�쐬
	ASSERT_FAILED(CPolygon::CreateInstance());
	// �G�t�F�N�g�Ǘ��쐬
	ASSERT_FAILED(CEffectManager::CreateInstance());
	// ���f���Ǘ��쐬
	ASSERT_FAILED(CModelManager::CreateInstance());
	// ���b�V��������
	ASSERT_FAILED(CMeshRenderer::InitMesh());
	// �e�N�X�`���Ǘ��쐬
	ASSERT_FAILED(CTextureManager::CreateInstance());
	// �V�[���Ǘ��쐬
	ASSERT_FAILED(CSceneManager::CreateInstance());
	return hr;
}


/**
* @brief	�I������
*/
void Uninit()
{
	// �V�[���Ǘ��폜
	CSceneManager::DestroyInstance();
	// �e�N�X�`���Ǘ��폜
	CTextureManager::DestroyInstance();
	// ���b�V���I��
	CMeshRenderer::UninitMesh();
	// ���f���Ǘ��폜
	CModelManager::DestroyInstance();
	// �G�t�F�N�g�Ǘ��폜
	CEffectManager::DestroyInstance();
	// �|���S���N���X�폜
	CPolygon::DestroyInstance();
	// �O���t�B�b�N�N���X�폜
	CGraphics::DestroyInstance();
	// ���C�g�Ǘ��폜
	CLightManager::DestroyInstance();
	// �J�����Ǘ��폜
	CCameraManager::DestroyInstance();
	// �V�F�[�_�[�I��
	UninitShaderResource();
	// �f�o�b�O�I��
	CDebugProc::Uninit();
	// �T�E���h�Ǘ��폜
	CSoundManager::DestroyInstance();
	// ���͏I��
	CInput::Uninit();
	// DirectX�I��
	UninitDX();
}


/**
* @brief	�X�V����
*/
void Update()
{
	// ���͏����X�V
	CInput::Update();
	// �f�o�b�O������
	CDebugProc::Start();
	//CDebugProc::Print("FPS:%d\n\n", GetFPSCount());
	// �J�����X�V
	CAMERA->Update();
	// ���C�g�X�V
	LIGHT->Update();
	// �V�[���X�V
	SCENE_MANAGER->Update();
	// �T�E���h�X�V
	SOUND_MANAGER->Update();
}


/**
* @brief	�`�揈��
*/
void Draw()
{
	// �����`��
	GRAPHICS->BeginDraw();
	// �V�[���`��
	SCENE_MANAGER->Draw();
	// �f�o�b�O�\��
	CDebugProc::Draw();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	GRAPHICS->EndDraw();
}
