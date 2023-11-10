//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
#include "CInput.h"
#include "CCamera.h"
#include "CUiGauge.h"
#include "Maths.h"
#include "CSceneManager.h"

// �v���C���[�̃��f���f�[�^�̃p�X
#define MODEL_PATH "Character\\Monster1\\Monster_1.x"

// �v���C���[�֘A
#define PLAYER_HEIGHT 16.0f		// ����
#define MOVE_SPEED 1.0f			// �X�s�[�h
#define RUN_SPEED 0.05f			// �ړ��X�s�[�h
#define JUMP_SPEED 1.5f			// �W�����v
#define GRAVITY 0.0625f			// �d��
#define JUMP_END_Y 1.0f			// �W�����v�I����

// HP�֘A
#define HP 100

// ���x���֘A
#define LEVEL 1

// �X�^�~�i�֘A
#define STAMINA 100

// �v���C���[�̃C���X�^���X
CPlayer* CPlayer::spInstance = nullptr;


// �v���C���[�̃A�j���[�V�����f�[�^�̃e�[�u��
const CPlayer::AnimData CPlayer::ANIM_DATA[] =
{
	{ "",														true,	0.0f	},	// T�|�[�Y
	{ "Character\\Monster1\\anim\\Warrok_Idle.x",				true,	854.0f	},	// �ҋ@
	{ "Character\\Monster1\\anim\\Warrok_Walking.x",			true,	86.0f	},	// �_�b�V��
	{ "Character\\Monster1\\anim\\attack.x",					false,	91.0f	},	// �U��
	{ "Character\\Monster1\\anim\\Warrok_StrongAttack.x",		false,	161.0f	},	// ���U��
	{ "Character\\Monster1\\anim\\jump_start.x",				false,	25.0f	},	// �W�����v�J�n
	{ "Character\\Monster1\\anim\\jump.x",						true,	1.0f	},	// �W�����v��
	{ "Character\\Monster1\\anim\\jump_end.x",					false,	26.0f	},	// �W�����v�I��
	{ "Character\\Monster1\\anim\\Warrok_Run.x",				true,	53.0f	},	// ���s
	{ "Character\\Monster1\\anim\\Warrok_RunStop.x",			false,	90.0f	},	// �_�b�V���I��
	{ "Character\\Monster1\\anim\\Rotate.x",					false,	71.0f	},	// ���

};

// �R���X�g���N�^
CPlayer::CPlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mpRideObject(nullptr)
	, staminaDepleted(false)
{
	//mCharaStatus.hp = PLAYER_STATUS[0].hp; // ���x��1�̏���HP��ݒ�


	//�C���X�^���X�̐ݒ�
	spInstance = this;

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

	// HP�Q�[�W���쐬
	mpHpGauge = new CUIGauge();
	// �X�^�~�i�Q�[�W���쐬
	mpStaminaGauge = new CUIGauge();


	// �ŏ���1���x���ɐݒ�
	ChangeLevel(1);
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

// hp�擾
int CPlayer::GetHp()
{
	return mCharaStatus.hp;
}

// �ő�hp�擾
int CPlayer::GetMaxHp()
{
	return mCharaMaxStatus.hp;
}

// ���x���A�b�v
void CPlayer::LevelUp()
{
	int level = mCharaStatus.level;
	ChangeLevel(level + 1);
}

// ���x����ύX
void CPlayer::ChangeLevel(int level)
{
	// �X�e�[�^�X�̃e�[�u���̃C���f�b�N�X�l�ɕϊ�
	int index = Math::Clamp(level - 1, 0, PLAYER_LEVEL_MAX);
	// �ő�X�e�[�^�X�ɐݒ�
	mCharaMaxStatus = PLAYER_STATUS[index];
	// ���݂̃X�e�[�^�X���ő�l�ɂ��邱�ƂŁAHP����
	mCharaStatus = mCharaMaxStatus;

	// �ő�HP�ƌ���HP��HP�Q�[�W�ɔ��f
	mpHpGauge->SetMaxValue(mCharaMaxStatus.hp);
	mpHpGauge->SetValue(mCharaStatus.hp);

	// �ő�X�^�~�i�ƌ��݃X�^�~�i���X�^�~�i�Q�[�W�ɔ��f
	mpStaminaGauge->SetMaxValue(mCharaMaxStatus.stamina);
	mpStaminaGauge->SetValue(mCharaStatus.stamina);
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

			if (CInput::Key(VK_SHIFT) && KeyPush)
			{
				if (mCharaStatus.stamina > 0 || staminaDepleted)
				{
					mCharaStatus.stamina -= 1;
					ChangeAnimation(EAnimType::eDash);
					if (mCharaStatus.stamina == 0)
					{
						mState = EState::eDashEnd;
						//staminaDepleted = true;
					}
				}
			}
			else
			{
				if (mCharaStatus.stamina < 100 && !staminaDepleted)
				{
					mCharaStatus.stamina += 1;
				}
				else if (mCharaStatus.stamina >= 100)
				{
					staminaDepleted = false;  // �X�^�~�i��100�ȏ�ɂȂ�����t���O�����Z�b�g
				}
				ChangeAnimation(EAnimType::eWalk);
			}
			mMoveSpeed += move * MOVE_SPEED * mCharaStatus.moveSpeed;
		}
		// �ړ��L�[����͂��Ă��Ȃ�
		else
		{
			// �ҋ@�A�j���[�V�����ɐ؂�ւ�
			ChangeAnimation(EAnimType::eIdle);
			if (mCharaStatus.stamina < 100 && !staminaDepleted)
			{
				mCharaStatus.stamina += 1;
			}
			else if (mCharaStatus.stamina >= 100)
			{
				staminaDepleted = false;  // �X�^�~�i��100�ȏ�ɂȂ�����t���O�����Z�b�g
			}
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
		// Q,E�L�[�ŉ���ֈڍs
		else if (((CInput::PushKey('Q') || CInput::PushKey('E')) && KeyPush))
		{
			mState = EState::eRotate;
		}
	}
	else
	{
		if (mCharaStatus.stamina < 100)
		{
			mCharaStatus.stamina += 1;
		}
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

// �_�b�V���I��
void CPlayer::UpdateDashEnd()
{
	mMoveSpeed.Z(0.0f);
	mMoveSpeed.X(0.0f);
	ChangeAnimation(EAnimType::eDashStop);
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
		// ����J�n
		case EState::eRotate:
			UpdateRotate();
			break;
		// ����I��
		case EState::eRotateEnd:
			UpdateRotateEnd();
			break;
		// �_�b�V���I��
		case EState::eDashEnd:
			UpdateDashEnd();
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

	mIsGrounded = false;

	// ���G���̓J�E���g������������
	if (mInvincible > 0)
	{
		// ���Z
		mInvincible--;
	}

	// �L�����N�^�[�̃f�o�b�O�\��
	static bool debug = false;
	if (CInput::PushKey('T'))
	{
		debug = !debug;
	}
	if (debug)
	{
		//CDebugPrint::Print(" ���x�� %d\n", mCharaMaxStatus.level);
		CDebugPrint::Print(" HP%d / %d\n", mCharaStatus.hp, mCharaMaxStatus.hp);
		CDebugPrint::Print(" �U���l%d\n", mCharaStatus.power);
		CDebugPrint::Print(" �X�^�~�i%d / %d\n", mCharaStatus.stamina, mCharaMaxStatus.stamina);
	}
	// 1�L�[�������Ȃ���A�� �� ��HP����
	if (CInput::Key('1'))
	{
		if (CInput::PushKey(VK_UP)) mCharaStatus.hp++;
		else if (CInput::PushKey(VK_DOWN)) mCharaStatus.hp--;
	}
	else if (CInput::Key('2'))
	{
		LevelUp();
	}
	// ���݂�HP��ݒ�
	mpHpGauge->SetValue(mCharaStatus.hp);
	// ���݂̃X�^�~�i��ݒ�
	mpStaminaGauge->SetValue(mCharaStatus.stamina);

	// �L�����N�^�[�̍X�V
	CXCharacter::Update();
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
	// �L�����`��
	CXCharacter::Render();
}