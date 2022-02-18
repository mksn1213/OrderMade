#pragma once
/**
*
* @file		CTimer.h
* @brief	時間クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/31	実装開始
*
*/

/** インクルード部 */
#include <System/Defines.h>

/** タイマークラス */
class CTimer
{
public:
	CTimer(int nTime);
	~CTimer();

	bool Update();
	
	/**
	* @brief	残り時間の取得
	* @return	int		残り時間
	*/
	int GetTime() { return m_nTime; }

private:
	int m_nTime;
};