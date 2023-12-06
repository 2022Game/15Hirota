#include "CUnityChan.h"
#include "CCamera.h"

// �v���C���[�̃C���X�^���X
CUnityChan* CUnityChan::spInstance = nullptr;

//// �v���C���[�̃��f���f�[�^�̃p�X
//#define MODEL_PATH "Character\\UnityChan\\unitychan.x"

// �v���C���[�̃A�j���[�V�����f�[�^�̃e�[�u��
const CUnityChan::AnimData CUnityChan::ANIM_DATA[] =
{
	//{ "",										true,	0.0f	},	// T�|�[�Y
	{ "Character\\UnityChan\\anim1\\UnityChan_Animation_Pose1.x",		true,	25.0f	},	// �|�[�Y
};

#define PLAYER_HEIGHT 16.0f
#define MOVE_SPEED 1.0f
#define JUMP_SPEED 1.5f
#define GRAVITY 0.0625f
#define JUMP_END_Y 1.0f

// �R���X�g���N�^
CUnityChan::CUnityChan()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mpRideObject(nullptr)
{
	//�C���X�^���X�̐ݒ�
	spInstance = this;

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("UnityChan");

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

CUnityChan::~CUnityChan()
{
	if (mpColliderLine != nullptr)
	{
		delete mpColliderLine;
		mpColliderLine = nullptr;
	}
}

CUnityChan* CUnityChan::Instance()
{
	return spInstance;
}

// �A�j���[�V�����؂�ւ�
void CUnityChan::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// �ҋ@
void CUnityChan::UpdateIdle()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	//if (mIsGrounded)
	//{
	//	// �ړ�����
	//	// �L�[�̓��̓x�N�g�����擾
	//	CVector input;
	//	if (CInput::Key('W'))		input.Z(1.0f);
	//	else if (CInput::Key('S'))	input.Z(-1.0f);
	//	if (CInput::Key('A'))		input.X(-1.0f);
	//	else if (CInput::Key('D'))	input.X(1.0f);

	//	// ���̓x�N�g���̒����œ��͂���Ă��邩����
	//	if (input.LengthSqr() > 0.0f)
	//	{
	//		// �J�����̌����ɍ��킹���ړ��x�N�g���ɕϊ�
	//		CVector move = CCamera::MainCamera()->Rotation() * input;
	//		move.Y(0.0f);
	//		move.Normalize();

	//		mMoveSpeed += move * MOVE_SPEED;

	//		// ���s�A�j���[�V�����ɐ؂�ւ�
	//		ChangeAnimation(EAnimType::eWalk);
	//	}
	//	// �ړ��L�[����͂��Ă��Ȃ�
	//	else
	//	{
	//		// �ҋ@�A�j���[�V�����ɐ؂�ւ�
	//		ChangeAnimation(EAnimType::eIdle);
	//	}

	//	// ���N���b�N�ōU����Ԃֈڍs
	//	if (CInput::PushKey(VK_LBUTTON))
	//	{
	//		mMoveSpeed.X(0.0f);
	//		mMoveSpeed.Z(0.0f);
	//		mState = EState::eAttack;
	//	}
	//	// SPACE�L�[�ŃW�����v�J�n�ֈڍs
	//	else if (CInput::PushKey(VK_SPACE))
	//	{
	//		mState = EState::eJumpStart;
	//	}
	//}
	//else
	{
		// �ҋ@�A�j���[�V�����ɐ؂�ւ�
		ChangeAnimation(EAnimType::eIdle);
	}
}

// �U��
void CUnityChan::UpdateAttack()
{
	// �U���A�j���[�V�������J�n
	ChangeAnimation(EAnimType::eAttack);
	// �U���I���҂���Ԃֈڍs
	mState = EState::eAttackWait;
}

// �U���I���҂�
void CUnityChan::UpdateAttackWait()
{
	// �U���A�j���[�V�������I��������A
	if (IsAnimationFinished())
	{
		// �ҋ@��Ԃֈڍs
		mState = EState::eIdle;
		ChangeAnimation(EAnimType::eIdle);
	}
}

// �W�����v�J�n
void CUnityChan::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	mState = EState::eJump;

	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}

// �W�����v��
void CUnityChan::UpdateJump()
{
	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		mState = EState::eJumpEnd;
	}
}

// �W�����v�I��
void CUnityChan::UpdateJumpEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
	}
}

// �X�V
void CUnityChan::Update()
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
}

// �Փˏ���
void CUnityChan::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
void CUnityChan::Render()
{
	CXCharacter::Render();
}