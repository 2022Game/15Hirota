#pragma once

//Task�̗D�揇��
enum class TaskPriority
{
	eNone = -1,

	eBackground,//�w�i
	eDefault,	//�f�t�H���g
	ePlayer,	//�v���C���[

	eEffect,	//�G�t�F�N�g

	eUI,		//UI�֘A
	eSystem,	//�V�X�e���֘A

	Num
};