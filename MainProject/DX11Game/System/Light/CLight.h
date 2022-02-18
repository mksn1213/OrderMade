#pragma once
/**
*
* @file		CLight.h
* @brief	ライトクラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	実装開始
* @date		2022/01/21	ライトマネージャーを作成
*
*/

/** インクルード */
#include <System/Defines.h>

/** ライトクラス */
class CLight
{
public:
	CLight();
	virtual ~CLight();

	virtual void Update();

	/**
	* @brief	ディフューズ取得
	* @return	XMFLOAT4	ディフューズ
	*/
	const XMFLOAT4& GetDiffuse() const { return m_diffuse; }

	/**
	* @brief	アンビエント取得
	* @return	XMFLOAT4	アンビエント
	*/
	const XMFLOAT4& GetAmbient() const { return m_ambient; }

	/**
	* @brief	スペキュラ取得
	* @return	XMFLOAT4	スペキュラ
	*/
	const XMFLOAT4& GetSpecular() const { return m_specular; }


	/**
	* @brief	方向取得
	* @return	XMFLOAT3	方向
	*/
	const XMFLOAT3& GetDirection() const { return m_direction; }

	/**
	* @brief	有効ON/OFF
	* @param	enable	有効/無効(true/有効 false/無効)
	*/
	void Enable(bool enable) { m_bIsEnable = enable; }

	/**
	* @brief	有効かどうか
	* @return	bool	有効/無効(true/有効 false/無効)
	*/
	bool IsEnable() const { return m_bIsEnable; }

	/**
	* @brief	方向セット
	* @param	XMFLOAT3	方向
	*/
	void SetDirection(XMFLOAT3 direction) 
	{ 
		XMStoreFloat3(&m_direction, XMVector3Normalize(XMLoadFloat3(&direction)));
	}

private:
	XMFLOAT4 m_diffuse;
	XMFLOAT4 m_ambient;
	XMFLOAT4 m_specular;
	XMFLOAT3 m_direction;
	bool	 m_bIsEnable;
};