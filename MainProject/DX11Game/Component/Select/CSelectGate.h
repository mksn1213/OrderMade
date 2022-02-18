#pragma once
/**
*
* @file		CSelectGate.h
* @brief	セレクトゲートクラス
* @author	SHONOSUKE MAKITA
* @date		2022/02/11	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CScriptBase.h>

/** セレクトゲートクラス */
class CSelectGate final : public CScriptBase
{
public:
	/**
	* @enum		EGateType
	* @brief	ゲートタイプ
	*/
	enum EGateType
	{
		GateTitle = 0,	// タイトル
		GateTutorial,	// チュートリアル
		GateGame1,		// ゲーム1

		MaxGate
	};

public:
	CSelectGate();
	virtual ~CSelectGate();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;

	void OnCollision(std::weak_ptr<CCollider> collider)		override;
	bool ExistsProcess(std::weak_ptr<CCollider> collider)	override;

	/**
	* @brief	ゲートタイプセット
	* @param	type	ゲートタイプ
	*/
	void SetGateType(EGateType type);

private:
	// ゲートタイプ
	EGateType	m_eType;
};
