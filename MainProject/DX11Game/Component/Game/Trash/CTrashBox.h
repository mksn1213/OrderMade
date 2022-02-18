#pragma once
/**
*
* @file		CTrashBox.h
* @brief	ごみ箱クラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/30	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** ごみ箱クラス */
class CTrashBox final : public CScriptBase
{
public:
	CTrashBox();
	virtual ~CTrashBox();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)	override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> item)	override;
};