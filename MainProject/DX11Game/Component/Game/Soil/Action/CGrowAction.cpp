/**
*
* @file		CGrowAction.cpp
* @brief	�����A�N�V�����N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/07	�����J�n
* @date		2021/12/18	�R���|�[�l���g�ɕύX
* @date		2021/12/28	�A�N�V�����Q�[�WUI�쐬
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Soil/Action/CGrowAction.h>
#include <System/CTimer.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Factory/CStageFactory.h>
#include <System/Effect/CEffectManager.h>
#include <Component/Tutorial/CTutorialManager.h>
#include <Scene/CSceneManager.h>
#include <System/Sound/CSound.h>
#include <System/Utility/Search.h>

// �R���|�[�l���g
#include <Component/Game/Soil/CSoil.h>
#include <Component/Game/Soil/CFertilizer.h>
#include <Component/Game/Plant/CSprout.h>
#include <Component/Game/Plant/CFlower.h>
#include <Component/Game/Order/GameUI/CIconUI.h>

/** �}�N����` */
namespace
{
	const int TIME = 180;					// �A�N�V��������
	const int EFFECT_PLAY_INTERVAL = 60;	// �G�t�F�N�g�Đ��Ԋu
}

/**
* @brief	�R���X�g���N�^
*/
CGrowAction::CGrowAction()
	: m_nFrame(EFFECT_PLAY_INTERVAL)
{

}


/**
* @brief	�f�X�g���N�^
*/
CGrowAction::~CGrowAction()
{

}


/**
* @brief	������
*/
void CGrowAction::OnCreate()
{
	// �X�N���v�g������
	CScriptBase::OnCreate();
	// �R���|�[�l���gID�ݒ�
	SetID(EComponentType::Action);
	// �^�C�}�[�̐���
	m_pTimer = new CTimer(TIME);
	// �A�N�V�����Q�[�WUI����
	CreateActionGauge(TIME, EDirection::Up, 30.0f);
	// SE�{�����[���Z�b�g
	SOUND_MANAGER->SetVolume(SE_GROW, 0.5f);
}


/**
* @brief	�X�V����
*/
void CGrowAction::Update()
{
	// �G�t�F�N�g�Đ�
	if (m_nFrame > EFFECT_PLAY_INTERVAL)
	{
		EFFECT_MANAGER->Play(EEffectType::GrowAction, m_spTransform.lock()->GetPosition());
		m_nFrame = 0;
	}
	m_nFrame++;

	// �X�V�ł��Ȃ���ΏI��
	if (!IsUpdate())
	{
		// �A�N�V�����I�����̏���
		EndProcess();
		// �A�N�V�����t���OOFF
		m_spGameObject.lock()->GetComponent<CSoil>().lock()->SetActionFlag(false);
		return;
	}
}


/**
* @brief	�A�N�V�����I�����̏���
*/
void CGrowAction::EndProcess()
{
	// SE�Đ�
	SOUND_MANAGER->Play(SE_GROW);

	// �G�t�F�N�g�Đ�
	EFFECT_MANAGER->Play(EEffectType::Grow, m_spTransform.lock()->GetPosition());

	const auto& id = m_spTargetItem.lock()->GetObjectID();

	// �����i�K�ɂ���ď�����ς���
	if (id == EObjectType::Seed)
	{
		// �e�q�֌W������
		m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(m_spTargetItem);
		// ��I�u�W�F�N�g�̍폜
		m_spTargetItem.lock()->Destroy();
		// ��I�u�W�F�N�g�̐���
		const auto& sproutObj = CStageFactory::CreateGameObject(EObjectType::Sprout);
		// �e�q�֌W�����
		CTransform::SetParentChildRelation(m_spGameObject, sproutObj, EDirection::Up, 0.0f);
	
		// �엿�����݂��Ă����ꍇ
		const auto& childList = m_spGameObject.lock()->m_spTransform.lock()->GetChildList();
		const auto& fertilizerObj = SearchExistsList(childList, "SupportItem");
		if (fertilizerObj.lock())
		{
			// ��I�u�W�F�N�g�ɐF�����Z�b�g
			const auto& addColor = fertilizerObj.lock()->GetComponent<CFertilizer>().lock()->GetColor();
			sproutObj.lock()->GetComponent<CSprout>().lock()->SetColor(addColor);
						
			// �q�I�u�W�F�N�g�����ւ���
			fertilizerObj.lock()->m_spTransform.lock()->ReplaceChildAll(sproutObj);

			// �e�q�֌W������
			m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(fertilizerObj);
			// �엿�I�u�W�F�N�g�폜
			fertilizerObj.lock()->Destroy();
		}
	}
	else if (id == EObjectType::Sprout)
	{
		// �e�q�֌W������
		m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(m_spTargetItem);
		// �ԃI�u�W�F�N�g�̐���
		const auto& flowerObj = CStageFactory::CreateGameObject(EObjectType::Flower);
		// ��I�u�W�F�N�g�̐F����ێ�
		auto color = m_spTargetItem.lock()->GetComponent<CSprout>().lock()->GetColor();
		// �q�I�u�W�F�N�g�����ւ���
		const auto& targetItemTrans = m_spTargetItem.lock()->m_spTransform.lock();
		targetItemTrans->GetChildList().begin()->lock()->Destroy();
		targetItemTrans->ReplaceChildAll(flowerObj);
		// ��I�u�W�F�N�g�̍폜
		m_spTargetItem.lock()->Destroy();
		// �e�q�֌W�����
		CTransform::SetParentChildRelation(m_spGameObject, flowerObj, EDirection::Up, 0.0f);
	
		// �엿�����݂��Ă����ꍇ
		const auto& childList = m_spGameObject.lock()->m_spTransform.lock()->GetChildList();
		const auto& fertilizerObj = SearchExistsList(childList, "SupportItem").lock();
		if (fertilizerObj)
		{
			// �ԃI�u�W�F�N�g�ɐF�����Z�b�g
			const auto& addColor = fertilizerObj->GetComponent<CFertilizer>().lock()->GetColor();
			// �Z�b�g����F�̌���
			color = color + addColor;
			// �A�C�R����ύX����
			const auto& flowerTrans = flowerObj.lock()->m_spTransform.lock();
			flowerTrans->GetChildList().back().lock()->Destroy();
			flowerTrans->GetChildList().back().lock()->GetComponent<CIconUI>().lock()->SetIconTexture(color);
			const auto& flowerChild = flowerTrans->GetChildList();
			// �A�C�R���̈ړ�
			for (auto it = flowerChild.begin(); it != flowerChild.end(); ++it)
			{
				it->lock()->GetComponent<CIconUI>().lock()->MoveON(5.0f);
			}
			// �e�q�֌W������
			m_spGameObject.lock()->m_spTransform.lock()->ReleaseRelationship(fertilizerObj);
			// �엿�I�u�W�F�N�g�폜
			fertilizerObj->Destroy();
		}

		// �F���̃Z�b�g
		flowerObj.lock()->GetComponent<CFlower>().lock()->SetColor(color);
		
		// �`���[�g���A���V�[���������ꍇ
		if (SCENE_MANAGER->GetScene()->GetSceneType() == ESceneType::SceneTutorial)
		{
			auto stageNo = TUTORIAL_MANAGER->GetStageNo();
			if (stageNo == 0)
			{
				TUTORIAL_MANAGER->Fin();
			}
			else if (stageNo == 1)
			{
				if (color.colorType != CColor::EColor::White)	TUTORIAL_MANAGER->Fin();
			}
		}
	}

	// �A�N�V�����Q�[�W�폜
	DeleteActionGauge();
}
