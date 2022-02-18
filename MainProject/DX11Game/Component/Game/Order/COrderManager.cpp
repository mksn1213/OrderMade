/**
*
* @file		COrderManager.cpp
* @brief	�����Ǘ��N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	�����J�n
* @date		2021/12/21	�R���|�[�l���g�ɑΉ�
*
*/

/** �C���N���[�h�� */
#include <Component/Game/Order/COrderManager.h>
#include <System/Utility/CSVLoader.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Order/COrder.h>
#include <System/Utility/Search.h>
#include <Scene/CGameManager.h>
#include <System/Systems/CTransformSystem.h>
#include <System/Sound/CSound.h>
#include <Scene/CSceneManager.h>

// �R���|�[�l���g
#include <Component/Game/Plant/CSprout.h>
#include <Component/Game/Plant/CFlower.h>
#include <Component/Game/Order/GameUI/COrderBoardUI.h>

/** �}�N����` */
namespace
{
	const int ADDTIME = 60 * 13;	// ������ǉ����鎞�ԊԊu
}

/**
* @brief	�R���X�g���N�^
*/
COrderManager::COrderManager()
{

}


/**
* @brief	�f�X�g���N�^
*/
COrderManager::~COrderManager()
{

}


/**
* @brief	����������
*/
HRESULT COrderManager::Init()
{
	// �����f�[�^�ǂݍ���
	LoadOrderDataFromCSV("data/csv/orderData/orderList.csv", 1, 0);

	// SE�{�����[���Z�b�g
	SOUND_MANAGER->SetVolume(SE_ORDER_BREAK, 4.0f);
	SOUND_MANAGER->SetVolume(SE_SHIP, 5.0f);
	// �ϐ�������
	m_nCount = 60 * 10;

	return S_OK;
}


/**
* @brief	�I������
*/
void COrderManager::Uninit()
{
	// �����f�[�^�̃N���A
	m_orderDataList.clear();

	// �����f�[�^�I�u�W�F�N�g�̍폜
	for (auto it = m_spOrderList.begin(); it != m_spOrderList.end();)
	{
		(*it)->RemoveComponentAll();
		it = m_spOrderList.erase(it);
	}
	m_spOrderList.clear();
}


/**
* @brief	�X�V����
*/
void COrderManager::Update()
{
	// ������ǉ����邩
	ShouldAddOrder();

	// UI�ړ��p�t���O
	bool move = false;

	// �����̍X�V
	for (auto order = m_spOrderList.begin(); order != m_spOrderList.end();)
	{	
		const auto& com = (*order)->GetComponent<COrder>();
		// �������폜���ꂽ���A���̒����̈ړ��t���O��ON�ɂ���
		if (move)
		{
			const auto& uiCom = com.lock()->GetGameObject().lock()->GetComponent<COrderBoardUI>().lock();
			uiCom->MoveON();
		}

		// �X�V�ł��Ȃ������ꍇ�����폜
		if (!com.lock()->IsUpdate())
		{
			(*order)->RemoveComponentAll();
			// �����폜
			order = m_spOrderList.erase(order);
			// SE�Đ�
			SOUND_MANAGER->Play(SE_ORDER_BREAK);
			// �ړ��t���OON
			move = true;
		}
		else
		{
			order++;
		}
	}
}


/**
* @brief	�`�揈��
*/
void COrderManager::Draw()
{

}


/**
* @brief	�����𐶐�
* @param	data	�쐬���钍���f�[�^
* @return	std::weak_ptr<CGameObject>	���������Q�[���I�u�W�F�N�g
*/
std::weak_ptr<CGameObject> COrderManager::CreateOrder(COrderData data)
{
	// �C���X�^���X��
	std::shared_ptr<CGameObject> spObj = std::make_shared<CGameObject>();
	// ���g���i�[
	spObj->m_self = spObj;
	// ������
	spObj->Init();
	// �R���|�[�l���g�ǉ�
	const auto& spCom = spObj->AddComponent<COrder>();
	// �����f�[�^�Z�b�g
	spCom.lock()->SetOrderData(data);
	// ���X�g�Ɋi�[
	m_spOrderList.push_back(spObj);
	// �����͕ʂŊǗ����邽�߁A�R���|�[�l���g�V�X�e������폜
	CTransformSystem* pSystem = SCENE_MANAGER->GetSystem<CTransformSystem>(EComponentType::Transform);
	if (pSystem != nullptr)	pSystem->RemoveList("Order");

	return spObj;
}


/**
* @brief	������ǉ����邩�ǂ���
*/
void COrderManager::ShouldAddOrder()
{
	m_nCount++;
	if (m_nCount >= ADDTIME)
	{
		// �������X�g���烉���_���Œ���������
		int randomNum = rand() % m_orderDataList.size();
		COrderData data = m_orderDataList.at(randomNum);
		// ��������
		const auto& orderObj = CreateOrder(data);
		// �J�E���g���Z�b�g
		m_nCount = 0;
	}
}


/**
* @brief	�A�C�e���ƒ������ƍ�
* @param	itemObj		�A�C�e���I�u�W�F�N�g
* @return	bool		�ƍ�����(true/��v,false/�s��v)
*/
bool COrderManager::CheckOrder(std::weak_ptr<CGameObject> itemObj)
{
	// �A�C�e���f�[�^�𒍕��f�[�^�ɕϊ�
	COrderData itemData;
	if (itemObj.lock()->GetObjectID() == EObjectType::Potted)
	{
		itemData.m_bPotted = true;
		const auto& childList = itemObj.lock()->m_spTransform.lock()->GetChildList();
		const auto& item = SearchExistsList(childList, "Item");
		EObjectType id = item.lock()->GetObjectID();
		if (id == EObjectType::Sprout)
		{
			const auto& com = item.lock()->GetComponent<CSprout>();
			itemData.m_eColor = com.lock()->GetColor().colorType;
		}
		else if (id == EObjectType::Flower)
		{
			const auto& com = item.lock()->GetComponent<CFlower>();
			itemData.m_eColor = com.lock()->GetColor().colorType;
		}
		itemData.m_eKind = id;
	}
	else
	{
		itemData.m_bPotted = false;
		EObjectType id = itemObj.lock()->GetObjectID();
		if (id == EObjectType::Sprout)
		{
			const auto& com = itemObj.lock()->GetComponent<CSprout>();
			itemData.m_eColor = com.lock()->GetColor().colorType;
		}
		else if (id == EObjectType::Flower)
		{
			const auto& com = itemObj.lock()->GetComponent<CFlower>();
			itemData.m_eColor = com.lock()->GetColor().colorType;
		}
		itemData.m_eKind = id;
	}

	// UI�ړ��p�t���O
	bool move = false;

	// �������X�g�Əƍ�
	for (auto it = m_spOrderList.begin(); it != m_spOrderList.end();)
	{
		// �����f�[�^�擾
		const auto& com = (*it)->GetComponent<COrder>().lock();
		COrderData orderData = com->GetOrderData();

		// �������폜���ꂽ���A���̒����̈ړ��t���O��ON�ɂ���
		if (move)
		{
			const auto& uiCom = com->GetGameObject().lock()->GetComponent<COrderBoardUI>().lock();
			uiCom->MoveON();
		}

		// �����Əƍ�
		if (orderData == itemData && !move)
		{
			// �X�R�A���Z
			GAME_MANAGER->AddScore(orderData.m_nScore);
			// SE�Đ�
			SOUND_MANAGER->Play(SE_SHIP);
			// �����̍폜
			(*it)->RemoveComponentAll();
			it = m_spOrderList.erase(it);
			move = true;
		}
		else
		{
			++it;
		}
	}

	if (move)	return true;
	return false;
}