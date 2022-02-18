#pragma once
/**
*
* @file		CField.h
* @brief	フィールドクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/20	実装開始
* @date		2021/12/05	コンポーネントに変更
* @date		2022/01/30	CScriptBaseを継承
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** フィールドクラス */
class CField final : public CScriptBase
{
public:
	CField();
	virtual ~CField();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
};