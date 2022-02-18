#pragma once
/**
*
* @file		CPotted.h
* @brief	鉢植えクラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/14	実装開始
* @date		2021/12/19	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 鉢植えクラス */
class CPotted final : public CScriptBase
{
public:
	CPotted();
	virtual ~CPotted();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
};