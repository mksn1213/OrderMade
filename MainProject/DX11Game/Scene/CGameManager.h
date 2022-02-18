#pragma once
/**
*
* @file		CGameManager.h
* @brief	ゲーム管理クラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/12	実装開始
* @date		2022/01//30	シングルトン継承
*
*/

/** インクルード部 */
#include <System/Utility/Singleton.h>
#include <System/CTimer.h>
#include <memory>

#define GAME_MANAGER	(CGameManager::GetInstance())

/** 前定義 */
class CGameObject;
class CTimeUpUI;
class CSpriteRenderer;

/** ゲーム管理クラス */
class CGameManager final : public Singleton<CGameManager>
{
public:
	CGameManager();
	~CGameManager();
	
	HRESULT Init()		override;
	void	Uninit()	override;
	void	Update();
	void	Draw();

	/**
	* @brief	スコア加算
	* @param	score	加算するスコア
	*/
	void AddScore(int score) { m_nScore += score; }

	/**
	* @brief	スコア取得
	* @return	int		現在のスコア
	*/
	int GetScore() { return m_nScore; }

	/**
	* @brief	時間取得
	* @return	int		残り時間
	*/
	int GetTime() { return m_pTimer->GetTime(); }

	/**
	* @brief	ポーズ中かどうか
	* @return	bool	ポーズ中か(true/ポーズ中,false/ポーズ中ではない)
	*/
	bool IsPause() { return m_bIsPause; }

	/**
	* @brief	ゲームが終了したか
	* @return	bool	ゲーム終了したか(true/終了,false/ゲーム中)
	*/
	bool IsGameFin() { return m_bGameFin; }

private:
	// スコア
	int			m_nScore;
	// 制限時間
	CTimer*		m_pTimer;
	// ポーズのON/OFF
	bool		m_bIsPause;
	// ゲーム終了フラグ
	bool		m_bGameFin;
	// ゲーム開始フラグ
	bool		m_bGameStart;
	// カウントダウン用
	int			m_nFrame;
	// ポーズ時の選択用
	bool		m_bSelect;
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// ポーズオブジェクト
	std::weak_ptr<CGameObject>		m_spPauseUIObj;
	// 終了UIオブジェクト
	std::shared_ptr<CGameObject>	m_spFinUIObj;
	// 終了UIスクリプト
	std::weak_ptr<CTimeUpUI>		m_spFinUIScript;
};