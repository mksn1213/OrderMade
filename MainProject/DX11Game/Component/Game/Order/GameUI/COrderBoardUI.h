#pragma once
/**
*
* @file		COrderBoardUI.h
* @brief	注文(看板)UIクラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/23	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 前定義 */
class CSpriteRenderer;
class COrderData;

/** 注文看板UIクラス */
class COrderBoardUI final : public CScriptBase
{
public:
	COrderBoardUI();
	virtual ~COrderBoardUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetOrder(COrderData data);

	/**
	* @brief	移動フラグON
	*/
	void MoveON()
	{
		m_bMoveFlag = true;
		m_fRemainingDistance += 150.0f;
	}

private:
	// スプライトレンダラー
	std::weak_ptr<CSpriteRenderer>	m_spSprite;
	// 移動フラグ
	bool							m_bMoveFlag;
	// 移動量
	float							m_fRemainingDistance;
	// SE再生済かどうか
	bool							m_bIsPlaySound;
};
