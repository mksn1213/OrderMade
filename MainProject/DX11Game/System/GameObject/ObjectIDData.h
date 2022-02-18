#pragma once
/**
* @enum		EObjectType
* @brief	オブジェクトタイプ
*/
enum EObjectType
{

	//-----固定オブジェクト
	None = 0,			// タイプなし
	Soil,				// 土
	Table,				// テーブル
	SeedBox,			// 種箱
	Well,				// 井戸
	ClayBox,			// 粘土箱
	FertilizerBagC,		// 肥料袋(シアン)
	FertilizerBagM,		// 肥料袋(マゼンタ)
	FertilizerBagY,		// 肥料袋(イエロー)
	ShipGate,			// 出荷ゲート
	Oven,				// 竈
	PotteryWheel,		// 轆轤
	TrashBox,			// ごみ箱



	Wall = 20,			// 壁



	//-----アイテムオブジェクト
	Seed = 50 ,			// 種
	Bucket,				// バケツ
	Sprout,				// 芽
	Flower,				// 花
	Clay,				// 粘土
	Potted,				// 鉢植え
	FertilizerC,		// 肥料(シアン)
	FertilizerM,		// 肥料(マゼンタ)
	FertilizerY,		// 肥料(イエロー)


	Player = 100,		// プレイヤー
	PlayerTarget,		// プレイヤーターゲット

	//-----配置用オブジェクト
	Bonfire = 1000,
	Fence1,
	FlowerBed,
	StackedStraw,
	Stump,
	Tree1,
	Tree2,

	MaxObjectType
};
