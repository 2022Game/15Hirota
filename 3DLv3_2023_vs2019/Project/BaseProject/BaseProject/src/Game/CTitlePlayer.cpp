#include "CTitlePlayer.h"
#include "CColliderLine.h"
#include "CCamera.h"
#include "CGameManager.h"
#include "CStageManager.h"

// �d��
#define GRAVITY 0.0625f
// �v���C���[�̍���
#define PLAYER_HEIGHT 16.0f

// �^�C�g���v���C���[�̃C���X�^���X
CTitlePlayer* CTitlePlayer::spInstance = nullptr;

CTitlePlayer* CTitlePlayer::Instance()
{
	return spInstance;
}

// �v���C���[�̃A�j���[�V�����f�[�^�̃e�[�u��
const CTitlePlayer::AnimData CTitlePlayer::ANIM_DATA[] =
{
	{ "",															true,	0.0f	},	// T�|�[�Y
	{ "Character\\Monster1\\anim\\Warrok_Idle.x",					true,	854.0f	},	// �ҋ@
};

// �R���X�g���N�^
CTitlePlayer::CTitlePlayer()
	: CXCharacter(ETag::ePlayer, ETaskPriority::ePlayer, 0,
		ETaskPauseType::ePlayer)
	, mState(EState::eReady)
	, mStateStep(0)
	, mMoveSpeedY(0.0f)
	, mGroundNormal(CVector::zero)
	, mIsGrounded(false)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;

	Position(0.0f, 0.0f, 0.0f);

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

	// �t�B�[���h�Ƃ̓����蔻������R���C�_�[
	mpColliderLine = new CColliderLine
	(
		this, ELayer::ePlayer,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, PLAYER_HEIGHT, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::eField});
}

CTitlePlayer::~CTitlePlayer()
{
	CStageManager::RemoveTask(this);
	spInstance = nullptr;

	SAFE_DELETE(mpColliderLine);
}

// �Փˏ���
void CTitlePlayer::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// ����R���C�_�[
	if (self == mpColliderLine)
	{
		if (other->Layer() == ELayer::eField)
		{
			CVector adjust = hit.adjust;
			mMoveSpeedY = 0.0f;
			adjust.X(0.0f);
			adjust.Z(0.0f);
			Position(Position() + adjust * hit.weight);

			// �ڒn����
			mIsGrounded = true;
			// �ڒn�����n�ʂ̖@�����L�����Ă���
			mGroundNormal = hit.adjust.Normalized();

			if (other->Tag() == ETag::eRideableObject)
			{
				mpRideObject = other->Owner();
			}
		}
	}
}

// ���݂̏�Ԃ�؂�ւ�
void CTitlePlayer::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	// �A�j���[�V�����̍Đ����x�����Ƃɖ߂�
	SetAnimationSpeed(1.0f);
}

// �A�j���[�V�����؂�ւ�
void CTitlePlayer::ChangeAnimation(EAnimType type)
{
	if (!(EAnimType::None < type && type < EAnimType::Num)) return;
	AnimData data = ANIM_DATA[(int)type];
	CXCharacter::ChangeAnimation((int)type, data.loop, data.frameLength);
}

// �������̏��
void CTitlePlayer::UpdateReady()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ���
	switch (mStateStep)
	{
		// �X�e�b�v0 ����������
	case 0:
		ChangeAnimation(EAnimType::eIdle);
		// �S�Ă̏Փ˔�����I�t�ɂ���
		SetEnableCol(false);
		// �v���C���[�̈ړ����x��0�ɂ���
		mMoveSpeedY = 0.0f;
		// ���̃X�e�b�v��
		mStateStep++;
		break;
	}
}

// �ҋ@
void CTitlePlayer::UpdateIdle()
{
	if (mIsGrounded)
	{
		mStateStep = 0;
		ChangeAnimation(EAnimType::eIdle);
	}
	// �v���C���[���ڒn���Ă��Ȃ�
	else
	{
		// �󒆂ɔ�яo�����Ƃ��ɑҋ@���[�V�����֐؂�ւ���̂�
		// ���t���[���҂�
		if (mStateStep <= 5)
		{
			mStateStep++;
		}
		else
		{
			// �ҋ@�A�j���[�V�����ɐ؂�ւ�
			ChangeAnimation(EAnimType::eIdle);
		}
	}
}

// �X�V
void CTitlePlayer::Update()
{
	SetColor(CColor(1.0, 1.0, 1.0, 1.0));
	mpRideObject = nullptr;
	
	// ��Ԃɍ��킹�āA�X�V������؂�ւ���
	switch (mState)
	{
		// �������̏��
	case EState::eReady:
		UpdateReady();
		break;
		// �ҋ@���
	case EState::eIdle:
		UpdateIdle();
		break;
	}

	// �������łȂ���΁A�ړ������Ȃǂ��s��
	if (mState != EState::eReady)
	{
		mMoveSpeedY -= GRAVITY;

		CVector moveSpeed = CVector(0.0f, mMoveSpeedY, 0.0f * Time::DeltaTime());

		// �ړ�
		Position(Position() + moveSpeed * 60.0f * Time::DeltaTime());
	}

	// �L�����N�^�[�̍X�V
	CXCharacter::Update();
	mIsGrounded = false;
}

// �`��
void CTitlePlayer::Render()
{
	// �L�����`��
	CXCharacter::Render();
}