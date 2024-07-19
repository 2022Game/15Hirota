#ifndef CTITLEPLAYER_H
#define CTITLEPLAYER_H

#include "CXCharacter.h"
#include "CColliderLine.h"

// �^�C�g���v���C���[�N���X
class CTitlePlayer : public CXCharacter
{
public:
	//�C���X�^���X�̃|�C���^�̎擾
	static CTitlePlayer* Instance();

	// �R���X�g���N�^
	CTitlePlayer();
	// �f�X�g���N�^
	~CTitlePlayer();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂�������̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �v���C���[�̃C���X�^���X
	static CTitlePlayer* spInstance;

	// �c�̃R���C�_�[���C��
	CColliderLine* mpColliderLine;

	// �������̏��
	void UpdateReady();
	// �ҋ@���
	void UpdateIdle();

	// �v���C���[�̏��
	enum class EState
	{
		eReady,				 // ������
		eIdle,				 // �ҋ@
	};
	// ���݂̏�Ԃ�؂�ւ�
	void ChangeState(EState state);
	// �v���C���[�̏��
	EState mState;
	CTransform* mpRideObject;

	// �A�j���[�V�����̎��
	enum class EAnimType
	{
		None = -1,

		eTPose,			// T�|�[�Y
		eIdle,			// �x�e

		Num
	};

	// �A�j���[�V�����؂�ւ�
	void ChangeAnimation(EAnimType type);

	// �A�j���[�V�����f�[�^
	struct AnimData
	{
		std::string path;	// �A�j���[�V�����f�[�^�̃p�X
		bool loop;			// ���[�v���邩�ǂ���
		float frameLength;	// �A�j���[�V�����̃t���[����
	};
	// �A�j���[�V�����f�[�^�̃e�[�u��
	static const AnimData ANIM_DATA[];

	CVector mGroundNormal;		// �ݒu���Ă���n�ʂ̖@��

	// ��ԓ��̃X�e�b�v
	int mStateStep;

	// �d�͂�W�����v�ɂ��Y���̈ړ����x
	float mMoveSpeedY;

	// �ڒn���Ă��邩�ǂ���
	bool mIsGrounded;
};
#endif