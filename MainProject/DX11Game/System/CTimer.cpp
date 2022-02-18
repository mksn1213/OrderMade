/**
*
* @file		CTimer.cpp
* @brief	時間クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/31	実装開始
*
*/

/** インクルード部 */
#include <System/CTimer.h>

/**
* @brief	コンストラクタ
*/
CTimer::CTimer(int nTime)
	: m_nTime(nTime)
{

}


/**
* @brief	デストラクタ
*/
CTimer::~CTimer()
{

}


/**
* @brief	更新処理
* @return	bool	更新の可否(true/更新可能　false/終了)
*/
bool CTimer::Update()
{
	// タイマーの終了判定
	if (m_nTime <= 0)	return false;
	m_nTime--;
	return true;
}