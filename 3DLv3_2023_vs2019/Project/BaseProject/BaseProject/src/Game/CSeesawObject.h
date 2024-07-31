#ifndef CSEESAWOBJECT_H
#define CSEESAWOBJECT_H

#include "CModel.h"
#include "CCollider.h"
#include "CObjectBase.h"

// �V�[�\�[�I�u�W�F�N�gBase
class CSeesawObject : public CObjectBase
{
public:
	CSeesawObject(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer, const float right, const float left,
		const float rotateRSpeed, const float rotateLSpeed);
	virtual ~CSeesawObject();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
	/// <summary>
	/// ���C�Ƃ̏Փ˔���
	/// </summary>
	/// <param name="start">���C�̊J�n�ʒu</param>
	/// <param name="end">���C�̏I���ʒu</param>
	/// <param name="hit">�Փˈʒu�ԋp�p</param>
	/// <returns></returns>
	bool CollisionRay(const CVector& start, const CVector& end, CHitInfo* hit) override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

protected:
	// ���f���E�f�ފ֘A
	// �V�[�\�[�I�u�W�F�N�g���f���f�[�^
	CModel* mpModel;
	// �V�[�\�[�I�u�W�F�N�g�̃R���C�_�[
	CCollider* mpCollider;

	// ��Ԋ֘A
	// �V�[�\�[�̏��
	enum class EState
	{
		eIdle,	// �ҋ@���
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	// �ҋ@��Ԃ̍X�V����
	void UpdateIdle();
	// ���݂̏��
	EState mState;

	// �x�N�g���֘A
	// �ʒu��ݒ肷��
	CVector mStartPos;
	// ������]�l
	CQuaternion mDeafaultRot;

	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// ��]�����p�x��ێ�����ϐ�
	float mRotationAngle;
	// ��]�J�n���̊p�x
	float mRotateStartAngle;
	// ��]�I�����̊p�x
	float mRotateEndAngle;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �E���̊p�x
	float mRight;
	// �����̊p�x
	float mLeft;
	// ��]�X�s�[�hR
	float mRotateRSpeed;
	// ��]�X�s�[�hL
	float mRotateLSpeed;
	// �v���C���[���V�[�\�[��̂ǂ���ɐG��Ă��邩
	float mHitDir;
	// �v���C���[���V�[�\�[�ɐG��Ă��邩�ǂ���
	bool mIsHitCol;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;
};
#endif