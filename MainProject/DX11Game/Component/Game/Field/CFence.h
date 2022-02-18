#pragma once
/**
*
* @file		CFence.h
* @brief	柵クラス
* @author	SHONOSUKE MAKITA
* @date		2021/01/11	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 柵クラス */
class CFence final : public CScriptBase
{
public:
	CFence();
	virtual ~CFence();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
};