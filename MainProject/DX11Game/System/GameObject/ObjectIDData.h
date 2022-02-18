#pragma once
/**
* @enum		EObjectType
* @brief	�I�u�W�F�N�g�^�C�v
*/
enum EObjectType
{

	//-----�Œ�I�u�W�F�N�g
	None = 0,			// �^�C�v�Ȃ�
	Soil,				// �y
	Table,				// �e�[�u��
	SeedBox,			// �픠
	Well,				// ���
	ClayBox,			// �S�y��
	FertilizerBagC,		// �엿��(�V�A��)
	FertilizerBagM,		// �엿��(�}�[���^)
	FertilizerBagY,		// �엿��(�C�G���[)
	ShipGate,			// �o�׃Q�[�g
	Oven,				// �}
	PotteryWheel,		// �{�
	TrashBox,			// ���ݔ�



	Wall = 20,			// ��



	//-----�A�C�e���I�u�W�F�N�g
	Seed = 50 ,			// ��
	Bucket,				// �o�P�c
	Sprout,				// ��
	Flower,				// ��
	Clay,				// �S�y
	Potted,				// ���A��
	FertilizerC,		// �엿(�V�A��)
	FertilizerM,		// �엿(�}�[���^)
	FertilizerY,		// �엿(�C�G���[)


	Player = 100,		// �v���C���[
	PlayerTarget,		// �v���C���[�^�[�Q�b�g

	//-----�z�u�p�I�u�W�F�N�g
	Bonfire = 1000,
	Fence1,
	FlowerBed,
	StackedStraw,
	Stump,
	Tree1,
	Tree2,

	MaxObjectType
};
