/**
*
* @file		CStageFactory.cpp
* @brief	�X�e�[�W�t�@�N�g���N���X����
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	�����J�n
* @date		2021/12/01	�R���|�[�l���g�w���ɑΉ����ď�����ύX
* @date		2021/12/08	csv�t�@�C���̓ǂݍ��݂�ǂݍ��ݗp�̊֐��ōs���悤�ɕύX
*
*/

/** �C���N���[�h�� */
#include <System/Factory/CStageFactory.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/GameObject/ObjectIDData.h>

#include <System/Utility/CSVLoader.h>
#include <System/Utility/Vector3.h>

// �X�e�[�W�����p
#include <Component/Game/Player/CPlayer.h>
#include <Component/Game/Wall/CWall.h>
#include <Component/Game/Plant/CSeedBox.h>
#include <Component/Game/Soil/CSoil.h>
#include <Component/Game/Water/CWell.h>
#include <Component/Game/Potted/CClayBox.h>
#include <Component/Game/Soil/CFertilizerBag.h>
#include <Component/Game/Order/CShipGate.h>
#include <Component/Game/Potted/COven.h>
#include <Component/Game/Potted/CPotteryWheel.h>
#include <Component/Game/Trash/CTrashBox.h>
#include <Component/Game/Field/CFence.h>

#include <Component/Game/Water/CBucket.h>

// �Q�[�����̐����p
#include <Component/Game/Plant/CSeed.h>
#include <Component/Game/Player/CPlayerTarget.h>
#include <Component/Game/Plant/CSprout.h>
#include <Component/Game/Plant/CFlower.h>
#include <Component/Game/Potted/CClay.h>
#include <Component/Game/Potted/CPotted.h>
#include <Component/Game/Soil/CFertilizer.h>

/** �}�N����` */
namespace
{
	const float OBJECT_SPACE = 20.0f;
}

/**
* @brief	�R���X�g���N�^
*/
CStageFactory::CStageFactory()
{

}


/**
* @brief	�f�X�g���N�^
*/
CStageFactory::~CStageFactory()
{

}


/**
* @brief	����������
*/
void CStageFactory::Init(ESceneType scene, int nStageNo)
{
	// �t�B�[���h�̐���
	std::string fileName;
	switch (scene)
	{
	case ESceneType::SceneTitle:	fileName = "data/csv/stageData/Title.csv";		break;
	case ESceneType::SceneSelect:	fileName = "data/csv/stageData/Select.csv";		break;
	case ESceneType::SceneTutorial:	
		if (nStageNo == 0)			fileName = "data/csv/stageData/Tutorial1.csv";
		else if (nStageNo == 1)		fileName = "data/csv/stageData/Tutorial2.csv";
		else if (nStageNo == 2)		fileName = "data/csv/stageData/Tutorial3.csv";
		else if (nStageNo == 3)		fileName = "data/csv/stageData/Tutorial3.csv";
		break;
	case ESceneType::SceneGame:		fileName = "data/csv/stageData/Game1.csv";		break;
	default:
		break;
	}
	CreateStage(fileName);
}


/**
* @brief	�I������
*/
void CStageFactory::Uninit()
{
}


/**
* @brief	�X�e�[�W����
* @param	fileName	��������t�@�C����
*/
void CStageFactory::CreateStage(const std::string& fileName)
{
	// CSV�f�[�^�ǂݍ���
	std::vector<std::vector<std::string>> data = LoadObjectDataFromCSV(fileName);

	// �Q�[���I�u�W�F�N�g����
	for (int i = 0; i < data.size(); ++i)
	{
		// �f�[�^����g�����X�t�H�[�����擾
		Vector3 pos		= Vector3(std::stof(data[i].at(1)), std::stof(data[i].at(2)), std::stof(data[i].at(3)));
		Vector3 rot		= Vector3(std::stof(data[i].at(4)), std::stof(data[i].at(5)), std::stof(data[i].at(6)));
		Vector3 scale	= Vector3(std::stof(data[i].at(7)), std::stof(data[i].at(8)), std::stof(data[i].at(9)));

		// �C���X�^���X��
		const auto& object = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(pos).lock();
		// �g�����X�t�H�[���擾
		const auto& transform = object->m_spTransform.lock();
		// �p�x�Z�b�g
		transform->SetRotation(rot);
		// �T�C�Y�Z�b�g
		transform->SetScale(scale);

		// �I�u�W�F�N�gID�Ő�������Q�[���I�u�W�F�N�g�𔻕ʂ���
		EModelType type;
		switch (std::stoi(data[i].at(0)))
		{
		case EObjectType::Soil:				object->AddComponent<CSoil>();			object->SetObjectID(EObjectType::Soil);				break;
		case EObjectType::SeedBox:			object->AddComponent<CSeedBox>();		object->SetObjectID(EObjectType::SeedBox);			break;
		case EObjectType::Well:				object->AddComponent<CWell>();			object->SetObjectID(EObjectType::Well);				break;
		case EObjectType::ClayBox:			object->AddComponent<CClayBox>();		object->SetObjectID(EObjectType::ClayBox);			break;
		case EObjectType::FertilizerBagC: {
			const auto& com = object->AddComponent<CFertilizerBag>();
			com.lock()->SetColor(CColor::EColor::Cyan);}																				break;
		case EObjectType::FertilizerBagM: {
			const auto& com = object->AddComponent<CFertilizerBag>();
			com.lock()->SetColor(CColor::EColor::Magenta); }																			break;
		case EObjectType::FertilizerBagY: {
			const auto& com = object->AddComponent<CFertilizerBag>();
			com.lock()->SetColor(CColor::EColor::Yellow); }																				break;
		case EObjectType::ShipGate:			object->AddComponent<CShipGate>();		object->SetObjectID(EObjectType::ShipGate);			break;
		case EObjectType::Oven:				object->AddComponent<COven>();			object->SetObjectID(EObjectType::Oven);				break;
		case EObjectType::PotteryWheel:		object->AddComponent<CPotteryWheel>();	object->SetObjectID(EObjectType::PotteryWheel);		break;
		case EObjectType::TrashBox:			object->AddComponent<CTrashBox>();		object->SetObjectID(EObjectType::TrashBox);			break;
		case EObjectType::Wall:				object->AddComponent<CWall>();			object->SetObjectID(EObjectType::Wall);				break;		
		case EObjectType::Bucket:			object->AddComponent<CBucket>();		object->SetObjectID(EObjectType::Bucket);			break;
		case EObjectType::Clay:				object->AddComponent<CClay>();			object->SetObjectID(EObjectType::Clay);				break;
		case EObjectType::Player:			object->AddComponent<CPlayer>();		object->SetObjectID(EObjectType::Player);			break;
		
		case EObjectType::Bonfire:			type = EModelType::Bonfire;
		{
			object->SetObjectID((EObjectType)std::stoi(data[i].at(0)));
			const auto& renderer = object->AddComponent<CModelRenderer>().lock();
			renderer->SetModel(type);
			break;
		}
		case EObjectType::Fence1:			object->AddComponent<CFence>();			object->SetObjectID(EObjectType::Fence1);			break;
		case EObjectType::FlowerBed:		type = EModelType::FlowerBed;
		{
			object->SetObjectID((EObjectType)std::stoi(data[i].at(0)));
			const auto& renderer = object->AddComponent<CModelRenderer>().lock();
			renderer->SetModel(type);
			break;
		}
		case EObjectType::StackedStraw:		type = EModelType::StackedStraw;
		{
			object->SetObjectID((EObjectType)std::stoi(data[i].at(0)));
			const auto& renderer = object->AddComponent<CModelRenderer>().lock();
			renderer->SetModel(type);
			break;
		}
		case EObjectType::Stump:			type = EModelType::Stump;
		{
			object->SetObjectID((EObjectType)std::stoi(data[i].at(0)));
			const auto& renderer = object->AddComponent<CModelRenderer>().lock();
			renderer->SetModel(type);
			break;
		}
		case EObjectType::Tree1:			type = EModelType::Tree1;
		{
			object->SetObjectID((EObjectType)std::stoi(data[i].at(0)));
			const auto& renderer = object->AddComponent<CModelRenderer>().lock();
			renderer->SetModel(type);
			break;
		}
		case EObjectType::Tree2:			type = EModelType::Tree2; {
			object->SetObjectID((EObjectType)std::stoi(data[i].at(0)));
			const auto& renderer = object->AddComponent<CModelRenderer>().lock();
			renderer->SetModel(type);
			break;
		}

		default:																														break;
		}

	}
}


/**
* @brief	�Q�[���I�u�W�F�N�g�̐���
* @param	type		�I�u�W�F�N�g�^�C�v
* @param	pos			����������W
* @return	std::weak_ptr<CGameObject>	���������Q�[���I�u�W�F�N�g
*/
std::weak_ptr<CGameObject> CStageFactory::CreateGameObject(EObjectType type, Vector3 pos)
{
	// �Q�[���I�u�W�F�N�g�̐���
	std::weak_ptr<CGameObject> object = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(pos);

	// �R���|�[�l���g�ǉ�
	switch (type)
	{
	case EObjectType::Seed:				object.lock()->AddComponent<CSeed>();			break;
	case EObjectType::Sprout:			object.lock()->AddComponent<CSprout>();			break;
	case EObjectType::Flower:			object.lock()->AddComponent<CFlower>();			break;
	case EObjectType::Clay:				object.lock()->AddComponent<CClay>();			break;
	case EObjectType::Potted:			object.lock()->AddComponent<CPotted>();			break;
	case EObjectType::FertilizerC: {
		const auto& com = object.lock()->AddComponent<CFertilizer>();
		com.lock()->SetColor(CColor::EColor::Cyan); }									break;
	case EObjectType::FertilizerM: {
		const auto& com = object.lock()->AddComponent<CFertilizer>();
		com.lock()->SetColor(CColor::EColor::Magenta); }								break;
	case EObjectType::FertilizerY: {
		const auto& com = object.lock()->AddComponent<CFertilizer>();
		com.lock()->SetColor(CColor::EColor::Yellow); }									break;
	case EObjectType::PlayerTarget:		object.lock()->AddComponent<CPlayerTarget>();	break;
	default:
		break;
	}
	object.lock()->SetObjectID(type);

	return object;
}
