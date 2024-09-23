#pragma once
#include <initializer_list>

// �I�u�W�F�N�g���ʗp�̃^�O
enum class ETag
{
	eNone = -1,

	eSky,				// ��

	eBullet,			// �e��
	eFlame,				// ��
	eSlash,				// �a��
	eBiribiri,			// �r���r��
	eSmoke,				// ��

	eSeesaw,			// �V�[�\�[
	ePropeller,			// �v���y��
	eReflection,		// ���˂�����I�u�W�F�N�g
	eField,				// �t�B�[���h���\������I�u�W�F�N�g
	eStageMenuObject,	// �X�e�[�W���j���[�̃I�u�W�F�N�g
	eButton,			// �X�e�[�W�I���{�^��
	eObstacle,			// ��Q��
	eRideableObject,	// ��邱�Ƃ��ł���I�u�W�F�N�g
	eItemRecover,		// �񕜃A�C�e���̃I�u�W�F�N�g
	eItemInvincible,	// ���G�A�C�e��
	eAttackObject,		// �U���̓A�b�v���f��
	eMedal,				// ���_���A�C�e��
	eMeat,				// ���A�C�e��
	eGoalObject,		// �N���A�����̃I�u�W�F�N�g
	eSavePoint1,		// �Z�[�u�|�C���g
	eSavePoint2,		// �Z�[�u�|�C���g
	eJumpingObject,		// �W�����v����I�u�W�F�N�g
	eNeedleObject,		// �j�I�u�W�F�N�g
	eNumberObject,		// �񐔐����I�u�W�F�N�g
	eFall,				// ��������p�I�u�W�F�N�g
	eRingBeam,			// �����O�r�[���I�u�W�F�N�g

	ePlayer,			// �v���C���[
	eEnemy,				// �G�l�~�[
	eSoldier,

	eWeapon,			// �v���C���[�̕���
	eEnemyWeapon,		// �G�̕���

	eHealing,			// �񕜃G�t�F�N�g

	eBakuhatu,
	eGauge,
	eEnemyFrame,

	eEffect,	// �G�t�F�N�g
	eBillboard,	// �r���{�[�h�C���[�W

	eCamera,			// �J����

	Num
};
// �I�u�W�F�N�g���ʗp�̃^�O�̏��������X�g
using Tags = std::initializer_list<ETag>;