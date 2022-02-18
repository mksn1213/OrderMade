/**
*
* @file		COrder.cpp
* @brief	注文クラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/21	実装開始
* @date		2021/12/21	コンポーネントに変更
*
*/

/** インクルード部 */
#include <Component/Game/Order/COrder.h>
#include <System/CTimer.h>
#include <System/Renderer/CSpriteRenderer.h>
#include <Component/Game/Order/COrderManager.h>
#include <Scene/CSceneManager.h>

// 生成用
#include <System/GameObject/CGameObjectManager.h>
#include <Component/Game/Order/GameUI/COrderBoardUI.h>

/** マクロ定義 */
namespace
{
	const int	TIME				= 60 * 45;	// 注文生存時間
	const float CREATE_INTERVAL_X	= 150.0f;	// UIのX方向間隔
	const float CREATE_SPACE_Y		= 150.0f;
}

/** 静的メンバ */
const EComponentType COrder::comID = EComponentType::Order;

/**
* @brief	コンストラクタ
*/
COrder::COrder()
	: m_pTimer(nullptr)
{
}


/**
* @brief	デストラクタ
*/
COrder::~COrder()
{
	SAFE_DELETE(m_pTimer);
}


/**
* @brief	生成時
*/
void COrder::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// タグ設定
	obj->SetTag("Order");
	// 名前設定
	obj->SetName("Order");
	// コンポーネントID設定
	SetID(Order);
	// タイマー生成
	m_pTimer = new CTimer(TIME);
}


/**
* @brief	破棄時
*/
void COrder::OnDestroy()
{
	// スプライトオブジェクト削除
	m_spSpriteObject.lock()->Destroy();
}


/**
* @brief	更新処理
*/
void COrder::Update()
{
	// ディゾルブパラメータ更新
	m_spSpriteRenderer.lock()->SetParam(m_pTimer->GetTime() / (float)TIME);
}


/**
* @brief	更新出来るかどうか
* @return	bool	更新の可否
*/
bool COrder::IsUpdate()
{
	// 更新出来なければ終了
	if (!m_pTimer->Update())	return false;
	// 更新
	Update();
	return true;
}


/**
* @brief	UIの生成
*/
void COrder::CreateUI()
{
	// 生成する座標の計算
	int num = ORDER_MANAGER->GetOrderQuantity() + 1;
	Vector3 createPos(-SCREEN_WIDTH / 2 + num * CREATE_INTERVAL_X, SCREEN_HEIGHT / 2 + CREATE_SPACE_Y, 1.0f);

	// 注文UI生成
	const auto& boardUIObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>(createPos).lock();
	const auto& boardUICom = boardUIObj->AddComponent<COrderBoardUI>().lock();
	boardUICom->SetOrder(m_orderData);
	m_spSpriteObject = boardUIObj;
	m_spSpriteRenderer = m_spSpriteObject.lock()->GetComponent<CSpriteRenderer>().lock();

	// マルチテクスチャ用シェーダーセット
	m_spSpriteObject.lock()->SetShader(EVertexShaderKind::Simple2DVS, EPixelShaderKind::MultiTexturePS);

	// 注文データからテクスチャをセット
	SetOrderTexture();
}


/**
* @brief	注文データを基に使用するテクスチャをセット
*/
void COrder::SetOrderTexture()
{
	// 鉢植えの有無
	const auto& renderer = m_spSpriteRenderer.lock();
	if (m_orderData.m_bPotted)	renderer->SetMultiTexture(ETexture::OrderPotted_true);
	else						renderer->SetMultiTexture(ETexture::OrderPotted_false);

	// 成長段階
	if (m_orderData.m_eKind == EObjectType::Sprout)			renderer->SetMultiTexture(ETexture::OrderPlant_Sprout, 1);
	else if (m_orderData.m_eKind == EObjectType::Flower)	renderer->SetMultiTexture(ETexture::OrderPlant_Flower, 1);

	// ディゾルブテクスチャセット
	renderer->SetEffectTexture(ETexture::Dissolve2);
}
