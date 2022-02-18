#pragma once
/**
*
* @file		CSceneTitle.h
* @brief	タイトルシーンクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
* @date		2021/12/03	ベースクラスの変更
*
*/

/** インクルード部 */
#include <Scene/CSceneBase.h>


/** タイトルシーンクラス */
class CSceneTitle final : public CSceneBase
{
public:
	CSceneTitle();
	virtual ~CSceneTitle();

	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
};