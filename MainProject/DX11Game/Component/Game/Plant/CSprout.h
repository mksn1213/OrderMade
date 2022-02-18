#pragma once
/**
*
* @file		CSprout.h
* @brief	芽クラス
* @author	SHONOSUKE MAKITA
* @date		2021/11/08	実装開始
* @date		2021/12/19	コンポーネントに変更
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <System/Utility/CColor.h>

/** 芽クラス */
class CSprout final : public CScriptBase
{
public:
	CSprout();
	virtual ~CSprout();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider, std::weak_ptr<CGameObject> itemObj)	override;

	/**
	* @brief	色のセット
	* @param	color		セットする色情報
	*/
	void SetColor(CColor color);

	/**
	* @brief	色情報の取得
	* @return	CColor		色情報
	*/
	CColor GetColor() { return m_eColor; }

private:
	CColor m_eColor;
};