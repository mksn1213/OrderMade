#pragma once
/**
*
* @file		CFertilizer.h
* @brief	肥料クラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/16  実装開始
* @date		2021/12/20	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <System/Utility/CColor.h>

/** 前定義 */
class CMeshRenderer;

/** 肥料クラス */
class CFertilizer final : public CScriptBase
{
public:
	CFertilizer();
	virtual ~CFertilizer();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;

	void SetColor(CColor::EColor color);

	/**
	* @brief	色情報取得
	* @return	CColor		色情報
	*/
	CColor GetColor() { return m_eColor; }

private:
	// 色情報
	CColor m_eColor;
	// メッシュレンダラー
	std::weak_ptr<CMeshRenderer>	m_spRenderer;
};