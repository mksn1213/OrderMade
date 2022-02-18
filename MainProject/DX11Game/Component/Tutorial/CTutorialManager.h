#pragma once
/**
*
* @file		CTutorialManager.h
* @brief	チュートリアル管理クラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	実装開始
*
*/

/** インクルード部 */
#include <System/Utility/Singleton.h>
#include <memory>

#define TUTORIAL_MANAGER	(CTutorialManager::GetInstance())

/** 前定義 */
class CTutorialMessageUI;
class CTutorialOperateUI;

/** チュートリアル管理クラス */
class CTutorialManager final : public Singleton<CTutorialManager>
{
public:
	CTutorialManager();
	~CTutorialManager();

	HRESULT Init()		override;
	void	Uninit()	override;
	void	Update();
	void	Draw();

	/**
	* @brief	ステージ番号セット
	* @param	nStageNo	ステージ番号
	*/
	void SetStageNo(int nStageNo);

	/**
	* @brief	ステージ番号取得
	* @param	int		ステージ番号
	*/
	int GetStageNo() { return m_nStageNo; }

	/**
	* @brief	終了
	*/
	void Fin() { m_bIsFin = true; }

private:
	// メッセージUIオブジェクト
	std::weak_ptr<CTutorialMessageUI>	m_spMessageCom;
	// 説明UIオブジェクト
	std::weak_ptr<CTutorialOperateUI>	m_spOperateCom;
	// ステージ番号
	int		m_nStageNo;
	// 終了フラグ
	bool	m_bIsFin;
	// 生成フラグ
	bool	m_bIsCreate;
};

