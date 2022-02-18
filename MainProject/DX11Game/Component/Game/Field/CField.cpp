/**
*
* @file		CField.cpp
* @brief	フィールドクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/15  実装開始
* @date		2021/12/05	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Field/CField.h>
#include <System/GameObject/CGameObject.h>
#include <System/Renderer/CMeshRenderer.h>

/**
* @brief	コンストラクタ
*/
CField::CField()
{

}


/**
* @brief	デストラクタ
*/
CField::~CField()
{

}


/**
* @brief	生成時
*/
void CField::OnCreate()
{
	// スクリプト初期化
	CScriptBase::OnCreate();

	// レンダラーコンポーネント追加
	const auto& renderer = m_spGameObject.lock()->AddComponent<CMeshRenderer>().lock();
	m_spTransform.lock()->SetScale(Vector3(400.0f, 1.0f, 400.0f));
	renderer->MakePlane(10.0f);
	renderer->SetBaseTexture(ETexture::Field);
}


/**
* @brief	破棄時
*/
void CField::OnDestroy()
{
	CScriptBase::OnDestroy();
}

/**
* @brief	更新処理
*/
void CField::Update()
{
}