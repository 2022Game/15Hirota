#pragma once

// Task�̗D�揇��
enum class ETaskPriority
{
	eNone = -1,

	// 3D�֘A
	eBackground,// �w�i
	eDefault,	// �f�t�H���g
	ePlayer,	// �v���C���[

	eEffect,	// �G�t�F�N�g

	eCamera,	// �J����

	// 2D�֘A
	eUI,		// UI�֘A�̃f�t�H���g
	eSystem,	// �V�X�e���֘A
	eDebug,		// �f�o�b�O�֘A

	Num,

	// 2D�֘A�̃^�X�N�̊J�n�ʒu
	Start2d = eUI,
};