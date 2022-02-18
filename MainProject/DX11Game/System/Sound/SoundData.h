#pragma once
/**
*
* @file		SoundData.h
* @brief	サウンドデータ
* @author	SHONOSUKE MAKITA
* @date		2022/02/06	実装開始
*
*/

/**
* @enum		EBGM
* @brief	BGMタイプ
*/
enum EBGM
{
	BGM_TITLE = 0,	// タイトル
	BGM_SELECT,		// セレクト
	BGM_GAME,		// ゲーム
	BGM_RESULT,		// リザルト

	MAX_BGM
};

/**
* @enum		ESE
* @brief	SEタイプ
*/
enum ESE
{
	SE_BAKE,		// 焼ける
	SE_CAR,			// 車
	SE_CLICK,		// クリック
	SE_CURSOR,		// カーソル
	SE_FERTILIZER,	// 肥料
	SE_GAME_FINISH,	// ゲーム終了
	SE_GAME_START,	// ゲームスタート
	SE_GROW,		// 成長
	SE_ORDER_BREAK,	// 注文破棄	
	SE_ORDER_IN,	// 注文
	SE_PLANT,		// 種を植える
	SE_PAUSE,		// ポーズ
	SE_PUT,			// 置く
	SE_GIVEWATER,	// 水やり
	SE_SHIP,		// 出荷
	SE_TAKE,		// 持つ
	SE_TRIM,		// 成形
	SE_WALK,		// 歩き
	SE_WELL_IN,		// 井戸入り
	SE_WELL_OUT,	// 井戸出る
	SE_WELL_PULLEY,	// 井戸滑車

	MAX_SE
};