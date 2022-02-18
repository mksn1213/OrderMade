#pragma once
/**
*
* @file		CSeed.h
* @brief	種クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/17  実装開始
* @date		2021/12/14	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 種クラス */
class CSeed final : public CScriptBase
{
public:
	CSeed();
	virtual ~CSeed();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
};