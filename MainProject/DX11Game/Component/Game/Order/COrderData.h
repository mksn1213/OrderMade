#pragma once
/**
*
* @file		COrderData.h
* @brief	注文データクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	実装開始
*
*/

/** インクルード部 */
#include <System/GameObject/ObjectIDData.h>
#include <System/Utility/CColor.h>

/** 注文データクラス */
class COrderData
{
public:
	COrderData() {}
	COrderData(bool need, EObjectType kind, CColor::EColor color, int score);
	~COrderData();

	// 「==」記号のオーバーロード
	bool operator==(COrderData data)
	{
		// 一致しているかどうか
		if (m_bPotted	== data.m_bPotted	&&
			m_eKind		== data.m_eKind		&&
			m_eColor	== data.m_eColor)
		{
			return true;
		}
		return false;
	}

	// 鉢植えが必要か
	bool			m_bPotted;
	// オブジェクトの種類
	EObjectType		m_eKind;
	// 色情報
	CColor::EColor	m_eColor;
	// スコア
	int				m_nScore;
};
