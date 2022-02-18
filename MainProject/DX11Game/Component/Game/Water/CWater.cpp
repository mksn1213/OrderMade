/**
*
* @file		CWater.cpp
* @brief	水クラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/02/09	実装開始
*
*/

/** インクルード部 */
#include <Component/Game/Water/CWater.h>
#include <System/GameObject/CGameObject.h>
#include <System/Renderer/CMeshRenderer.h>

/**
* @brief	コンストラクタ
*/
CWater::CWater()
{

}


/**
* @brief	デストラクタ
*/
CWater::~CWater()
{

}


/**
* @brief	生成時
*/
void CWater::OnCreate()
{
	// スクリプト初期化
	CScriptBase::OnCreate();

	// レンダラーコンポーネント追加
	const auto& renderer = m_spGameObject.lock()->AddComponent<CMeshRenderer>().lock();
	renderer->MakePlane();
	renderer->SetBaseTexture(ETexture::Water);
}


/**
* @brief	破棄時
*/
void CWater::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CWater::Update()
{
}
