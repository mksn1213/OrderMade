#pragma once
/**
*
* @file		CSeedBox.h
* @brief	種箱クラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/17	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** 種箱クラス */
class CSeedBox final : public CScriptBase
{
public:
	CSeedBox();
	virtual ~CSeedBox();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
};