#pragma once
/**
*
* @file		CSceneResult.h
* @brief	リザルトシーンクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/11	実装開始
*
*/

/** インクルード部 */
#include <Scene/CSceneBase.h>

/**  リザルトシーンクラス */
class CSceneResult final : public CSceneBase
{
public:
	CSceneResult();
	virtual ~CSceneResult();

	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;

	/**
	* @brief	スコアセット
	* @param	nScore	スコア
	*/
	void SetScore(int nScore) { m_nScore = nScore; }

private:
	int m_nScore;
};