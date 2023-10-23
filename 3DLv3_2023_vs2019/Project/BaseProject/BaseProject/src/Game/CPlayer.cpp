//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
#include "CInput.h"
#include "CCamera.h"

// �v���C���[�̃C���X�^���X
CPlayer* CPlayer::spInstance = nullptr;

// HP
int CPlayer::sHP = 0;

int CPlayer::HP()
{
	return sHP;
}

// �v���C���[�̃��f���f�[�^�̃p�X
#define MODEL_PATH "Character\\Monster1\\Monster_1.x"
// HP�̏����l
#define HP 100;

// �v���C���[�̃A�j���[�V�����f�[�^�̃e�[�u��
const CPlayer::AnimData CPlayer::ANIM_DATA[] =
{
	{ "",												true,	0.0f	},	// T�|�[�Y
	{ "Character\\Player\\anim\\idle.x",				true,	153.0f	},	// �ҋ@
	{ "Character\\Player\\anim\\walk.x",				true,	66.0f	},	// ���s
	{ "Character\\Player\\anim\\attack.x",				false,	91.0f	},	// �U��
	{ "Character\\Player\\anim\\Attack_Strong.x",		false,	161.0f	},	// ���U��
	{ "Character\\Player\\anim\\jump_start.x",			false,	25.0f	},	// �W�����v�J�n
	{ "Character\\Player\\anim\\jump.x",				true,	1.0f	},	// �W�����v��
	{ "Character\\Player\\anim\\jump_end.x",			false,	26.0f	},	// �W�����v�I��
	{ "Character\\Player\\anim\\Dash.x",				true,	23.0f	},	// �_�b�V��
	{ "Character\\Player\\anim\\Dash_Stop.x",			false,	27.0f	},	// �_�b�V���I��
	{ "Character\\Player\\anim\\Rotate.x",				false,	71.0f	},	// ���
};

#define PLAYER_HEIGHT 16.0f
#define MOVE_SPEED 1.0f
#define JUMP_SPEED 1.5f
#define GRAVITY 0.0625f
#define JUMP_END_Y 1.0f

// �R���X�g���N�^
CPlayer::CPlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mpRideObject(nullptr)
	, mRemainTime(50)
	, mInvincible(0)
{
	//�C���X�^���X�̐ݒ�
	spInstance = this;
	// HP
	sHP = HP;

	// ���f���f�[�^�ǂݍ���
	CModelX* model = new CModelX();
	model->Load(MODEL_PATH);

	// �e�[�u�����̃A�j���[�V�����f�[�^��ǂݍ���
	int size = ARRAY_SIZE(ANIM_DATA);
	for (int i = 0; i < size; i++)
	{
		const AnimData& data = ANIM_DATA[i];
		if (data.path.empty()) continue;
		model->AddAnimationSet(data.path.c_str());
	}
	// CXCharacter�̏�����
	Init(model);

	// �ŏ��͑ҋ@�A�j���[�V�������Đ�
	ChangeAnimation(EAnimType::eIdle);

	mpColliderLine = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField });
}

CPlayer::~CPlayer()
{
	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}

	if (mpModel != nullptr)
	{
		delete mpModel;
		mpModel = nullptr;
	}
}

CPlayer* CPlayer::Instance()
{
	return spInstance;
}

// �A�j���[�V�����؂�ւ�
void CPlayer::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// �ҋ@
void CPlayer::UpdateIdle()
{
	bool KeyPush = (CInput::Key('W') || CInput::Key('A') || CInput::Key('S') || CInput::Key('D'));

	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	
	if (mIsGrounded)
	{
		// �ړ�����
		// �L�[�̓��̓x�N�g�����擾
		CVector input;
		if (CInput::Key('W'))		input.Z(1.0f);
		else if (CInput::Key('S'))	input.Z(-1.0f);
		if (CInput::Key('A'))		input.X(-1.0f);
		else if (CInput::Key('D'))	input.X(1.0f);

		// ���̓x�N�g���̒����œ��͂���Ă��邩����
		if (input.LengthSqr() > 0.0f)
		{
			// �J�����̌����ɍ��킹���ړ��x�N�g���ɕϊ�
			CVector move = CCamera::MainCamera()->Rotation() * input;
			move.Y(0.0f);
			move.Normalize();

			mMoveSpeed += move * MOVE_SPEED;

			// ���s�A�j���[�V�����ɐ؂�ւ�
			ChangeAnimation(EAnimType::eWalk);
		}
		// �ړ��L�[����͂��Ă��Ȃ�
		else
		{
			// �ҋ@�A�j���[�V�����ɐ؂�ւ�
			ChangeAnimation(EAnimType::eIdle);
		}

		// J�L�[�ōU����Ԃֈڍs
		if (CInput::PushKey('J'))
		{
			mMoveSpeed.X(0.0f);
			mMoveSpeed.Z(0.0f);
			mState = EState::eAttack;
		}
		// K�L�[�ŋ��U��
		else if (CInput::PushKey('K'))
		{
			mMoveSpeed.X(0.0f);
			mMoveSpeed.Z(0.0f);
			mState = EState::eAttackStrong;
		}
		// SPACE�L�[�ŃW�����v�J�n�ֈڍs
		else if (CInput::PushKey(VK_SPACE))
		{
			mState = EState::eJumpStart;
		}
		// SHIFT�L�[�Ń_�b�V���J�n�ֈڍs
		else if (CInput::Key(VK_SHIFT) && KeyPush)
		{
			mMoveSpeed.Y(0.0f);
			mState = EState::eDashStart;
		}
		// Q,E�L�[�ŉ���ֈڍs
		else if ((CInput::PushKey('Q') || CInput::PushKey('E') && KeyPush) || mState == EState::eDash)
		{
			mState = EState::eRotate;
		}
	}
	else
	{
		// �ҋ@�A�j���[�V�����ɐ؂�ւ�
		ChangeAnimation(EAnimType::eIdle);
	}
}

// �U��
void CPlayer::UpdateAttack()
{
	// �U���A�j���[�V�������J�n
	ChangeAnimation(EAnimType::eAttack);
	// �U���I���҂���Ԃֈڍs
	mState = EState::eAttackWait;
}

// ���U��
void CPlayer::UpdateAttackStrong()
{
	// ���U���A�j���[�V�������J�n
	ChangeAnimation(EAnimType::eAttackStrong);
	// �U���I���҂���Ԃֈڍs
	mState = EState::eAttackWait;
}

// �U���I���҂�
void CPlayer::UpdateAttackWait()
{
	// �U���A�j���[�V�������I��������A
	if (IsAnimationFinished())
	{
		// �ҋ@��Ԃֈڍs
		mState = EState::eIdle;
		ChangeAnimation(EAnimType::eIdle);
	}
}

//�_�b�V���J�n
void CPlayer::UpdateDashStart()
{
	ChangeAnimation(EAnimType::eDash);
	mState = EState::eDash;
}

//�_�b�V����
void CPlayer::UpdateDash()
{
	//�ȗ�
	bool KeyPush = CInput::Key('W') || CInput::Key('A') || CInput::Key('S') || CInput::Key('D');
	// �_�b�V���̑��x�{����ݒ�
	const float dashSpeed = 0.5f; // �_�b�V�����x

	// �_�b�V�����̑��x�K�p
	// �ړ�����
	CVector input;
	if (mState == EState::eDash) {
		// WASD�L�[�̓��͂��Ď����A���x�{����K�p
		if (CInput::Key('W')) {
			input.Z(-1.0f);
		}
		if (CInput::Key('A')) {
			input.X(-1.0f);
		}
		if (CInput::Key('S')) {
			input.Z(1.0f);
		}
		if (CInput::Key('D')) {
			input.X(1.0f);
		}

		// ���̓x�N�g���𐳋K��
		if (input.Length() > 0.0f) {
			input.Normalize();
			input *= dashSpeed;
		}
	}

	// �ړ�����
	Position(Position() + mMoveSpeed + input);

	// �_�b�V���^�C������
	mRemainTime--;

	// ����
	if (mRemainTime <= 0 || !CInput::Key(VK_SHIFT) || input.Length() == 0.0f)
	{
		// �_�b�V���I���A�j���[�V����
		ChangeAnimation(EAnimType::eDashStop);
		mState = EState::eDashEnd;
	}
}

//�_�b�V���I��
void CPlayer::UpdateDashEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
		mRemainTime = 50;
	}
}

// �W�����v�J�n
void CPlayer::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	mState = EState::eJump;

	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}

// �W�����v��
void CPlayer::UpdateJump()
{
	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		mState = EState::eJumpEnd;
	}
}

// �W�����v�I��
void CPlayer::UpdateJumpEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
	}
}

//����J�n
void CPlayer::UpdateRotate()
{
	ChangeAnimation(EAnimType::eRotate);
	mState = EState::eRotateEnd;
}

//����I���҂�
void CPlayer::UpdateRotateEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
		ChangeAnimation(EAnimType::eIdle);
	}
}

// �X�V
void CPlayer::Update()
{
	SetParent(mpRideObject);
	mpRideObject = nullptr;

	// ��Ԃɍ��킹�āA�X�V������؂�ւ���
	switch (mState)
	{
		// �ҋ@���
		case EState::eIdle:
			UpdateIdle();
			break;
		// �U��
		case EState::eAttack:
			UpdateAttack();
			break;
		// ���U��
		case EState::eAttackStrong:
			UpdateAttackStrong();
			break;
		// �U���I���҂�
		case EState::eAttackWait:
			UpdateAttackWait();
			break;
		// �W�����v�J�n
		case EState::eJumpStart:
			UpdateJumpStart();
			break;
		// �W�����v��
		case EState::eJump:
			UpdateJump();
			break;
		// �W�����v�I��
		case EState::eJumpEnd:
			UpdateJumpEnd();
			break;
		//�_�b�V���J�n
		case EState::eDashStart:
			UpdateDashStart();
			break;
		//�_�b�V�����
		case EState::eDash:
			UpdateDash();
			break;
		//�_�b�V���I��
		case EState::eDashEnd:
			UpdateDashEnd();
			break;
		//����J�n
		case EState::eRotate:
			UpdateRotate();
			break;
		//����I��
		case EState::eRotateEnd:
			UpdateRotateEnd();
			break;
	}

	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// �ړ�
	Position(Position() + mMoveSpeed);

	// �v���C���[���ړ������֌�����
	CVector current = VectorZ();
	CVector target = mMoveSpeed;
	target.Y(0.0f);
	target.Normalize();
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));

	// �L�����N�^�[�̍X�V
	CXCharacter::Update();

	mIsGrounded = false;

	// ���G���̓J�E���g������������
	if (mInvincible > 0)
	{
		// ���Z
		mInvincible--;
	}
}

// �Փˏ���
void CPlayer::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	if (self == mpColliderLine)
	{
		if (other->Layer() == ELayer::eField)
		{
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
			mIsGrounded = true;

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
	}
}

// �`��
void CPlayer::Render()
{
	CXCharacter::Render();
}