#pragma once
/**
*
* @file		CSceneTutorial.h
* @brief	チュートリアルシーンクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/10	実装開始
*
*/

/** インクルード部 */
#include <Scene/CSceneBase.h>

/** チュートリアルシーンクラス */
class CSceneTutorial final : public CSceneBase
{
public:
	CSceneTutorial();
	virtual ~CSceneTutorial();

	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;

	/**
	* @brief	ステージ番号セット
	* @param	nStageNo	ステージ番号
	*/
	void SetStageNo(int nStageNo) { m_nStageNo = nStageNo; }

	/**
	* @brief	ステージ番号取得
	* @return	int		ステージ番号
	*/
	int GetStageNo() { return m_nStageNo; }

private:
	// ステージ番号
	int m_nStageNo;
};