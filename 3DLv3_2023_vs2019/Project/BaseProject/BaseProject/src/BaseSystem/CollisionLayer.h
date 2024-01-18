#pragma once
#include <initializer_list>

// �Փ˔��背�C���[
enum class ELayer
{
	eNone = -1,
	eTest,

	eField,
	eFieldWall,
	eFieldEnemyWall,

	eEffect,
	ePlayer,
	eEnemy,

	eVarious,		// �F�X�R���C�_�[
	eRecoverCol,	// �񕜃R���C�_�[
	eInvincbleCol,	// ���G�R���C�_�[
	eAttackCol,		// �U����^���鎞�̃R���C�_�[
	eBulletCol,		// �e�̃R���C�_�[
	eKickCol,		// �L�b�N�R���C�_�[
	eDamageCol,		// �_���[�W���󂯂鎞�̃R���C�_�[
	eJumpingCol,	// �W�����v������R���C�_�[
	eFallingCol,	// �����u���b�N�R���C�_�[
	eGoalCol,		// �S�[���̃R���C�_�[
	eDamageObject,	// �_���[�W��^����R���C�_�[
	eBlockCol,// �u���b�N�̃R���C�_�[
};
// �Փ˔��背�C���[�̏��������X�g
using Layers = std::initializer_list<ELayer>;
