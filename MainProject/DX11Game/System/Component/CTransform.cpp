/**
*
* @file		CTransform.cpp
* @brief	トランスフォームクラス実装
* @author	SHONOSUKE MAKITA
* @date		2021/11/29	実装開始
*
*/

/** インクルード部 */
#include <System/Component/CTransform.h>
#include <System/GameObject/CGameObject.h>
#include <Component/Game/Order/GameUI/CIconUI.h>
#include <System/Systems/CTransformSystem.h>
#include <Scene/CSceneManager.h>

/** 静的メンバ */
const EComponentType CTransform::comID = EComponentType::Transform;

/**
* @brief	コンストラクタ
*/
CTransform::CTransform()
	: m_position(Vector3::zero())
	, m_rotation(Vector3::zero())
	, m_scale(Vector3::one())
{
	XMStoreFloat4x4(&m_mtxWorld, XMMatrixIdentity());
	XMStoreFloat4x4(&m_mtxLocalWorld, XMMatrixIdentity());
}


/**
* @brief	デストラクタ
*/
CTransform::~CTransform()
{

}


/**
* @brief	生成時
*/
void CTransform::OnCreate()
{
	SetID(Transform);
	// システムに格納
	CTransformSystem* pSystem = SCENE_MANAGER->GetSystem<CTransformSystem>(EComponentType::Transform);
	if (pSystem != nullptr)	pSystem->AddList(this);
}


/**
* @brief	破棄時
*/
void CTransform::OnDestroy()
{
	// システムから除外
	CTransformSystem* pSystem = SCENE_MANAGER->GetSystem<CTransformSystem>(EComponentType::Transform);
	if (pSystem != nullptr)	pSystem->RemoveList(this);
}


/**
* @brief	更新処理
*/
void CTransform::Update()
{
	// 親ゲームオブジェクトが存在する場合
	if (m_spParent.lock())
	{
		// ビルボードは座標のみ反映
		if (m_spGameObject.lock()->GetTag() == "Billboard")
		{
			const auto& parentPos = m_spParent.lock()->m_spTransform.lock()->GetPosition();
			m_mtxWorld._41 = m_mtxLocalWorld._41 + parentPos.m_vector.x;
			m_mtxWorld._42 = m_mtxLocalWorld._42 + parentPos.m_vector.y;
			m_mtxWorld._43 = m_mtxLocalWorld._43 + parentPos.m_vector.z;
		}
		else
		{
			XMMATRIX mtxRot;

			// 回転を反映
			mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_rotation->x),
				XMConvertToRadians(m_rotation->y), XMConvertToRadians(m_rotation->z));
			auto mtx = XMLoadFloat4x4(&m_mtxLocalWorld);
			mtx *= mtxRot;

			// 親の行列をかけてトランスフォームを反映させる
			mtx *= XMLoadFloat4x4(&m_spParent.lock()->m_spTransform.lock()->GetWorldMatrix());

			// ワールド変換行列セット
			XMStoreFloat4x4(&m_mtxWorld, mtx);
		}

		// 子オブジェクトが存在していれば更新
		if (m_spChildList.size() > 0)
		{
			for (auto child : m_spChildList)
			{
				child.lock()->m_spTransform.lock()->Update();
			}
		}
	}
	else
	{
		// 行列の更新
		UpdateMatrix();

		// 子オブジェクトが存在していれば更新
		if (m_spChildList.size() > 0)
		{
			for (auto child : m_spChildList)
			{
				child.lock()->m_spTransform.lock()->Update();
			}
		}
	}

	// 当たり判定に使用するため座標を常に更新する
	m_position = Vector3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);
}


/**
* @brief	行列の更新
*/
void CTransform::UpdateMatrix()
{
	XMMATRIX mtxWorld, mtxTranslate, mtxRot, mtxScale;

	// ワールドマトリックス初期化
	mtxWorld = XMMatrixIdentity();

	// スケール反映
	mtxScale = XMMatrixScaling(m_scale->x, m_scale->y, m_scale->z);
	mtxWorld = XMMatrixMultiply(mtxScale, mtxWorld);

	// 回転を反映
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_rotation->x),
		XMConvertToRadians(m_rotation->y), XMConvertToRadians(m_rotation->z));
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// 移動を反映
	mtxTranslate = XMMatrixTranslation(m_position->x, m_position->y, m_position->z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ワールド変換行列セット
	XMStoreFloat4x4(&m_mtxWorld, mtxWorld);
}


/**
* @brief	親のセット
* @param	spParent	親となるゲームオブジェクト
* @param	dir			親からの方向
* @param	fLocalPos	セットするローカル座標
*/
void CTransform::SetParent(std::weak_ptr<CGameObject> spParent, EDirection dir, float fLocalPos)
{
	m_spParent = spParent;

	// ローカル座標の初期化
	XMStoreFloat4x4(&m_mtxLocalWorld, XMMatrixIdentity());

	// ローカル座標のセット
	SetLocalPosition(dir, fLocalPos);
}


/**
* @brief	親のセット
* @param	spParent	親となるゲームオブジェクト
* @param	dir			親からの方向
* @param	fLocalPos	セットするローカル座標
* @param	dir2		親からの方向2
* @param	fLocalPos2	セットするローカル座標2
*/
void CTransform::SetParent(std::weak_ptr<CGameObject> spParent, EDirection dir, float fLocalPos, EDirection dir2, float fLocalPos2)
{
	m_spParent = spParent;

	// ローカル座標の初期化
	XMStoreFloat4x4(&m_mtxLocalWorld, XMMatrixIdentity());

	// ローカル座標のセット
	SetLocalPosition(dir, fLocalPos);

	// ローカル座標のセット2
	SetLocalPosition(dir2, fLocalPos2);
}


/**
* @brief	ローカル座標のセット
* @param	dir			セットする方向
* @param	fLocalPos	セットするローカル座標
* @param	add			加算かどうか(true/加算,false/代入)
*/
void CTransform::SetLocalPosition(EDirection dir, float fLocalPos, bool add)
{
	// ローカル座標のセット
	if (add)
	{
		switch (dir)
		{
		case Front:		m_mtxLocalWorld._43 += -fLocalPos;	break;
		case Back:		m_mtxLocalWorld._43 += fLocalPos;	break;
		case Up:		m_mtxLocalWorld._42 += fLocalPos;	break;
		case Down:		m_mtxLocalWorld._42 += -fLocalPos;	break;
		case Right:		m_mtxLocalWorld._41 += fLocalPos;	break;
		case Left:		m_mtxLocalWorld._41 += -fLocalPos;	break;
		default:											break;
		}
	}
	else
	{
		switch (dir)
		{
		case Front:		m_mtxLocalWorld._43 = -fLocalPos;	break;
		case Back:		m_mtxLocalWorld._43 = fLocalPos;	break;
		case Up:		m_mtxLocalWorld._42 = fLocalPos;	break;
		case Down:		m_mtxLocalWorld._42 = -fLocalPos;	break;
		case Right:		m_mtxLocalWorld._41 = fLocalPos;	break;
		case Left:		m_mtxLocalWorld._41 = -fLocalPos;	break;
		default:											break;
		}
	}
}


/**
* @brief	子供を追加する
* @param	spChild
*/
void CTransform::AddChild(std::weak_ptr<CGameObject> spChild)
{
	m_spChildList.push_back(spChild);
}


/**
* @brief	親子関係を解除
* @detail	親側から呼び出すことで親子関係を解除する
* @param	childObj	解除したい子供オブジェクト
*/
void CTransform::ReleaseRelationship(std::weak_ptr<CGameObject> childObj)
{
	// 親子関係の解除
	for (auto it = m_spChildList.begin(); it != m_spChildList.end();)
	{
		if (childObj.lock() == it->lock())
		{
			// 子から親へのリンクをクリア
			it->lock()->m_spTransform.lock()->m_spParent.reset();
			// 親の子リストから削除
			it = m_spChildList.erase(it);
			break;
		}
		else
		{
			++it;
		}
	}
}


/**
* @brief	親子関係を結ぶ
* @param	parent		親になるゲームオブジェクト
* @param	child		子になるゲームオブジェクト
* @param	dir			親からの方向
* @param	fLocalPos	セットするローカル座標
*/
void CTransform::SetParentChildRelation(std::weak_ptr<CGameObject> parent, std::weak_ptr<CGameObject> child, EDirection dir, float fLocalPos)
{
	// 子のセット
	parent.lock()->m_spTransform.lock()->AddChild(child);
	// 親のセット
	child.lock()->m_spTransform.lock()->SetParent(parent, dir, fLocalPos);
	// 子オブジェクトの行列更新
	child.lock()->m_spTransform.lock()->Update();
}


/**
* @brief	親子関係を結ぶ
* @param	parent		親になるゲームオブジェクト
* @param	child		子になるゲームオブジェクト
* @param	dir			親からの方向
* @param	fLocalPos	セットするローカル座標
* @param	dir2		親からの方向2
* @param	fLocalPos2	セットするローカル座標2
*/
void CTransform::SetParentChildRelation(std::weak_ptr<CGameObject> parent, std::weak_ptr<CGameObject> child, EDirection dir, float fLocalPos, EDirection dir2, float fLocalPos2)
{
	// 子のセット
	parent.lock()->m_spTransform.lock()->AddChild(child);
	// 親のセット
	child.lock()->m_spTransform.lock()->SetParent(parent, dir, fLocalPos, dir2, fLocalPos2);
	// 子オブジェクトの行列更新
	child.lock()->m_spTransform.lock()->Update();
}


/**
* @brief	全ての子オブジェクトを取り替える
* @param	parent		付け替える相手オブジェクト
*/
void CTransform::ReplaceChildAll(std::weak_ptr<CGameObject> parent)
{
	while (m_spChildList.size() > 0)
	{
		// 親子関係の解除
		auto childObj = m_spChildList.begin()->lock();
		ReleaseRelationship(childObj);

		// 新しい親オブジェクトに取り替える
		// ビルボード(アイコン)だった場合、位置を調整する
		if (childObj->GetTag() == "Billboard")
		{
			const auto& parentChildList = parent.lock()->m_spTransform.lock()->GetChildList();
			int size = parentChildList.size();

			if (size == 1)
			{
				const auto& iconCom = parentChildList.begin()->lock()->GetComponent<CIconUI>().lock();
				if (iconCom)	iconCom->MoveON(-5.0f);
				CTransform::SetParentChildRelation(parent, childObj, EDirection::Up, 20.0f, EDirection::Right, 5.0f);
			}
			else if (size = 2)
			{
				const auto& iconCom = parentChildList.begin()->lock()->GetComponent<CIconUI>().lock();
				if (iconCom)	iconCom->MoveON(-5.0f);
				const auto& iconCom2 = parentChildList.back().lock()->GetComponent<CIconUI>().lock();
				if (iconCom2)	iconCom2->MoveON(-5.0f);

				CTransform::SetParentChildRelation(parent, childObj, EDirection::Up, 20.0f, EDirection::Right, 10.0f);
			}			
		}
		else
		{
			CTransform::SetParentChildRelation(parent, childObj, EDirection::Up, 10.0f);
		}
	}
}


/**
* @brief	前又は後の子オブジェクトを取り替える
* @param	parent		付け替える相手オブジェクト
* @param	forward		先頭の子オブジェクトかどうか(false/最後尾,true/先頭)
*/
void CTransform::ReplaceChild(std::weak_ptr<CGameObject> parent, bool forward)
{
	// 子オブジェクトが存在しない場合終了
	if (m_spChildList.size() == 0)	return;

	// 親子関係の解除
	std::weak_ptr<CGameObject> childObj;
	if (forward)	childObj = m_spChildList.begin()->lock();
	else			childObj = m_spChildList.back();
	ReleaseRelationship(childObj);
	// 新しい親オブジェクトに取り替える
	CTransform::SetParentChildRelation(parent, childObj, EDirection::Up, 20.0f, EDirection::Right, 5.0f);

	// アイコンの移動
	for (auto it = m_spChildList.begin(); it != m_spChildList.end(); ++it)
	{
		const auto& iconCom = it->lock()->GetComponent<CIconUI>().lock();
		if (iconCom)	iconCom->MoveON(5.0f);
	}
	const auto& iconCom2 =  childObj.lock()->GetComponent<CIconUI>().lock();
	if (iconCom2)	iconCom2->MoveON(-5.0f);
}
