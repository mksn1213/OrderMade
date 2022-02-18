#pragma once
/**
*
* @file		CScriptSystem.h
* @brief	スクリプトシステムクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CTemplateSystem.h>

// 前定義
class CScriptBase;

/** スクリプトシステムクラス */
class CScriptSystem final : public CTemplateSystem<CScriptBase>
{
public:
	CScriptSystem();
	virtual ~CScriptSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnUpdate()		override;
};

