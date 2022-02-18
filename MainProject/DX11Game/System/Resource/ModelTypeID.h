#pragma once
/**
* @enum		EModelType
* @brief	モデルタイプ
*/
enum class EModelType
{
	Player = 0,		// プレイヤー
	TargetPoint,	// プレイヤーのターゲットポイント
	Wall,			// 壁
	SeedBox,		// 種箱
	Soil,			// 土
	Well,			// 井戸
	ClayBox,		// 粘土箱
	FertilizerBagC,	// 肥料袋(シアン)
	FertilizerBagM,	// 肥料袋(マゼンタ)
	FertilizerBagY,	// 肥料袋(イエロー)

	ShipGate,		// 出荷ゲート
	ShipTruck,		// 出荷トラック
	Oven,			// 竈
	PotteryWheel,	// 轆轤
	Wheel,			// 回転台

	Seed,			// 種
	Bucket,			// バケツ
	Sprout_W,		// 芽(白)
	Sprout_C,		// 芽(シアン)
	Sprout_M,		// 芽(マゼンタ)
	Sprout_Y,		// 芽(イエロー)
	Sprout_R,		// 芽(赤)
	Sprout_G,		// 芽(緑)
	Sprout_B,		// 芽(青)

	Flower_W,		// 花(白)
	Flower_C,		// 花(シアン)
	Flower_M,		// 花(マゼンタ)
	Flower_Y,		// 花(イエロー)
	Flower_R,		// 花(赤)
	Flower_G,		// 花(緑)
	Flower_B,		// 花(青)

	Clay,			// 粘土
	TrimClay,		// 加工後粘土
	Potted,			// 鉢植え
	FertilizerC,	// 肥料(シアン)
	FertilizerM,	// 肥料(マゼンタ)
	FertilizerY,	// 肥料(イエロー)
	TrashBox,		// ごみ箱

	Bonfire,		// 焚火
	Fence1,			// フェンス
	FlowerBed,		// 花壇
	StackedStraw,	// 藁
	Stump,			// 切り株
	Tree1,			// 木1
	Tree2,			// 木2

	MaxModel
};

