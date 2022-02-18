#pragma once
/**
*
* @file		CTransformSystem.h
* @brief	トランスフォームシステムクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CTemplateSystem.h>

// 前定義
class CTransform;

/** トランスフォームシステムクラス */
class CTransformSystem final : public CTemplateSystem<CTransform>
{
public:
	CTransformSystem();
	virtual ~CTransformSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnUpdate()		override;
};