#pragma once
/**
*
* @file		CSceneSelect.h
* @brief	セレクトシーンクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
* @date		2021/12/03	ベースクラスの変更
*
*/

/** インクルード部 */
#include <Scene/CSceneBase.h>

/** セレクトシーンクラス */
class CSceneSelect final : public CSceneBase
{
public:
	CSceneSelect();
	virtual ~CSceneSelect();

	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
};