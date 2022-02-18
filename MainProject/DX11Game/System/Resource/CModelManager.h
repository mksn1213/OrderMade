#pragma once
/**
*
* @file		CModelManager.h
* @brief	���f���Ǘ��N���X
* @author	SHONOSUKE MAKITA
* @date		2021/12/03	�����J�n
* @date		2022/01/15	�V���O���g���p��
*
*/

/** �C���N���[�h�� */
#include <System/Renderer/AssimpModel.h>
#include <System/Resource/ModelTypeID.h>
#include <System/Utility/Singleton.h>

#define MODEL_MANAGER (CModelManager::GetInstance())

/** ���f���Ǘ��N���X */
class CModelManager :public Singleton<CModelManager>
{
public:
	// TODO : �K�v�Ȏ��Ɋe���f����ǂݍ��ނ悤�ɕύX����
	CModelManager();
	virtual ~CModelManager();

	HRESULT Init()		final;
	void	Uninit()	final;

	HRESULT LoadModelAll();
	void	ReleaseModelAll();

	/**
	* @brief	���f���̎擾
	* @param	type			���f���^�C�v
	* @return	CAssimpModel*	�擾���郂�f��
	*/
	CAssimpModel* GetModel(EModelType type) { return m_pModels[static_cast<int>(type)]; }
	
	/**
	* @brief	�����ς݂̃��f���ɃJ�����A���C�g���Z�b�g����
	* @param	camera		�Z�b�g����J����
	* @param	light		�Z�b�g���郉�C�g
	*/
	// TODO : ���f���𐶐������Ƃ��Ɉꏏ�ɃZ�b�g�ł���悤�ɕύX������
	//void SetCameraLight(CCamera* camera, CLight* light)
	//{
	//	for (int i = 0; i < static_cast<int>(EModelType::MaxModel); ++i)
	//	{
	//		m_pModels[i]->SetCamera(camera);
	//		m_pModels[i]->SetLight(light);
	//	}
	//}

private:
	CAssimpModel* m_pModels[static_cast<int>(EModelType::MaxModel)];
};