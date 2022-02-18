#pragma once
/**
*
* @file		CRenderer.h
* @brief	�`��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/04	�����J�n
*
*/

/** �C���N���[�h�� */
#include <System/Component/CComponent.h>
#include <System/Defines.h>

class CTransform;
/** �`��N���X */
class CRenderer : public CComponent
{
public:
	CRenderer();
	virtual ~CRenderer();

	void OnCreate()		override;
	void OnDestroy()	override;
	void Update()		override;
	virtual void Draw(ID3D11DeviceContext* pDC) {}

protected:
	std::weak_ptr<CTransform> m_spTransform;
};