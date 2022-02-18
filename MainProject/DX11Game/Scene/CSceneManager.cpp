/**
*
* @file		CSceneManager.cpp
* @brief	�V�[���Ǘ��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	�����J�n
* @date		2021/12/03	�\���̕ύX
* @date		2022/01/16	�V���O���g���p��
* @date		2022/01/29	�R���|�[�l���g���^�C�v�ʂňꊇ�X�V����悤�ɕύX
*
*/

/** �C���N���[�h�� */
#include <Scene/CSceneManager.h>
#include <Scene/CSceneTitle.h>
#include <Scene/CSceneGame.h>
#include <Scene/CSceneSelect.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Systems/CScriptSystem.h>
#include <System/Systems/CRigidbodySystem.h>
#include <System/Systems/CCollisionSystem.h>
#include <System/Systems/CTransformSystem.h>
#include <System/Systems/CMeshRendererSystem.h>
#include <System/Systems/CModelRendererSystem.h>
#include <System/Systems/CSpriteRendererSystem.h>
#include <System/Renderer/CSpriteRenderer.h>
#include <System/Graphics/CGraphics.h>
#include <System/Effect/CEffectManager.h>

/**
* @brief	�R���X�g���N�^
*/
CSceneManager::CSceneManager()
{

}


/**
* @brief	�f�X�g���N�^
*/
CSceneManager::~CSceneManager()
{

}


/**
* @brief	����������
*/
HRESULT CSceneManager::Init()
{
	// �����V�[���̐���
	m_pCurrentScene = CreateScene<CSceneTitle>();
	//m_pCurrentScene = CreateScene<CSceneSelect>();
	//m_pCurrentScene = CreateScene<CSceneGame>();
	m_pNextScene = nullptr;

	// �ϐ�������
	m_bIsStop = false;

	// �Q�[���I�u�W�F�N�g�Ǘ��쐬
	CGameObjectManager::CreateInstance();

	// �V�X�e���̒ǉ�
	AddSystem<CScriptSystem>(EComponentType::Script);
	AddSystem<CRigidbodySystem>(EComponentType::Rigidbody);
	AddSystem<CCollisionSystem>(EComponentType::Collider);
	AddSystem<CTransformSystem>(EComponentType::Transform);
	AddSystem<CModelRendererSystem>(EComponentType::ModelRenderer);
	AddSystem<CMeshRendererSystem>(EComponentType::MeshRenderer);
	AddSystem<CSpriteRendererSystem>(EComponentType::SpriteRenderer);

	// �����V�[���̐���������
	m_pCurrentScene->Init();

	// �t�F�[�h����
	const auto& obj = std::make_shared<CGameObject>();
	obj->m_self = obj;
	obj->Init();
	obj->AddComponent<CFade>();
	m_spFade = obj;

	// �t�F�[�h�I�u�W�F�N�g�͕ʂŊǗ����邽�߁A�R���|�[�l���g�V�X�e������폜
	CTransformSystem* pTransSystem = SCENE_MANAGER->GetSystem<CTransformSystem>(EComponentType::Transform);
	if (pTransSystem != nullptr)	pTransSystem->RemoveList("Fade");
	CScriptSystem* pScriptSystem = SCENE_MANAGER->GetSystem<CScriptSystem>(EComponentType::Script);
	if (pScriptSystem != nullptr)	pScriptSystem->RemoveList("Fade");
	CSpriteRendererSystem* pSpriteSystem = SCENE_MANAGER->GetSystem<CSpriteRendererSystem>(EComponentType::SpriteRenderer);
	if (pSpriteSystem != nullptr)	pSpriteSystem->RemoveList("Fade");

	// �t�F�[�h�I�u�W�F�N�g��ʂōX�V�A�`�悷�邽�߁A�ŏ��ɃR���|�[�l���g��ێ����Ă���
	m_spFadeScript = obj->GetComponent<CFade>();
	m_spFadeSprite = obj->GetComponent<CSpriteRenderer>();

	return S_OK;
}


/**
* @brief	�I������
*/
void CSceneManager::Uninit()
{
	// �t�F�[�h�j��
	m_spFade.reset();

	// ���݂̃V�[���I��
	m_pCurrentScene->Uninit();

	// �Q�[���I�u�W�F�N�g�}�l�[�W���[�I��
	CGameObjectManager::DestroyInstance();

	// �V�X�e�����X�g�I��
	for (auto it = m_spSystemList.begin(); it != m_spSystemList.end();)
	{
		(*it)->OnDestroy();
		it = m_spSystemList.erase(it);
	}
}


/**
* @brief	�X�V����
*/
void CSceneManager::Update()
{
	// ���݃V�[���̍X�V
	m_pCurrentScene->Update();

	// �t���O�������Ă���΍X�V�Ȃ�
	if (!m_bIsStop)
	{
		// �V�X�e�����X�g�̍X�V
		for (auto system : m_spSystemList)
		{
			system->OnUpdate();
		}
	}

	// �G�t�F�N�g�Ǘ��X�V
	EFFECT_MANAGER->Update();

	// �t�F�[�h�X�V
	m_spFadeScript.lock()->Update();
}


/**
* @brief	�`�揈��
*/
void CSceneManager::Draw()
{
	// �f�o�C�X�R���e�L�X�g�擾
	auto pDC = GetDeviceContext();

	// ���݃V�[���`��
	m_pCurrentScene->Draw();

	// �V�X�e�����X�g�̕`��
	for (auto system : m_spSystemList)
	{
		system->OnDraw(pDC);
	}

	// �G�t�F�N�g�Ǘ��`��
	EFFECT_MANAGER->Draw();
	
	// �t�F�[�h�`��
	m_spFadeSprite.lock()->Draw(pDC);
}


/**
* @brief	���̃V�[���֑J��
*/
void CSceneManager::SetSceneChange()
{
	// �S�ẴG�t�F�N�g���~�߂�
	EFFECT_MANAGER->StopAll();

	// ���݂̃V�[���I��
	m_pCurrentScene->Uninit();

	// �Q�[���I�u�W�F�N�g�}�l�[�W���[�I��
	GAMEOBJECT_MANAGER->Uninit();

	// �V�X�e���N���A
	for (auto system : m_spSystemList)
	{
		system->ListClear();
	}

	// ���݂̃V�[���폜
	delete m_pCurrentScene;

	// �V�[���̐؂�ւ�
	m_pCurrentScene = m_pNextScene;
	m_pNextScene = nullptr;

	// �Q�[���I�u�W�F�N�g�}�l�[�W���[������
	GAMEOBJECT_MANAGER->Init();

	// �V�����V�[���̏�����
	m_pCurrentScene->Init();

	// �ϐ��̏�����
	m_bIsStop = false;
}
