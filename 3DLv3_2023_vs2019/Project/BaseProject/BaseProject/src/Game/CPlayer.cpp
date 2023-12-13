//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
#include "CInput.h"
#include "CCamera.h"
#include "CUiGauge.h"
#include "CStaminaGauge.h"
#include "Maths.h"
#include "CSceneManager.h"
#include "CMajicSword.h"
#include "CBullet.h"

//// �v���C���[�̃��f���f�[�^�̃p�X
//#define MODEL_PATH "Character\\Monster1\\Monster_1.x"

// �v���C���[�֘A
#define PLAYER_HEIGHT 16.0f		// ����
#define MOVE_SPEED 0.9f			// �X�s�[�h
#define RUN_SPEED 1.3f			// �ړ��X�s�[�h
#define JUMP_SPEED 1.5f			// �W�����v
#define GRAVITY 0.0625f			// �d��
#define JUMP_END_Y 1.0f			// �W�����v�I����

#define FOV_ANGLE 45.0f			//����̊p�x(�[�p�x+�p�x���o)
#define FOV_LENGTH 5.0f			//����̊p�x

// HP�֘A
#define HP 100

// ���x���֘A
#define LEVEL 1

// �X�^�~�i�֘A
#define STAMINA 109

// �v���C���[�̃C���X�^���X
CPlayer* CPlayer::spInstance = nullptr;


// �v���C���[�̃A�j���[�V�����f�[�^�̃e�[�u��
const CPlayer::AnimData CPlayer::ANIM_DATA[] =
{
	{ "",														true,	0.0f	},	// T�|�[�Y
	{ "Character\\Monster1\\anim\\Warrok_Idle.x",				true,	854.0f	},	// �ҋ@
	{ "Character\\Monster1\\anim\\Warrok_Walking.x",			true,	86.0f	},	// �_�b�V��
	{ "Character\\Monster1\\anim\\Warrok_Punchi.x",				false,	67.0f	},	// �U��
	{ "Character\\Monster1\\anim\\Warrok_StrongAttack.x",		false,	161.0f	},	// ���U��
	{ "Character\\Monster1\\anim\\jump_start.x",				false,	25.0f	},	// �W�����v�J�n
	{ "Character\\Monster1\\anim\\jump.x",						true,	1.0f	},	// �W�����v��
	{ "Character\\Monster1\\anim\\jump_end.x",					false,	26.0f	},	// �W�����v�I��
	{ "Character\\Monster1\\anim\\Warrok_Run.x",				true,	53.0f	},	// ���s
	{ "Character\\Monster1\\anim\\Warrok_RunStop.x",			false,	90.0f	},	// �_�b�V���I��
	{ "Character\\Monster1\\anim\\Rotate.x",					false,	71.0f	},	// ���
	{ "Character\\Monster1\\anim\\Guts pose_325.x",				false,	325.0f	},	// �K�b�c�|�[�Y
	{ "Character\\Monster1\\anim\\Deth_276.x",					false,	276.0f	},	// ���S

};

// �R���X�g���N�^
CPlayer::CPlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mPosition(0.0f,0.0f,0.0f)//0.0f, 60.0f, -30.0f
	, mpRideObject(nullptr)
	, staminaDepleted(false)
	, staminaLowerLimit(false)
	, damageObject(false)
	, mLife(50)
{
	SetColor(CColor(1.0, 0.0, 0.0, 1.0));
	// HP�Q�[�W���쐬
	mpHpGauge = new CUIGauge();
	// �X�^�~�i�Q�[�W���쐬
	mpStaminaGauge = new CStaminaGauge();

	// �C���X�^���X�̐ݒ�
	spInstance = this;

	// ���f���f�[�^�擾
	CModelX* model = CResourceManager::Get<CModelX>("Player");

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

	// �c�̃R���C�_�[���C��
	mpColliderLine = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f)
	);
	/*const CMatrix* speneMtxL = GetFrameMtx("Armature_mixamorig_Spine1");
	mpColliderLine->SetAttachMtx(speneMtxL);*/
	mpColliderLine->SetCollisionLayers({ ELayer::eField,ELayer::eDamageObject });


	// �O��̃R���C�_�[���C��
	mpColliderLine_2 = new CColliderLine
	(
		this, ELayer::eField,
		CVector(0.0f, 8.0f, -8.0f),
		CVector(0.0f, 8.0f, 8.0f)
	);
	mpColliderLine_2->SetCollisionLayers({ ELayer::eFieldWall });


	// ���̃R���C�_�[���C��
	mpColliderLine_3 = new CColliderLine
	(
		this, ELayer::eField,
		CVector(8.0f, 8.0f, 0.0f),
		CVector(-8.0f, 8.0f, 0.0f)
	);
	mpColliderLine_3->SetCollisionLayers({ ELayer::eFieldWall });


	// �_���[�W���󂯂�R���C�_�[���쐬
	mpDamageCol = new CColliderSphere
	(
		this, ELayer::eDamageCol,
		0.5f//0.5f
	);
	// �_���[�W���󂯂�R���C�_�[��
	// �Փ˔�����s���R���C�_�[�̃��C���[�ƃ^�O��ݒ�
	mpDamageCol->SetCollisionLayers({ ELayer::eAttackCol,ELayer::eGoalCol });
	mpDamageCol->SetCollisionTags({ ETag::eEnemyWeapon,ETag::eGoalObject });
	// �_���[�W���󂯂�R���C�_�[��������ւ��炷
	mpDamageCol->Position(0.0f, 0.0f, 0.0f);
	const CMatrix* spineMtx = GetFrameMtx("Armature_mixamorig_Spine1");
	mpDamageCol->SetAttachMtx(spineMtx);


	mpSword = new CMajicSword();
	mpSword->AttachMtx(GetFrameMtx("Armature_mixamorig_RightHand"));
	mpSword->SetOwner(this);

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

	if (mpColliderLine_2 != nullptr)
	{
		delete mpColliderLine_2;
		mpColliderLine_2 = nullptr;
	}

	if (mpColliderLine_3 != nullptr)
	{
		delete mpColliderLine_3;
		mpColliderLine_3 = nullptr;
	}

	if (mpDamageCol != nullptr)
	{
		delete mpDamageCol;
		mpDamageCol = nullptr;
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
	mpStaminaGauge->SetSutaminaMaxValue(mCharaMaxStatus.stamina);
	mpStaminaGauge->SetSutaminaValue(mCharaStatus.stamina);
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
	mpDamageCol->SetEnable(true);
	bool KeyPush = (CInput::Key('W') || CInput::Key('A') || CInput::Key('S') || CInput::Key('D'));

	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	
	if (mIsGrounded)
	{
		// �ړ�����
		// �L�[�̓��̓x�N�g�����擾
		CVector input;
		if (CInput::Key('W'))		input.Z(-1.0f);
		else if (CInput::Key('S'))	input.Z(1.0f);
		if (CInput::Key('A'))		input.X(-1.0f);
		else if (CInput::Key('D'))	input.X(1.0f);

		// ���̓x�N�g���̒����œ��͂���Ă��邩����
		if (input.LengthSqr() > 0.0f)
		{
			// �J�����̌����ɍ��킹���ړ��x�N�g���ɕϊ�
			CVector move = CCamera::MainCamera()->Rotation() * input;
			move.Y(0.0f);
			move.Normalize();

			float speed = MOVE_SPEED;
			if (CInput::Key(VK_SHIFT) && KeyPush)
			{
				if ((mCharaStatus.stamina > 0 && !staminaLowerLimit))
				{
					// ���x�𑖍s���x�ɕύX
					speed = RUN_SPEED;
					mCharaStatus.stamina -= 1;
					ChangeAnimation(EAnimType::eDash);

					if (mCharaStatus.stamina == 0)
					{
						staminaLowerLimit = true;
						mState = EState::eDashEnd;
					}
				}
				else
				{
					if (staminaLowerLimit && mCharaStatus.stamina == mCharaMaxStatus.stamina)
					{
						staminaLowerLimit = false; // �X�^�~�i���Ă�MAX�ɂȂ����烊�Z�b�g
					}
					mCharaStatus.stamina += 1;
					ChangeAnimation(EAnimType::eWalk);
				}
			}
			else
			{
				if (mCharaStatus.stamina < mCharaMaxStatus.stamina && !staminaDepleted)
				{
					mCharaStatus.stamina += 1;
				}
				else if (mCharaStatus.stamina >= mCharaMaxStatus.stamina)
				{
					staminaDepleted = false;  // �X�^�~�i������l����ɂȂ����烊�Z�b�g
				}

				ChangeAnimation(EAnimType::eWalk);
			}
			mMoveSpeed += move * speed * MOVE_SPEED * mCharaStatus.moveSpeed;
		}
		// �ړ��L�[����͂��Ă��Ȃ�
		else
		{
			// �ҋ@�A�j���[�V�����ɐ؂�ւ�
			ChangeAnimation(EAnimType::eIdle);
			if (mCharaStatus.stamina < mCharaMaxStatus.stamina && !staminaDepleted)
			{
				mCharaStatus.stamina += 1;
			}
			else if (mCharaStatus.stamina >= mCharaMaxStatus.stamina)
			{
				staminaDepleted = false;  //  �X�^�~�i������l����ɂȂ����烊�Z�b�g
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
			if (mCharaStatus.stamina - 20 >= 0)
			{
				mState = EState::eJumpStart;
				// �X�^�~�i��0�ȉ��ɂȂ�Ȃ��ꍇ�̓W�����v�����s
				mCharaStatus.stamina -= 20;
			}
			else
			{
			}
		}
		// Q,E�L�[�ŉ���ֈڍs
		else if (((CInput::PushKey('Q') || CInput::PushKey('E')) && KeyPush) && (mCharaStatus.stamina <= mCharaMaxStatus.stamina))
		{
			// ����s���O�ɃX�^�~�i��0�ȉ��ɂȂ邩�ǂ������m�F
			if (mCharaStatus.stamina - 50 >= 0) {

				mState = EState::eRotate;
				// �X�^�~�i��0�ȉ��ɂȂ�Ȃ��ꍇ�͉���s�������s
				mCharaStatus.stamina -= 50;
			}
			else 
			{
			}
		}
	}
	else
	{
		if (mCharaStatus.stamina < mCharaMaxStatus.stamina)
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
	// ���ɍU���J�n��`����
	mpSword->AttackStart();
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
	mState = EState::eAttackWait2;
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

		// ���ɍU���I����`����
		mpSword->AttackEnd();
	}
}

// �U���I���҂�2
void CPlayer::UpdateAttackWait2()
{
	if (IsAnimationFinished())
	{
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

// �N���A
void CPlayer::UpdateClear()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eGuts);
	mState = EState::eClearEnd;
}

// �N���A�I��
void CPlayer::UpdateClearEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
		Position(0.0f,0.0f,-30.0f);
	}
}

// ���S
void CPlayer::UpdateDeth()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);
	ChangeAnimation(EAnimType::eDeth);
	if (IsAnimationFinished())
	{
		mState = EState::eDethEnd;
	}
}

// ���S�����I��
void CPlayer::UpdateDethEnd()
{
	if (IsAnimationFinished())
	{
		mCharaStatus = mCharaMaxStatus;
		Position(0.0f, 0.0f, -30.0f);
		mState = EState::eIdle;
	}
}

// �ċN
void CPlayer::UpdateReStart()
{
	if (IsAnimationFinished())
	{
		damageObject = false;
		Position(0.0f, 10.0f, -30.0f);
		mState = EState::eIdle;
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
		// �U���I���҂�2
		case EState::eAttackWait2:
			UpdateAttackWait2();
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
		// �N���A
		case EState::eClear:
			UpdateClear();
			break;
		// �N���A�I��
		case EState::eClearEnd:
			UpdateClearEnd();
			break;
		// ���S
		case EState::eDeth:
			UpdateDeth();
			break;
		// ���S�����I��
		case EState::eDethEnd:
			UpdateDethEnd();
			break;
		// �ċN
		case EState::eReStart:
			UpdateReStart();
			break;
	}

	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// �ړ�
	Position(Position() + mMoveSpeed * 60.0f * Time::DeltaTime());

	// �v���C���[���ړ������֌�����
	CVector current = VectorZ();
	CVector target = mMoveSpeed;
	target.Y(0.0f);
	target.Normalize();
	CVector forward = CVector::Slerp(current, target, 0.125f);
	Rotation(CQuaternion::LookRotation(forward));

	// ���G���̓J�E���g������������
	if (mInvincible > 0)
	{
		// ���Z
		mInvincible--;
	}

	// �L�����N�^�[�̃f�o�b�O�\��
	static bool debug = false;
	if (CInput::PushKey('R'))
	{
		debug = !debug;
	}
	if (debug)
	{
		//CDebugPrint::Print(" ���x�� %d\n", mCharaMaxStatus.level);
		CDebugPrint::Print(" HP%d / %d\n", mCharaStatus.hp, mCharaMaxStatus.hp);
		CDebugPrint::Print(" �U���l%d\n", mCharaStatus.power);
		CDebugPrint::Print(" ST%d / %d\n", mCharaStatus.stamina, mCharaMaxStatus.stamina);
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
	mpStaminaGauge->SetSutaminaValue(mCharaStatus.stamina);

	// �L�����N�^�[�̍X�V
	CXCharacter::Update();
	mpDamageCol->Update();

	mIsGrounded = false;
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
		else if (other->Layer() == ELayer::eDamageObject)
		{
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
			mIsGrounded = true;

			if (other->Tag() == ETag::eRideableObject)
			{
				if (!damageObject)
				{
					mCharaStatus.hp -= 1;
					damageObject = true;
				}
				ChangeAnimation(EAnimType::eDeth);
				mpRideObject = other->Owner();
				mState = EState::eReStart;
			}
		}
	}

	if (self == mpColliderLine_2)
	{
		if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust); //+ hit.adjust * hit.weight

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
	}

	if (self == mpColliderLine_3)
	{
		if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust); //+ hit.adjust * hit.weight

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
	}

	if (self == mpDamageCol)
	{
		if (other->Layer() == ELayer::eGoalCol)
		{
			CDebugPrint::Print("Player hit GoalObject!\n");
			mpDamageCol->SetEnable(false);
			mState = EState::eClear;
		}
	}
}

// ��_���[�W����
void CPlayer::TakeDamage(int damage)
{
	//// ���S���Ă�����A�_���[�W�͎󂯂Ȃ�
	//if (mCharaStatus.hp <= 0)return;

	//// HP����_���[�W������
	//mCharaStatus.hp = max(mCharaStatus.hp - damage, 0);
	//mCharaStatus.hp -= damage;
	// HP��0�ɂȂ�����
	if (mCharaStatus.hp <= 0)
	{
		mState = EState::eDeth;
	}
}

// �`��
void CPlayer::Render()
{
	// �L�����`��
	CXCharacter::Render();
}