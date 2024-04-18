#pragma once
#include <initializer_list>

// �I�u�W�F�N�g���ʗp�̃^�O
enum class ETag
{
	eNone = -1,

	eField,				// �t�B�[���h���\������I�u�W�F�N�g
	eRideableObject,	// ��邱�Ƃ��ł���I�u�W�F�N�g
	eItemRecover,		// �񕜃A�C�e���̃I�u�W�F�N�g
	eItemInvincible,	// ���G�A�C�e��
	eAttackObject,		// �U���̓A�b�v���f��
	eMedal,				// ���_���A�C�e��
	eGoalObject,		// �N���A�����̃I�u�W�F�N�g
	eJumpingObject,		// �W�����v����I�u�W�F�N�g

	ePlayer,			// �v���C���[
	eEnemy,				// �G�l�~�[
	eSoldier,

	eWeapon,			// �v���C���[�̕���
	eEnemyWeapon,		// �G�̕���
	eBullet,			// �e��
	eFlame,				// ��
	eSlash,				// �a��

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
