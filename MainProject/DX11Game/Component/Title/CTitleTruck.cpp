/**
*
* @file		CTitleTruck.cpp
* @brief	タイトルトラッククラス実装
* @author	SHONOSUKE MAKITA
* @date		2022/01/10	実装開始
*
*/

/** インクルード部 */
#include <Component/Title/CTitleTruck.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Effect/CEffectManager.h>
#include <random>

/** マクロ定義 */
namespace
{
	const float SPEED		= 0.5f;			// 移動速度
	const float START_POS	= -300.0f;		// 始点
	const float END_POS		= 300.0f;		// 終点
	const int	EFFECT_PLAY_INTERVAL = 10;	// エフェクト再生間隔
}

/**
* @brief	コンストラクタ
*/
CTitleTruck::CTitleTruck()
	: m_nFrame(0)
{

}


/**
* @brief	デストラクタ
*/
CTitleTruck::~CTitleTruck()
{

}


/**
* @brief	生成時
*/
void CTitleTruck::OnCreate()
{
	// スクリプト初期化
	CScriptBase::OnCreate();

	// モデル追加
	const auto& renderer = m_spGameObject.lock()->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::ShipTruck);

	m_spTransform.lock()->SetRotation(Vector3(0.0f, 270.0f, 0.0f));

	// 花オブジェクト生成
	const auto& flowerObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& flowerRenderer = flowerObj->AddComponent<CModelRenderer>().lock();
	int num = (int)EModelType::Flower_W;
	num += rand() % 7;
	flowerRenderer->SetModel((EModelType)num);
	m_spRenderer = flowerRenderer;

	// 鉢植えオブジェクト生成
	const auto& pottedObj = GAMEOBJECT_MANAGER->Instantiation<CGameObject>().lock();
	const auto& pottedRenderer = pottedObj->AddComponent<CModelRenderer>().lock();
	pottedRenderer->SetModel(EModelType::Potted);
	CTransform::SetParentChildRelation(pottedObj, flowerObj, EDirection::Up, 3.0f);
	CTransform::SetParentChildRelation(m_spGameObject, pottedObj, EDirection::Up, 10.0f, EDirection::Back, 10.0f);
}


/**
* @brief	破棄時
*/
void CTitleTruck::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CTitleTruck::Update()
{
	// エフェクト再生
	if (m_nFrame > EFFECT_PLAY_INTERVAL)
	{
		EFFECT_MANAGER->Play(EEffectType::Smoke, m_spTransform.lock()->GetPosition()+Vector3::left()*10);
		m_nFrame = 0;
	}
	m_nFrame++;

	// 移動処理
	const auto& trans = m_spTransform.lock();
	auto pos = trans->GetPosition();
	pos->x += SPEED;
	// 終点まで行った場合
	if (pos->x >= END_POS)
	{
		pos->x = START_POS;
		// モデルの変更
		int num = (int)EModelType::Flower_W;
		num += rand() % 7;
		m_spRenderer.lock()->SetModel((EModelType)num);
	}
	trans->SetPosition(pos);
}