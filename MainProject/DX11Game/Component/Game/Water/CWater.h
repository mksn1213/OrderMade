#pragma once
/**
*
* @file		CWater.h
* @brief	水クラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/09	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 水クラス */
class CWater final : public CScriptBase
{
public:
	CWater();
	virtual ~CWater();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
};
