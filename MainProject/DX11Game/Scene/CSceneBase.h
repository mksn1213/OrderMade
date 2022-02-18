#pragma once
/**
*
* @file		CSceneBase.h
* @brief	シーンベースクラス
* @author	SHONOSUKE MAKITA
* @date		2021/10/12	実装開始
* @date		2021/12/03	
*
*/

/** インクルード部 */
#include <Scene/SceneTypeID.h>
#include <System/Systems/CSystemBase.h>
#include <vector>

/** シーンクラス */
class CSceneBase
{
public:
	CSceneBase();
	virtual ~CSceneBase();

	virtual void Init()		= 0;
	virtual void Uninit()	= 0;
	virtual void Update()	= 0;
	virtual void Draw()		= 0;

	/**
	* @brief	シーンタイプセット
	* @param	type	シーンタイプ
	*/
	void		SetSceneType(ESceneType type)	{ m_eSceneType = type; }
	
	/**
	* @brief	シーンタイプ取得
	* @return	ESceneType	シーンタイプ
	*/
	ESceneType	GetSceneType()					{ return m_eSceneType; }

protected:
	// シーンタイプ
	ESceneType	m_eSceneType;
};