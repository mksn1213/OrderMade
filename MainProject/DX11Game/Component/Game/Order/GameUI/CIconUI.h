#pragma once
/**
*
* @file		CIconUI.h
* @brief	アイコンUIクラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/28	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>
#include <System/Resource/TextureID.h>

class CColor;
class CMeshRenderer;
/** アイコンUIクラス */
class CIconUI final : public CScriptBase
{
public:
	CIconUI();
	virtual ~CIconUI();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void SetIconTexture(ETexture type);
	void SetIconTexture(CColor color);

	/**
	* @brief	移動フラグON
	* @param	移動距離
	*/
	void MoveON(float distance)
	{
		m_bMoveFlag = true;
		m_fRemainingDistance += distance;
	}

private:
	// メッシュレンダラー
	std::weak_ptr<CMeshRenderer>	m_spRenderer;
	// 移動フラグ
	bool							m_bMoveFlag;
	// 移動量
	float							m_fRemainingDistance;
};