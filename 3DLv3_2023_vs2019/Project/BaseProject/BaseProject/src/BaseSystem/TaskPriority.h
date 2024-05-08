#pragma once

// Task�̗D�揇��
enum class ETaskPriority
{
	eNone = -1,

	// �C�x���g�֘A
	eEvent,

	// 3D�֘A
	eDefault,		// �f�t�H���g
	eBackground,	// �w�i
	eObstacle,		// ��Q��
	ePlayer,		// �v���C���[
	eEnemy,			// �G�l�~�[

	eNumberFalling,	// �񐔂ŗ�������I�u�W�F�N�g
	eFall,			// ��������p�̃I�u�W�F�N�g
	eMedal,			// ���_���I�u�W�F�N�g
	eTransparent,	// �����I�u�W�F�N�g
	eFalling,		// �����I�u�W�F�N�g
	eRising,		// �㏸����I�u�W�F�N�g
	eHatenaOBJ,		// �n�e�i�u���b�N�I�u�W�F�N�g
	eNeedle,		// �j�I�u�W�F�N�g
	eRotate,		// ��]����I�u�W�F�N�g
	eEffect,
	eBillboard,		// �r���{�[�h�C���[�W
	eEnemyGauge,	// �G�l�~�[�̃Q�[�W
	eEnemyUi,		// �G�l�~�[��UI
	eItem,			// �A�C�e��
	eWeapon,		// �v���C���[����
	eEnemyWeapon,	// �G�̕���

	eCamera,		// �J����
	eLeteCamera,	// �J������̍X�V

	// 2D�֘A
	eUI,			// UI�֘A�̃f�t�H���g
	eFade,			// ��ʃt�F�[�h
	eSystem,		// �V�X�e���֘A
	eDebug,			// �f�o�b�O�֘A

	Num,

	// 2D�֘A�̃^�X�N�̊J�n�ʒu
	Start2d = eUI,
};