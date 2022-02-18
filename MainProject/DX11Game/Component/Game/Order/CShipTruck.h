#pragma once
/**
*
* @file		CShipTruck.h
* @brief	出荷トラッククラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/07	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <System/Utility/Vector3.h>

/** 出荷トラッククラス */
class CShipTruck final : public CScriptBase
{
public:
	CShipTruck();
	virtual ~CShipTruck();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	bool IsFin()		{ return m_bFin; }
	void SetShipFlag()	
	{ 
		m_bShipping = true; 
		m_bIsPlaySE = false;
	}
	void SetMoveFlag(Vector3 pos)
	{ 
		m_gatePos = pos;
		m_bMove = true;
		m_bIsPlaySE = false;
	}

private:
	// 移動フラグ
	bool	m_bMove;
	// 出荷フラグ
	bool	m_bShipping;
	// 終了フラグ
	bool	m_bFin;
	// セット座標
	Vector3	m_gatePos;
	// SE再生用
	bool	m_bIsPlaySE;
	// エフェクト再生用
	int		m_nFrame;
};