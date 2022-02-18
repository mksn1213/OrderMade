/**
*
* @file		Collision.cpp
* @brief	当たり判定関数群実装
* @author	SHONOSUKE MAKITA
* @date		2021/01/01	実装開始
* @date		2021/01/01	OBBとOBBの判定作成
* @date		2021/01/02	円と点の判定作成
* @date		2021/01/03	球と四角形の判定作成
* @date		2021/01/04	押し出し処理作成
* @date		2021/01/05	四角形と球の判定作成
*						球と球の判定作成
* @date		2021/01/13	角度付き四角形と円の判定作成
*
*/

/** インクルード部 */
#include <System/Utility/Vector3.h>
#include <System/Utility/Math.h>
#include <System/Component/CCollider.h>
#include <System/Component/CRigidbody.h>
#include <System/GameObject/CGameObject.h>

/**
* @brief	円と点
* @param	circlePos	円の中心座標
* @param	rad			円の半径
* @param	point		点の座標
* @return	bool		true/当たり,false/当たってない
*/
bool CircleToPoint(Vector3 circlePos, float rad, Vector3 point)
{
	Vector3 dif = point - circlePos;
	float distance = sqrt(dif->x*dif->x + dif->z*dif->z);

	if (distance <= rad)	return true;
	else				return false;
}


/**
* @brief	球と球
* @param	owner	自身のコライダー
* @param	other	相手のコライダー
* @return	当たった/当たってない
*/
bool SphereToSpphere(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other)
{
	// 中心座標
	const Vector3& ownerPos = owner.lock()->m_spTransform.lock()->GetPosition() + owner.lock()->GetCenter();
	const Vector3& otherPos = other.lock()->m_spTransform.lock()->GetPosition() + owner.lock()->GetCenter();

	// 半径
	float radius1 = owner.lock()->GetColliderSize()->x;
	float radius2 = other.lock()->GetColliderSize()->x;

	// 2点間の距離
	Vector3 distance = ownerPos - otherPos;

	// 判定
	if (LengthNotSqrt(distance) >= (radius1 + radius2) * (radius1 + radius2))	return false;

	const auto& rb1 = owner.lock()->GetRigidbody().lock();
	const auto& rb2 = other.lock()->GetRigidbody().lock();

	// 物理挙動の有り無し
	//if (rb1 && rb1->GetUsePhysics())
	//{
	//	// 物理計算
	//	rb1->CollisionPhysics(rb2, Normalize(distance));
	//}

	// 押し出し
	// 2点間と2半径の差
	float len = (radius1 + radius2) - Length(distance);
	// 押し出す方向
	Vector3 vec = Normalize(distance) * len;
	Vector3 pos = owner.lock()->m_spTransform.lock()->GetPosition();
	pos += vec;
	pos->y = 0.0f;
	owner.lock()->m_spTransform.lock()->SetPosition(pos);

	return true;
}


/**
* @brief	四角(OBB)と四角(OBB)
* @param	owner	自身のコライダー
* @param	other	相手のコライダー
* @return	当たった/当たってない
*/
bool BoxToBox(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other)
{
	const auto& rb1 = owner.lock()->GetRigidbody().lock();
	const auto& rb2 = other.lock()->GetRigidbody().lock();

	// ワールドマトリックス取得
	XMFLOAT4X4 mW1 = owner.lock()->m_spTransform.lock()->GetWorldMatrix();
	XMFLOAT4X4 mW2 = other.lock()->m_spTransform.lock()->GetWorldMatrix();

	// 中心座標取得
	Vector3 vP1, vP2;

	// 中心座標間のベクトルを求める
	XMVECTOR vD;
	vP1 = owner.lock()->m_spTransform.lock()->GetPosition() + owner.lock()->GetCenter();
	if (rb1)
	{
		const auto velocity = rb1->GetVelocity();
		vP1 += velocity;
	}
	vP2 = other.lock()->m_spTransform.lock()->GetPosition() + owner.lock()->GetCenter();
	vD = XMVectorSet(vP2->x - vP1->x, vP2->y - vP1->y, vP2->z - vP1->z, 0.0f);

	// モデル座標軸を求める
	XMVECTOR vN[8];
	vN[0] = XMVectorSet(mW1._11, mW1._12, mW1._13, 0.0f);
	vN[1] = XMVectorSet(mW1._21, mW1._22, mW1._23, 0.0f);
	vN[2] = XMVectorSet(mW1._31, mW1._32, mW1._33, 0.0f);
	vN[4] = XMVectorSet(mW2._11, mW2._12, mW2._13, 0.0f);
	vN[5] = XMVectorSet(mW2._21, mW2._22, mW2._23, 0.0f);
	vN[6] = XMVectorSet(mW2._31, mW2._32, mW2._33, 0.0f);

	// OBBの大きさ(半分)を掛けたベクトルを求める
	Vector3 half = owner.lock()->GetColliderSize() / 2;
	Vector3 half2 = other.lock()->GetColliderSize() / 2;
	XMFLOAT3 vBB1 = half.m_vector;
	XMFLOAT3 vBB2 = half2.m_vector;
	XMVECTOR vL[8];
	vL[0] = XMVectorSet(mW1._11 * vBB1.x, mW1._12 * vBB1.x, mW1._13 * vBB1.x, 0.0f);
	vL[1] = XMVectorSet(mW1._21 * vBB1.y, mW1._22 * vBB1.y, mW1._23 * vBB1.y, 0.0f);
	vL[2] = XMVectorSet(mW1._31 * vBB1.z, mW1._32 * vBB1.z, mW1._33 * vBB1.z, 0.0f);
	vL[3] = XMVectorSet(mW2._11 * vBB2.x, mW2._12 * vBB2.x, mW2._13 * vBB2.x, 0.0f);
	vL[4] = XMVectorSet(mW2._21 * vBB2.y, mW2._22 * vBB2.y, mW2._23 * vBB2.y, 0.0f);
	vL[5] = XMVectorSet(mW2._31 * vBB2.z, mW2._32 * vBB2.z, mW2._33 * vBB2.z, 0.0f);

	// 分離軸候補が面の法線ベクトル(モデル座標軸)
	float fL, f, fD;
	for (int i = 0; i < 6; ++i)
	{
		// 分離軸候補
		XMVECTOR& vS = vN[i];
		// OBBの影(の半分)の合計
		fL = 0.0f;
		for (int j = 0; j < 6; ++j)
		{
			XMStoreFloat(&f, XMVector3Dot(vS, vL[j]));
			fL += fabsf(f);
		}
		// 中心座標間の距離と比較
		XMStoreFloat(&fD, XMVector3Dot(vS, vD));
		fD = fabsf(fD);
		// 当たっていない場合終了
		if (fL < fD)	return false;
	}

	// 分離軸候補がそれぞれの辺に垂直なベクトル
	XMVECTOR vS;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 3; j < 6; ++j)
		{
			// 分離軸候補を求める
			vS = XMVector3Normalize(XMVector3Cross(vN[i], vN[j]));
			// OBBの影(の半分)の合計
			fL = 0.0f;
			for (int k = 0; k < 6; ++k)
			{
				XMStoreFloat(&f, XMVector3Dot(vS, vL[k]));
				fL += fabsf(f);
			}
			// 中心座標間の距離と比較
			XMStoreFloat(&fD, XMVector3Dot(vS, vD));
			fD = fabsf(fD);
			// 当たっていない場合終了
			if (fL < fD)	return false;
		}
	}

	// 法線(仮)
	Vector3 normal(0.0f, 0.0f, 1.0f);

	// 物理挙動の有り無し
	if (rb1 && rb1->GetUsePhysics())
	{
		// 物理計算
		rb1->CollisionPhysics(rb2, normal);
	}

	// ここまで来たら当たっている
	return true;
}


/**
* @brief	球と四角
* @detail	四角形の角度を0度にして判定を取る
* @param	owner	自身のコライダー
* @param	other	相手のコライダー
* @return	当たった/当たってない
*/
bool SphereToBox(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other)
{
	// 四角形の頂点を原点とした中心座標
	Vector3 rectHalfSize = other.lock()->GetColliderSize() / 2;
	Vector3 rectCenterPos = Vector3(rectHalfSize->x, 0.0f, rectHalfSize->z);

	// 四角形の座標を基にした円の中心座標
	Vector3 v = owner.lock()->m_spTransform.lock()->GetPosition() - other.lock()->m_spTransform.lock()->GetPosition();
	Vector3 distance = GetRotateVector(v, other.lock()->m_spTransform.lock()->GetRotation()->y);	
	Vector3 circleCenterPos = rectCenterPos + distance;

	// センター反映
	circleCenterPos += owner.lock()->GetCenter();
	rectCenterPos += other.lock()->GetCenter();

	// ボックスの最大最小
	Vector3 boxMax = Vector3(rectCenterPos->x + rectHalfSize->x, rectCenterPos->y, rectCenterPos->z + rectHalfSize->z);
	Vector3 boxMin = Vector3(rectCenterPos->x - rectHalfSize->x, rectCenterPos->y, rectCenterPos->z - rectHalfSize->z);

	// 半径取得
	float radius = owner.lock()->GetColliderSize()->x;

	// 最短距離を計算
	Vector3 vlen = LenAABBToPoint(boxMin, boxMax, circleCenterPos);
	float len = Length(vlen);

	// 判定
	if (len >= radius)	return false;

	// リジッドボディ取得
	const auto& rb1 = owner.lock()->GetRigidbody().lock();
	const auto& rb2 = other.lock()->GetRigidbody().lock();

	if (rb1 && rb1->GetUsePhysics())
	{
		// トランスフォーム取得
		const auto& ownerTrans = owner.lock()->m_spTransform.lock();

		// 物理計算
		//rb1->CollisionPhysics(rb2, Normalize(vlen));

		// 押し出し
		// ベクトルに角度を反映させる
		vlen = GetRotateVector(vlen, -other.lock()->m_spTransform.lock()->GetRotation()->y);
		float len = Length(vlen);

		len = radius - len;
		Vector3 vec = Normalize(vlen) * len;
		Vector3 pos = ownerTrans->GetPosition();
		pos += vec;
		ownerTrans->SetPosition(pos);
	}
	return true;
}


/**
* @brief	四角と球
* @param	owner	自身のコライダー
* @param	other	相手のコライダー
* @return	当たった/当たってない
*/
bool BoxToSphere(std::weak_ptr<CCollider> owner, std::weak_ptr<CCollider> other)
{
	// トランスフォーム取得
	const auto& ownerTrans = owner.lock()->m_spTransform.lock();
	const auto& otherTrans = other.lock()->m_spTransform.lock();

	// 中心座標
	Vector3 boxPos = ownerTrans->GetPosition() + owner.lock()->GetCenter();
	Vector3 spherePos = otherTrans->GetPosition() + other.lock()->GetCenter();

	// サイズ
	Vector3 boxSize = owner.lock()->GetColliderSize() / 2;

	// ボックスの最大最小
	Vector3 boxMax = Vector3(boxPos->x + boxSize->x, boxPos->y, boxPos->z + boxSize->z);
	Vector3 boxMin = Vector3(boxPos->x - boxSize->x, boxPos->y, boxPos->z - boxSize->z);

	// 半径
	float radius = other.lock()->GetColliderSize()->x;

	// 最短距離を計算
	Vector3 vlen = LenAABBToPoint(boxMin, boxMax, spherePos);
	float len = Length(vlen);

	// 判定
	if (len >= radius)	return false;

	// リジッドボディ取得
	const auto& rb1 = owner.lock()->GetRigidbody().lock();
	const auto& rb2 = other.lock()->GetRigidbody().lock();

	if (rb1 && rb1->GetUsePhysics())
	{
		// 物理計算
		//rb1->CollisionPhysics(rb2, Normalize(vlen));

		// 押し出し
		len = radius - len;
		Vector3 vec = Normalize(vlen)*len;
		Vector3 pos = ownerTrans->GetPosition();
		pos -= vec;
		ownerTrans->SetPosition(pos);
	}
	return true;
}
