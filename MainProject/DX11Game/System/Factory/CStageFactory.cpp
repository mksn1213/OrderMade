/**
*
* @file		CStageFactory.cpp
* @brief	ステージファクトリクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	実装開始
* @date		2021/12/01	コンポーネント指向に対応して処理を変更
* @date		2021/12/08	csvファイルの読み込みを読み込み用の関数で行うように変更
*
*/

/** インクルード部 */
#include <System/Factory/CStageFactory.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/GameObject/ObjectIDData.h>

#include <System/Utility/CSVLoader.h>
#include <System/Utility/Vector3.h>

// ステージ生成用
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

// ゲーム中の生成用
#include <Component/Game/Plant/CSeed.h>
#include <Component/Game/Player/CPlayerTarget.h>
#include <Component/Game/Plant/CSprout.h>
#include <Component/Game/Plant/CFlower.h>
#include <Component/Game/Potted/CClay.h>
#include <Component/Game/Potted/CPotted.h>
#include <Component/Game/Soil/CFertilizer.h>

/** マクロ定義 */
namespace
{
	const float OBJECT_SPACE = 20.0f;
}

/**
* @brief	コンストラクタ
*/
CStageFactory::CStageFactory()
{

}


/**
* @brief	デストラクタ
*/
CStageFactory::~CStageFactory()
{

}


/**
* @brief	初期化処理
*/
void CStageFactory::Init(ESceneType scene, int nStageNo)
{
	// フィールドの生成
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
* @brief	終了処理
*/
void CStageFactory::Uninit()
{
}


/**
* @brief	ステージ生成
* @param	fileName	生成するファイル名
*/
void CStageFactory::CreateStage(const std::string& fileName)
{
	// CSVデータ読み込み
	std::vector<std::vector<std::string>> data = LoadObjectDataFromCSV(fileName);

	// ゲームオブジェクト生成
	for (int i = 0; i < data.size(); ++i)
	{
		// データからトランスフォームを取得
		Vector3 pos		= Vector3(std::stof(data[i].at(1)), std::stof(data[i].at(2)), std::stof(data[i].at(3)));
		Vector3 rot		= Vector3(std::stof(data[i].at(4)), std::stof(data[i].at(5)), std::stof(data[i].at(6)));
		Vector3 scale	= Vector3(std::stof(data[i].at(7)), std::stof(data[i].at(8)), std::stof(data[i].at(9)));

		// インスタンス化
		const auto& object = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(pos).lock();
		// トランスフォーム取得
		const auto& transform = object->m_spTransform.lock();
		// 角度セット
		transform->SetRotation(rot);
		// サイズセット
		transform->SetScale(scale);

		// オブジェクトIDで生成するゲームオブジェクトを判別する
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
* @brief	ゲームオブジェクトの生成
* @param	type		オブジェクトタイプ
* @param	pos			生成する座標
* @return	std::weak_ptr<CGameObject>	生成したゲームオブジェクト
*/
std::weak_ptr<CGameObject> CStageFactory::CreateGameObject(EObjectType type, Vector3 pos)
{
	// ゲームオブジェクトの生成
	std::weak_ptr<CGameObject> object = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(pos);

	// コンポーネント追加
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
