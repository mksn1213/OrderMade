/**
*
* @file		CCamera.h
* @brief	カメラクラス
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	実装開始
* @date		2022/01/21	カメラマネージャーを作成
*
*/

/** インクルード */
#include <System/Camera/CCamera.h>
#include <System/Component/CTransform.h>
#include <System/CInput.h>

/** マクロ定義 */
namespace
{
	const float		NEAR_CLIP	= 10.0f;							// ニアクリップ
	const float		FAR_CLIP	= 1000.0f;							// ファークリップ
	const float		VIEW_ANGLE	= 45.0f;							// 視野角
	const Vector3	REL_POS		= Vector3(0.0f, 100.0f, -100.0f);	// モデル相対カメラ位置
	const Vector3	REL_TARGET	= Vector3(0.0f, 10.0f, 10.0f);		// モデル相対注視点位置

}

/**
* @brief	コンストラクタ
*/
CCamera::CCamera()
	: m_pos(Vector3::back() * 5.0f)
	, m_look(Vector3::zero())
	, m_up(Vector3::up())
	, m_screenSize(SCREEN_WIDTH, SCREEN_HEIGHT)
	, m_fNearClip(NEAR_CLIP)
	, m_fFarClip(FAR_CLIP)
	, m_fFov(XMConvertToRadians(VIEW_ANGLE))
	, m_bIsEnable(false)
	, m_bChase(false)
{
	m_lookAtMatrix = m_projectionMatrix = XMMatrixIdentity();
	XMStoreFloat4x4(&m_lookAt, m_lookAtMatrix);
	XMStoreFloat4x4(&m_projection, m_projectionMatrix);
}


/**
* @brief	デストラクタ
*/
CCamera::~CCamera()
{

}


/**
* @brief	プロジェクション行列計算
* @return	XMMATRIX	計算した行列
*/
XMMATRIX CCamera::CalcProjection()
{
	return XMMatrixPerspectiveFovLH(m_fFov, GetAspect(), m_fNearClip, m_fFarClip);
}


/**
* @brief	更新処理
*/
void CCamera::Update()
{
	// 対象を追うかどうか
	if (m_bChase)
	{
		// ターゲットが存在する場合
		if (m_spTargetTrans.lock())
		{
			auto pos = m_spTargetTrans.lock()->GetPosition();
			// 視点に移動量を加算
			m_pos->x = m_pos->x * 0.9f + (pos->x + REL_POS.m_vector.x) * 0.1f;
			m_pos->y = m_pos->y * 0.9f + (pos->y + REL_POS.m_vector.y) * 0.1f;
			m_pos->z = m_pos->z * 0.9f + (pos->z + REL_POS.m_vector.z) * 0.1f;

			// 注視点に移動量を加算
			m_look->x = m_look->x * 0.9f + (pos->x + REL_TARGET.m_vector.x) * 0.1f;
			m_look->y = m_look->y * 0.9f + (pos->y + REL_TARGET.m_vector.y) * 0.1f;
			m_look->z = m_look->z * 0.9f + (pos->z + REL_TARGET.m_vector.z) * 0.1f;
		}
	}

	// ビュー行列
	m_lookAtMatrix = XMMatrixLookAtLH(
		XMLoadFloat3(&m_pos.m_vector),
		XMLoadFloat3(&m_look.m_vector),
		XMLoadFloat3(&m_up.m_vector));

	// プロジェクション行列
	m_projectionMatrix = CalcProjection();
	XMStoreFloat4x4(&m_lookAt, m_lookAtMatrix);
	XMStoreFloat4x4(&m_projection, m_projectionMatrix);
}


/**
* @brief	スクリーン座標計算
* @param	worldPos	ワールド座標
* @return	Vector3		スクリーン座標
*/
Vector3 CCamera::CalcScreenPos(Vector3 worldPos)
{
	XMVECTOR vPos = XMLoadFloat3(&worldPos.m_vector);

	float halfW = m_screenSize.x * 0.5f;
	float halfH = m_screenSize.y * 0.5f;
	XMMATRIX screenMat = XMMatrixSet(
		halfW, 0.0f,   0.0f, 0.0f,
		0.0f,  -halfH, 0.0f, 0.0f,
		0.0f,  0.0f,   1.0f, 0.0f,
		halfW, halfH,  0.0f, 1.0f);

	vPos = XMVector3TransformCoord(vPos, GetLookAtMatrix());
	vPos = XMVector3TransformCoord(vPos, GetProjectionMatrix());
	vPos = XMVector3TransformCoord(vPos, screenMat);

	Vector3 screenPos;
	XMStoreFloat3(&screenPos.m_vector, vPos);

	return screenPos;
}


/**
* @brief	ワールド座標計算
* @param	screenPos	スクリーン座標
* @return	Vector3		ワールド座標
*/
Vector3 CCamera::CalcWorldPos(Vector3 screenPos)
{
	XMVECTOR vPos = XMLoadFloat3(&screenPos.m_vector);
	XMMATRIX invView = XMMatrixInverse(nullptr, GetLookAtMatrix());
	XMMATRIX invProj = XMMatrixInverse(nullptr, GetProjectionMatrix());

	float halfW = m_screenSize.x * 0.5f;
	float halfH = m_screenSize.y * 0.5f;
	DirectX::XMMATRIX screenMat = DirectX::XMMatrixSet(
		halfW, 0.0f,   0.0f, 0.0f,
		0.0f,  -halfH, 0.0f, 0.0f,
		0.0f,  0.0f,   1.0f, 0.0f,
		halfW, halfH,  0.0f, 1.0f);
	DirectX::XMMATRIX invScreen = DirectX::XMMatrixInverse(nullptr, screenMat);

	vPos = XMVector3TransformCoord(vPos, invScreen);
	vPos = XMVector3TransformCoord(vPos, invProj);
	vPos = XMVector3TransformCoord(vPos, invProj);
	
	Vector3 worldPos;
	XMStoreFloat3(&worldPos.m_vector, vPos);

	return worldPos;
}