#pragma once
#include <initializer_list>

// �Փ˔��背�C���[
enum class ELayer
{
	eNone = -1,
	eTest,

	eField,
	ePlayer,

	eGoalCol,	// �S�[���̃R���C�_�[
	eDamageCol,	// �_���[�W���󂯂鎞�̃R���C�_�[
	eAttackCol,	// �U����^���鎞�̃R���C�_�[
};
// �Փ˔��背�C���[�̏��������X�g
using Layers = std::initializer_list<ELayer>;
