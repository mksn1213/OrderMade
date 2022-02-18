#pragma once
/**
* @enum		EModelType
* @brief	���f���^�C�v
*/
enum class EModelType
{
	Player = 0,		// �v���C���[
	TargetPoint,	// �v���C���[�̃^�[�Q�b�g�|�C���g
	Wall,			// ��
	SeedBox,		// �픠
	Soil,			// �y
	Well,			// ���
	ClayBox,		// �S�y��
	FertilizerBagC,	// �엿��(�V�A��)
	FertilizerBagM,	// �엿��(�}�[���^)
	FertilizerBagY,	// �엿��(�C�G���[)

	ShipGate,		// �o�׃Q�[�g
	ShipTruck,		// �o�׃g���b�N
	Oven,			// �}
	PotteryWheel,	// �{�
	Wheel,			// ��]��

	Seed,			// ��
	Bucket,			// �o�P�c
	Sprout_W,		// ��(��)
	Sprout_C,		// ��(�V�A��)
	Sprout_M,		// ��(�}�[���^)
	Sprout_Y,		// ��(�C�G���[)
	Sprout_R,		// ��(��)
	Sprout_G,		// ��(��)
	Sprout_B,		// ��(��)

	Flower_W,		// ��(��)
	Flower_C,		// ��(�V�A��)
	Flower_M,		// ��(�}�[���^)
	Flower_Y,		// ��(�C�G���[)
	Flower_R,		// ��(��)
	Flower_G,		// ��(��)
	Flower_B,		// ��(��)

	Clay,			// �S�y
	TrimClay,		// ���H��S�y
	Potted,			// ���A��
	FertilizerC,	// �엿(�V�A��)
	FertilizerM,	// �엿(�}�[���^)
	FertilizerY,	// �엿(�C�G���[)
	TrashBox,		// ���ݔ�

	Bonfire,		// ����
	Fence1,			// �t�F���X
	FlowerBed,		// �Ԓd
	StackedStraw,	// �m
	Stump,			// �؂芔
	Tree1,			// ��1
	Tree2,			// ��2

	MaxModel
};

