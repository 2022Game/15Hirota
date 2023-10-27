#include "CYukari.h"
#include "CCamera.h"
#include "CBillBoard.h"
#include "CImage.h"

// �v���C���[�̃C���X�^���X
CYukari* CYukari::spInstance = nullptr;

// �v���C���[�̃��f���f�[�^�̃p�X
#define MODEL_PATH "Character\\Yukari\\Yukari_Model.x"

// �v���C���[�̃A�j���[�V�����f�[�^�̃e�[�u��
const CYukari::AnimData CYukari::ANIM_DATA[] =
{
	{ "",										true,	0.0f	},	// T�|�[�Y
	{ "Character\\Yukari\\anim\\yukari_Playing.x",		true,	163.0f	},	// Idle��
};

#define PLAYER_HEIGHT 16.0f
#define MOVE_SPEED 1.0f
#define JUMP_SPEED 1.5f
#define GRAVITY 0.0625f
#define JUMP_END_Y 1.0f

// �R���X�g���N�^
CYukari::CYukari()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer)
	, mState(EState::eIdle)
	, mpRideObject(nullptr)
	, mbillboard(nullptr)
	, mbillboard1(nullptr)
{

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

	// �摜�ǂݍ���
	mbillboard = new CImage("UI\\Image_Gauge_Frame.png");
	mbillboard1 = new CImage("UI\\Gauge.png");
}

CYukari::~CYukari()
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

	if (mbillboard != nullptr)
	{
		delete mbillboard;
		mbillboard = nullptr;
	}

	if (mbillboard1 != nullptr)
	{
		delete mbillboard1;
		mbillboard1 = nullptr;
	}
}

CVector CYukari::GetHeadPosition() const
{
	// Yukari�̈ʒu�ɓ��̍����������ē���̈ʒu���v�Z
	CVector headPosition = Position();
	headPosition.Y(headPosition.Y() + PLAYER_HEIGHT);
	return headPosition;
}


CYukari* CYukari::Instance()
{
	return spInstance;
}

// �A�j���[�V�����؂�ւ�
void CYukari::ChangeAnimation(EAnimType type)
{
	if (type != EAnimType::eIdle) return;
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// �ҋ@
void CYukari::UpdateIdle()
{
	mMoveSpeed.X(0.0f);
	mMoveSpeed.Z(0.0f);

	{
		// �ҋ@�A�j���[�V�����ɐ؂�ւ�
		ChangeAnimation(EAnimType::eIdle);
	}
}

// �U��
void CYukari::UpdateAttack()
{
	// �U���A�j���[�V�������J�n
	ChangeAnimation(EAnimType::eAttack);
	// �U���I���҂���Ԃֈڍs
	mState = EState::eAttackWait;
}

// �U���I���҂�
void CYukari::UpdateAttackWait()
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
void CYukari::UpdateJumpStart()
{
	ChangeAnimation(EAnimType::eJumpStart);
	mState = EState::eJump;

	mMoveSpeed += CVector(0.0f, JUMP_SPEED, 0.0f);
	mIsGrounded = false;
}

// �W�����v��
void CYukari::UpdateJump()
{
	if (mMoveSpeed.Y() <= 0.0f)
	{
		ChangeAnimation(EAnimType::eJumpEnd);
		mState = EState::eJumpEnd;
	}
}

// �W�����v�I��
void CYukari::UpdateJumpEnd()
{
	if (IsAnimationFinished())
	{
		mState = EState::eIdle;
	}
}

// �X�V
void CYukari::Update()
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


	// Yukari�̓���̈ʒu���擾
	CVector headPosition = GetHeadPosition();
	// �r���{�[�h�̈ʒu��ݒ�
	mbillboard->SetPos(CVector2(headPosition.X(), headPosition.Y()));
	// �r���{�[�h�̃T�C�Y��ݒ�
	mbillboard->SetSize(CVector2(600.0f, 30.0f));
	// UV���W�𐳂��������ɐݒ�
	mbillboard->SetUV(0, 0, 1, 1);


	mbillboard1->SetPos(CVector2(headPosition.X(), headPosition.Y()));
	mbillboard1->SetSize(CVector2(600.0f, 30.0f));
	mbillboard1->SetUV(0, 0, 1, 1);

	mbillboard->Render();


	// �L�����N�^�[�̍X�V
	CXCharacter::Update();

	mIsGrounded = false;
}

// �Փˏ���
void CYukari::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
void CYukari::Render()
{
	CXCharacter::Render();
}