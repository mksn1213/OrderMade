#pragma once
/**
* @enum		EEffectType
* @brief	エフェクトタイプ
*/
enum EEffectType
{
	Smoke = 0 ,		// 車煙
	PlantSmoke,		// 種まき時煙
	OvenSmoke,		// 竈の煙
	OvenFire,		// 竈の炎
	Grow,			// 成長完了時
	GrowAction,		// 成長中
	Ship,			// 出荷時
	Water,			// 水しぶき

	MaxEffect
};
