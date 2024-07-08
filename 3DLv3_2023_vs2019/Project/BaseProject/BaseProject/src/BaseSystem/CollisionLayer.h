#pragma once
#include <initializer_list>

// �Փ˔��背�C���[
enum class ELayer
{
	eNone = -1,
	eTest,

	eField,
	eStageMenuObject,		// �X�e�[�W���j���[�̃I�u�W�F�N�g
	eFieldWall,
	eFieldEnemyWall,

	eClimb,					// �o���R���C�_�[
	eClimbedTop,			// �o���ǂ̒���R���C�_�[
	eWireClimb,				// �o�����ԃR���C�_�[
	eWireClimbedTop,		// �o�����Ԃ̒���R���C�_�[
	eWireMoveClimb,			// �o��铮�����ԃR���C�_�[
	eWireMoveClimbedTop,	// �o�����Ԃ̒���R���C�_�[
	eMetalLadder,			// ������q�̃R���C�_�[
	eMetalLadderTop,		// ������q�̒���R���C�_�[
	
	eFall,			// ��������p�̃R���C�_�[

	eEffect,
	ePlayer,
	eEnemy,


	eVarious,		// �F�X�R���C�_�[
	eSavePoint1,	// �Z�[�u�|�C���g�̃R���C�_�[
	eSavePoint2,	// �Z�[�u�|�C���g�̃R���C�_�[
	eFlame,			// ���̃R���C�_�[
	eSmoke,			// ���̃R���C�_�[
	eFlameWall,		// �Ή����ˊ�̃R���C�_�[
	eBiribiri,		// �r���r���R���C�_�[
	eRecoverCol,	// �񕜃R���C�_�[
	eInvincbleCol,	// ���G�R���C�_�[
	eMedalCol,		// ���_���R���C�_�[
	eMeatCol,		// ���R���C�_�[
	eAttackCol,		// �U����^���鎞�̃R���C�_�[
	eElectricCol,	// �d���R���C�_�[
	eBulletCol,		// �e�̃R���C�_�[
	eKickCol,		// �L�b�N�R���C�_�[
	eDamageCol,		// �_���[�W���󂯂鎞�̃R���C�_�[
	eJumpingCol,	// �W�����v������R���C�_�[
	eReflection,	// ���˃R���C�_�[
	eReflectionJump,// ���˃W�����v�R���C�_�[
	eFallingCol,	// �����u���b�N�R���C�_�[
	eGoalCol,		// �S�[���̃R���C�_�[
	eDamageObject,	// �_���[�W��^����R���C�_�[
	eBlockCol,		// �u���b�N�̃R���C�_�[
	eNeedleCol,		// �j�u���b�N�̃R���C�_�[
};
// �Փ˔��背�C���[�̏��������X�g
using Layers = std::initializer_list<ELayer>;
