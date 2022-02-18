/**
*
* @file		CCollider.cpp
* @brief	コライダークラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/15	実装開始
* @date		2021/12/05	collisionクラスからcolliderクラスに変更
*						コンポーネント化
* @date		2021/01/02	リジッドボディによる動作に変更
*
*/

/** インクルード部 */
#include <System/Component/CCollider.h>
#include <System/GameObject/CGameObject.h>
#include <System/Component/CTransform.h>
#include <System/Utility/Vector3.h>
#include <Scene/CSceneManager.h>
#include <System/Utility/Math.h>
#include <System/Utility/Collision.h>
#include <System/Systems/CCollisionSystem.h>
#include <Scene/CSceneManager.h>

#include <System/CDebugProc.h>
#include <System/Renderer/CMeshRenderer.h>
#include <System/Component/CRigidbody.h>

/** 静的メンバ */
const EComponentType CCollider::comID = EComponentType::Collider;
std::list<std::weak_ptr<CCollider>>	CCollider::m_spColliderList;

/**
* @brief	コンストラクタ
*/
CCollider::CCollider()
	: m_pMainScript(nullptr)
	, m_bIsCollision(false)
	, m_colliderSize(Vector3::one())
	, m_center(Vector3::zero())
	, m_eColliderType(Box)
{
	SetID(Collider);
}


/**
* @brief	デストラクタ
*/
CCollider::~CCollider()
{
	if (m_pMainScript != nullptr)	m_pMainScript = nullptr;
}


/**
* @brief	生成時
*/
void CCollider::OnCreate()
{
	// トランスフォーム取得
	m_spTransform = m_spGameObject.lock()->GetComponent<CTransform>();
	// リジッドボディ取得
	m_spRigidbody = m_spGameObject.lock()->GetComponent<CRigidbody>();
	// コライダーリストに追加
	m_spColliderList.push_back(m_spGameObject.lock()->GetComponent<CCollider>());
	// システムリストに格納
	CCollisionSystem* pSystem = SCENE_MANAGER->GetSystem<CCollisionSystem>(EComponentType::Collider);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	破棄時
*/
void CCollider::OnDestroy()
{
	// システムから除外
	CCollisionSystem* pSystem = SCENE_MANAGER->GetSystem<CCollisionSystem>(EComponentType::Collider);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	更新処理
*/
void CCollider::Update()
{
	// TODO : デバッグ用メッシュ色変更
	if(m_spRenderer.lock())m_spRenderer.lock()->SetColor(XMFLOAT4(0.0f, 1.0f, 0.0f, 0.3f));

	// 当たり判定を行うフラグがたっていれば
	if (m_bIsCollision)
	{
		// 自身のweakポインタをコライダー型に変換
		std::weak_ptr<CCollider> main = std::static_pointer_cast<CCollider>(m_self.lock());

		for (auto collider : m_spColliderList)
		{
			// 自身と判定をとらない
			if (main.lock() == collider.lock())	continue;

			if (collider.lock()->m_spGameObject.lock()->GetObjectID() == EObjectType::PlayerTarget)	continue;

			// 当たり判定
			CheckCollision(main, collider);
		}
	}
}


/**
* @brief	当たり判定
* @param	owner	自身のコライダー
* @param	other	相手のコライダー
*/
void CCollider::CheckCollision(std::weak_ptr<CCollider> owner,std::weak_ptr<CCollider> other)
{
	bool hit = false;
	// コライダーの形状で判定を分ける
	const auto& mainType = owner.lock()->m_eColliderType;
	const auto& otherType = other.lock()->m_eColliderType;

	// 四角と四角
	if (mainType == EColliderType::Box && otherType == EColliderType::Box)
	{
		if (BoxToBox(owner, other))			hit = true;
	}
	// 四角と球
	else if (mainType == EColliderType::Box && otherType == EColliderType::Sphere)
	{
		if (BoxToSphere(owner, other))		hit = true;
	}
	// 球と球
	else if (mainType == EColliderType::Sphere && otherType == EColliderType::Sphere)
	{
		if (SphereToSpphere(owner, other))	hit = true;
	}
	// 球と四角
	else if (mainType == EColliderType::Sphere && otherType == EColliderType::Box)
	{
		if (SphereToBox(owner, other))		hit = true;
	}

	// 当たった際の処理
	if (hit)
	{
		owner.lock()->m_pMainScript->OnCollision(other.lock());
		other.lock()->m_pMainScript->OnCollision(owner.lock());

		// TODO : デバッグ用メッシュ色変更
		//if(m_spRenderer.lock())	m_spRenderer.lock()->SetColor(XMFLOAT4(1.0f, 0.0f, 0.0f, 0.5f));
	}
}


/**
* @brief	コライダーサイズセット
* @param	size		コライダーサイズ
* @param	center		コライダー中心
*/
void CCollider::SetColliderSize(EColliderType type, Vector3 size, Vector3 center)
{
	m_eColliderType = type;
	m_colliderSize = size;
	m_center = center;

	//// 当たり判定可視化
	//const auto& renderer = m_spGameObject.lock()->AddComponent<CMeshRenderer>().lock();
	//if (m_eColliderType == EColliderType::Box)
	//{
	//	renderer->MakeBox(size, m_center);
	//	renderer->SetBaseTexture(ETexture::Mesh);
	//}
	//else if (m_eColliderType == EColliderType::Sphere)
	//{
	//	renderer->MakeSphere(size, m_center);
	//	renderer->SetBaseTexture(ETexture::Mesh);
	//}
	//renderer->GetMesh()->m_pMaterial->m_diffuse = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.5f);
	//renderer->GetMesh()->m_ePrimitiveType = PT_TRIANGLE;

	//// TODO : デバッグ用
	//m_spRenderer = renderer;
}