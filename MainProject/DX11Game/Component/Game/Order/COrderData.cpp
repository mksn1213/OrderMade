/**
*
* @file		COrderData.cpp
* @brief	注文データクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/Order/COrderData.h>

/**
* @brief	コンストラクタ
* @param	need	鉢植えが必要か
* @param	kind	オブジェクトの種類
* @param	color	色情報
* @param	score	スコア
*/
COrderData::COrderData(bool need, EObjectType kind, CColor::EColor color, int score)
	: m_bPotted(need)
	, m_eKind(kind)
	, m_eColor(color)
	, m_nScore(score)
{

}


/**
* @brief	デストラクタ
*/
COrderData::~COrderData()
{

}