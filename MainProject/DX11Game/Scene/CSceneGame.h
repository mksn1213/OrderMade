#pragma once
/**
*
* @file		CSceneGame.h
* @brief	ゲームシーンクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
* @date		2021/12/03	ベースクラスの変更
*
*/

/** インクルード部 */
#include <Scene/CSceneBase.h>

/** ゲームシーンクラス */
class CSceneGame final : public CSceneBase
{
public:
	CSceneGame();
	virtual ~CSceneGame();
	
	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;

private:
	// シーン遷移用
	int m_nFrame;
};