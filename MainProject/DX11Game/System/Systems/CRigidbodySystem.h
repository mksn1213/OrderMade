#pragma once
/**
*
* @file		CRigidbodySystem.h
* @brief	リジッドボディシステムクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CTemplateSystem.h>

// 前定義
class CRigidbody;

/** リジッドボディシステムクラス */
class CRigidbodySystem final : public CTemplateSystem<CRigidbody>
{
public:
	CRigidbodySystem();
	virtual ~CRigidbodySystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnUpdate()		override;
};