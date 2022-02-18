#pragma once
/**
*
* @file		CActionGaugeUI.h
* @brief	アクションゲージUIクラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/26	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** アクションゲージUIクラス */
class CActionGaugeUI final : public CScriptBase
{
public:
	CActionGaugeUI();
	virtual ~CActionGaugeUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	/**
	* @brief	アクション時間セット
	* @param	time	アクション完了にかかる時間
	*/
	void SetActionTime(int time) 
	{ 
		m_nTime = time; 
		m_fIncrease = 10.0f / m_nTime;
	}

private:
	int		m_nTime;
	// ゲージの増加幅
	float	m_fIncrease;
};
