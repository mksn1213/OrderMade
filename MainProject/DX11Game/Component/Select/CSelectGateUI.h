#pragma once
/**
*
* @file		CSelectGateUI.h
* @brief	セレクトゲートUIクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <Component/Select/CSelectGate.h>

/** 前定義 */
class CMeshRenderer;

/** セレクトゲートUIクラス */
class CSelectGateUI final : public CScriptBase
{
public:
	CSelectGateUI();
	virtual ~CSelectGateUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetTexture(CSelectGate::EGateType type);

private:
	std::weak_ptr<CMeshRenderer>	m_spRenderer;
};