/**
*
* @file		CLight.cpp
* @brief	ライトクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	実装開始
* @date		2022/01/21	ライトマネージャーを作成
*
*/

/** インクルード */
#include <System/Light/CLight.h>

/** マクロ定義 */
namespace
{
	const XMFLOAT4 DIFFUSE   = XMFLOAT4(1.0f,  1.0f,  1.0f,  1.0f);
	const XMFLOAT4 AMBIENT   = XMFLOAT4(0.1f,  0.1f,  0.1f,  1.0f);
	const XMFLOAT4 SPECULAR	 = XMFLOAT4(0.2f,  0.2f,  0.2f,  1.0f);
	const XMFLOAT3 DIRECTION = XMFLOAT3(0.5f, -1.0f,  1.0f);
}

/**
* @brief	コンストラクタ
*/
CLight::CLight()
	: m_diffuse(DIFFUSE)
	, m_ambient(AMBIENT)
	, m_specular(SPECULAR)
	, m_bIsEnable(false)
{
	XMStoreFloat3(&m_direction, XMVector3Normalize(XMLoadFloat3(&DIRECTION)));
}


/**
* @brief	デストラクタ
*/
CLight::~CLight()
{

}


/**
* @brief	更新処理
*/
void CLight::Update()
{

}