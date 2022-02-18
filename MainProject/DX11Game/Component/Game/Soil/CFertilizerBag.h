#pragma once
/**
*
* @file		CFertilizerBag.h
* @brief	肥料袋クラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/16	実装開始
* @date		2021/12/11	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <System/Utility/CColor.h>

/** 肥料袋クラス */
class CFertilizerBag final : public CScriptBase
{
public:
	CFertilizerBag();
	virtual ~CFertilizerBag();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;

	void SetColor(CColor::EColor color);
	std::weak_ptr<CGameObject> Create();

private:
	// 色情報
	CColor m_eColor;
};