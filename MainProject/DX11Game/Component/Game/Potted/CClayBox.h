#pragma once
/**
*
* @file		CClayBox.h
* @brief	粘土箱クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 粘土箱クラス */
class CClayBox final : public CScriptBase
{
public:
	CClayBox();
	virtual ~CClayBox();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
};