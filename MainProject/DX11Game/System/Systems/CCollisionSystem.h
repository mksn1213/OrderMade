#pragma once
/**
*
* @file		CCollisionSystem.h
* @brief	コリジョンシステムクラス
* @author	SHONOSUKE MAKITA
* @date		2022/01/29	実装開始
*
*/

/** インクルード部 */
#include <System/Systems/CTemplateSystem.h>

// 前定義
class CCollider;

/** コリジョンシステムクラス */
class CCollisionSystem final : public CTemplateSystem<CCollider>
{
public:
	CCollisionSystem();
	virtual ~CCollisionSystem();

	void OnCreate()		override;
	void OnDestroy()	override;
	void OnUpdate()		override;
};