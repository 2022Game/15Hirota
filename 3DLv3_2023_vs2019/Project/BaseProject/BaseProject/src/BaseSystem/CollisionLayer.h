#pragma once
#include <initializer_list>

// �Փ˔��背�C���[
enum class ELayer
{
	eNone = -1,
	eTest,

	eField,
	eGoalCol,	// �S�[���̃R���C�_�[

	eEffect,
	ePlayer,
	eEnemy,

	eAttackCol,	// �U����^���鎞�̃R���C�_�[
	eDamageCol,	// �_���[�W���󂯂鎞�̃R���C�_�[
};
// �Փ˔��背�C���[�̏��������X�g
using Layers = std::initializer_list<ELayer>;
