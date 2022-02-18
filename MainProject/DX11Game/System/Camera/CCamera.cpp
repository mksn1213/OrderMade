/**
*
* @file		CCamera.h
* @brief	�J�����N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	�����J�n
* @date		2022/01/21	�J�����}�l�[�W���[���쐬
*
*/

/** �C���N���[�h */
#include <System/Camera/CCamera.h>
#include <System/Component/CTransform.h>
#include <System/CInput.h>

/** �}�N����` */
namespace
{
	const float		NEAR_CLIP	= 10.0f;							// �j�A�N���b�v
	const float		FAR_CLIP	= 1000.0f;							// �t�@�[�N���b�v
	const float		VIEW_ANGLE	= 45.0f;							// ����p
	const Vector3	REL_POS		= Vector3(0.0f, 100.0f, -100.0f);	// ���f�����΃J�����ʒu
	const Vector3	REL_TARGET	= Vector3(0.0f, 10.0f, 10.0f);		// ���f�����Β����_�ʒu

}

/**
* @brief	�R���X�g���N�^
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
* @brief	�f�X�g���N�^
*/
CCamera::~CCamera()
{

}


/**
* @brief	�v���W�F�N�V�����s��v�Z
* @return	XMMATRIX	�v�Z�����s��
*/
XMMATRIX CCamera::CalcProjection()
{
	return XMMatrixPerspectiveFovLH(m_fFov, GetAspect(), m_fNearClip, m_fFarClip);
}


/**
* @brief	�X�V����
*/
void CCamera::Update()
{
	// �Ώۂ�ǂ����ǂ���
	if (m_bChase)
	{
		// �^�[�Q�b�g�����݂���ꍇ
		if (m_spTargetTrans.lock())
		{
			auto pos = m_spTargetTrans.lock()->GetPosition();
			// ���_�Ɉړ��ʂ����Z
			m_pos->x = m_pos->x * 0.9f + (pos->x + REL_POS.m_vector.x) * 0.1f;
			m_pos->y = m_pos->y * 0.9f + (pos->y + REL_POS.m_vector.y) * 0.1f;
			m_pos->z = m_pos->z * 0.9f + (pos->z + REL_POS.m_vector.z) * 0.1f;

			// �����_�Ɉړ��ʂ����Z
			m_look->x = m_look->x * 0.9f + (pos->x + REL_TARGET.m_vector.x) * 0.1f;
			m_look->y = m_look->y * 0.9f + (pos->y + REL_TARGET.m_vector.y) * 0.1f;
			m_look->z = m_look->z * 0.9f + (pos->z + REL_TARGET.m_vector.z) * 0.1f;
		}
	}

	// �r���[�s��
	m_lookAtMatrix = XMMatrixLookAtLH(
		XMLoadFloat3(&m_pos.m_vector),
		XMLoadFloat3(&m_look.m_vector),
		XMLoadFloat3(&m_up.m_vector));

	// �v���W�F�N�V�����s��
	m_projectionMatrix = CalcProjection();
	XMStoreFloat4x4(&m_lookAt, m_lookAtMatrix);
	XMStoreFloat4x4(&m_projection, m_projectionMatrix);
}


/**
* @brief	�X�N���[�����W�v�Z
* @param	worldPos	���[���h���W
* @return	Vector3		�X�N���[�����W
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
* @brief	���[���h���W�v�Z
* @param	screenPos	�X�N���[�����W
* @return	Vector3		���[���h���W
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