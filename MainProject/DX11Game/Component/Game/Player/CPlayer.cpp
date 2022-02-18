/**
*
* @file		CPlayer.cpp
* @brief	プレイヤークラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/10/13  実装開始
* @date		2021/12/03	コンポーネントに変更
* @data		2021/12/09	ターゲットポイントのゲームオブジェクト作成
*
*/

/** インクルード部 */
#include <Component/Game/Player/CPlayer.h>
#include <System/GameObject/CGameObject.h>
#include <System/GameObject/CGameObjectManager.h>
#include <System/Factory/CStageFactory.h>
#include <System/CInput.h>
#include <Component/Game/Player/Action/CAction.h>
#include <System/Resource/CModelManager.h>
#include <System/Camera/CCameraManager.h>
#include <System/Sound/CSound.h>

// コンポーネント
#include <System/Renderer/CModelRenderer.h>
#include <System/Component/CTransform.h>
#include <System/Resource/ModelTypeID.h>
#include <Component/Game/Player/CPlayerTarget.h>
#include <Component/Game/Player/Action/GameUI/CActionGaugeUI.h>
#include <System/Component/CRigidbody.h>

/** マクロ定義 */
namespace
{
	const float SPEED = 0.2f;			// 移動速度
	const float ROTATE_RATE = 0.2f;		// 回転
}

/**
* @brief	コンストラクタ
*/
CPlayer::CPlayer()
	: m_pModel(nullptr)
	, m_bHasItem(false)
	, m_bIsAction(false)
	, m_bOldIsAction(false)
	, m_rotDest(Vector3::zero())

{
	
}


/**
* @brief	デストラクタ
*/
CPlayer::~CPlayer()
{
	if (m_pModel != nullptr)	m_pModel = nullptr;
}


/**
* @brief	生成時
*/
void CPlayer::OnCreate()
{
	const auto& obj = m_spGameObject.lock();

	// スクリプト初期化
	CScriptBase::OnCreate();

	// タグ設定
	obj->SetTag("Player");

	// 名前設定
	obj->SetName("Player");

	// コンポーネントID設定
	SetID(Script);

	// レンダラー追加
	const auto& renderer = obj->AddComponent<CModelRenderer>().lock();
	renderer->SetModel(EModelType::Player);
	m_pModel = MODEL_MANAGER->GetModel(EModelType::Player);
	// アニメーションセット
	m_pModel->SetAnimIndex(3);
	m_pModel->SetAnimTime(1.5f);

	// リジッドボディ追加
	const auto& rigidbody = obj->AddComponent<CRigidbody>().lock();
	rigidbody->SetUseGravity(true);
	rigidbody->SetUsePhysics(true);
	m_spRigidbody = rigidbody;

	// コライダー追加
	const auto& collider = obj->AddComponent<CCollider>().lock();
	collider->SetColliderSize(CCollider::EColliderType::Sphere, Vector3(5.0f, 10.0f, 10.0f));
	collider->m_pMainScript = this;

	// 当たり判定元フラグON
	collider->SetCollisionFlag(true);

	// ターゲットオブジェクト生成
	m_spTargetPoint = CStageFactory::CreateGameObject(EObjectType::PlayerTarget);

	// 親子関係を結ぶ
	CTransform::SetParentChildRelation(m_spGameObject, m_spTargetPoint, EDirection::Front, 10.0f);
	
	// プレイヤーセット
	m_spTargetPoint.lock()->GetComponent<CPlayerTarget>().lock()->m_spPlayer = obj->GetComponent<CPlayer>();

	// カメラにセット
	CAMERA->Get(0)->SetChaseTarget(m_spTransform);

	// SEボリュームセット
	SOUND_MANAGER->SetVolume(SE_TAKE, 2.0f);
	SOUND_MANAGER->SetVolume(SE_PUT, 2.0f);
}


/**
* @brief	破棄時
*/
void CPlayer::OnDestroy()
{
	CScriptBase::OnDestroy();
}


/**
* @brief	更新処理
*/
void CPlayer::Update()
{
	if (m_bOldIsAction && !m_bIsAction)
	{
		m_spGameObject.lock()->RemoveComponent<CAction>();
		m_bOldIsAction = m_bIsAction;
	}

	// アクション中は動作しない
	if (m_bIsAction)
	{
		m_pModel->SetAnimIndex(3);
		m_bOldIsAction = m_bIsAction;
		return;
	}

	// 移動更新
	MoveUpdate();

	// 回転更新
	AngleUpdate();
}


/**
* @brief	移動更新
*/
void CPlayer::MoveUpdate()
{
	m_pModel->SetAnimIndex(3);

	if (CInput::GetKeyPress(VK_A))
	{
		if (CInput::GetKeyPress(VK_W))			//-----左前
		{
			m_spRigidbody.lock()->AddForce(Vector3(-SPEED, 0.0f, SPEED));
			m_rotDest->y = XM_PI * 0.75f;
		}
		else if (CInput::GetKeyPress(VK_S))		//-----左後
		{
			m_spRigidbody.lock()->AddForce(Vector3(-SPEED, 0.0f, -SPEED));
			m_rotDest->y = XM_PI * 0.25f;
		}
		else									//-----左
		{
			m_spRigidbody.lock()->AddForce(Vector3(-SPEED, 0.0f, 0.0f));
			m_rotDest->y = XM_PIDIV2;
		}
		m_pModel->SetAnimIndex(0);
	}
	else if (CInput::GetKeyPress(VK_D))
	{
		if (CInput::GetKeyPress(VK_W))			//-----右前
		{
			m_spRigidbody.lock()->AddForce(Vector3(SPEED, 0.0f, SPEED));
			m_rotDest->y = -XM_PI * 0.75f;
		}
		else if (CInput::GetKeyPress(VK_S))		//-----右後
		{
			m_spRigidbody.lock()->AddForce(Vector3(SPEED, 0.0f, -SPEED));
			m_rotDest->y = -XM_PI * 0.25f;
		}
		else									//-----右
		{
			m_spRigidbody.lock()->AddForce(Vector3(SPEED, 0.0f, 0.0f));
			m_rotDest->y = -XM_PIDIV2;
		}
		m_pModel->SetAnimIndex(0);
	}
	else if (CInput::GetKeyPress(VK_W))			//-----前
	{
		m_spRigidbody.lock()->AddForce(Vector3(0.0f, 0.0f, SPEED));
		m_rotDest->y = XM_PI;
		m_pModel->SetAnimIndex(0);
	}
	else if (CInput::GetKeyPress(VK_S))			//-----後
	{
		m_spRigidbody.lock()->AddForce(Vector3(0.0f, 0.0f, -SPEED));
		m_rotDest->y = 0.0f;
		m_pModel->SetAnimIndex(0);
	}	
}


/**
* @brief	角度更新
*/
void CPlayer::AngleUpdate()
{
	// 目的の角度までの差分
	Vector3 rotate = m_spTransform.lock()->GetRotation();
	float fDiffRotY = m_rotDest->y - XMConvertToRadians(rotate->y);
	if (fDiffRotY > XM_PI)	fDiffRotY -= XM_2PI;
	if (fDiffRotY < -XM_PI)	fDiffRotY += XM_2PI;

	// 目的の角度まで慣性をかける
	rotate->y += XMConvertToDegrees(fDiffRotY * ROTATE_RATE);
	if (rotate->y > XM_PI)rotate->y -= XMConvertToDegrees(XM_2PI);
	else rotate->y += XMConvertToDegrees(XM_2PI);

	// 角度を反映
	m_spTransform.lock()->SetRotation(rotate);
}


/**
* @brief	当たった際の処理
* @param	collider		相手のコライダー
*/
void CPlayer::OnCollision(std::weak_ptr<CCollider> collider)
{

}


/**
* @brief	アイテムのセット
* @param	item		セットするアイテム
*/
void CPlayer::SetItem(std::weak_ptr<CGameObject> item)
{
	m_spItem = item.lock();
	m_bHasItem = true;
	// SE再生
	SOUND_MANAGER->Play(SE_TAKE);
}


/**
* @brief	アイテムの解放
*/
void CPlayer::ReleaseItem()
{
	m_spItem.reset();
	m_bHasItem = false;
	// SE再生
	SOUND_MANAGER->Play(SE_PUT);
}