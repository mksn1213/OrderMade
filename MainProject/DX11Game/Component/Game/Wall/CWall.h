#pragma once
/**
*
* @file		CWall.h
* @brief	壁クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/10	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 壁クラス */
class CWall final : public CScriptBase
{
public:
	CWall();
	virtual ~CWall();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)	override;
};