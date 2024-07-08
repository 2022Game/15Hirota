#include "CMeat3.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"
#include "Easing.h"
#include "CStageManager.h"
#include "CGameManager.h"
#include "CPlayer.h"

// �A�C�e���̈ړ�����
#define GET_MOVE_TIME 1.75f
#define GET_MOVE_UP 10.0f

// ���N���X�̃C���X�^���X
CMeat3* CMeat3::spInstance = nullptr;

int CMeat3::sScore = 0;

CMeat3* CMeat3::Instance()
{
	return spInstance;
}

// �f�X�g���N�^
CMeat3::CMeat3(const CVector& pos, const CVector& rot, const CVector& scale)
	: mState(EState::eIdle)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mGetCameraDist(0.0f)
	, mStartPos(CVector::zero)
	, mGetStartPos(CVector::zero)
	, mGetTargetPos(CVector::zero)
	, mMeat3(false)
	, mIsGround(false)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;
	// �X�R�A
	sScore;

	// ���A�C�e���̃��f���擾
	mpMeat = CResourceManager::Get<CModel>("Meat");

	// ���A�C�e���̃R���C�_�[�쐬
	mpMeatSphere = new CColliderSphere
	(
		this, ELayer::eMeatCol,
		1.5f
	);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	// �^�O�t��
	// ���C���[�t��
	// �R���C�_�[�̈ʒu�𒲐�
	mpMeatSphere->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField, });
	mpMeatSphere->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });

	// �ŏ��̓R���C�_�[���I���ɂ��Ă���
	mpMeatSphere->SetEnable(true);

	Position(pos);
	Rotate(rot);
	Scale(scale);

	mStartPos = Position();
}

// �f�X�g���N�^
CMeat3::~CMeat3()
{
	//spInstance = nullptr;
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpMeatSphere);
}

// ��ԕϏ���
void CMeat3::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// �Փˏ���
void CMeat3::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �R���C�_�[�ɓ���������
	if (self == mpMeatSphere)
	{
		// �v���C���[���
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// �擾��ԂɕύX
			ChangeState(EState::eGet);
		}
	}
	else if (other->Layer() == ELayer::eField)
	{
		mIsGround = true;
		Position(Position() + hit.adjust);
	}
}

// �������������ǂ����̊m�F
bool CMeat3::IsMeat3() const
{
	return mMeat3;
}

// �X�R�A��ݒ�
void CMeat3::SetScore(int score)
{
	sScore = score;
}

// �X�R�A���擾
int CMeat3::GetScore()
{
	return sScore;
}

// �ҋ@���
void CMeat3::UpdateIdle()
{
	float rot = 1.0f;
	Rotate(0.0f, rot, 0.0f);

	mIsGround = false;
}

// �擾���
void CMeat3::UpdateGet()
{
	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// �X�e�b�v���Ƃɏ����𕪂���
	switch (mStateStep)
	{
		// �X�e�b�v0 : �A�C�e�����ړ��J�n
	case 0:
		// �J�����܂ł̋������L�^���Ă���
		mGetCameraDist = (Position() - cam->Position()).Length();
		// �ړ��J�n���̍��W���L�����Ă���
		mGetStartPos = cam->WorldToScreenPos(Position());

		mElapsedTime = 0.0f;
		SetEnableCol(false);

		// �X�V�^�C�~���O���J��������ɕύX
		SetPriority(ETaskPriority::eLeteCamera);

		mStateStep++;
		break;
		// �X�e�b�v1 : �A�C�e����ړI�n�܂ňړ�
	case 1:
		// UI�̃A�C�e���{�b�N�X��2D���W��
		// 3D��Ԃ̍��W�ɕϊ�
		int meatNumber = GetMeatNumber();
		// �O��
		if (meatNumber == 3)
		{
			mGetTargetPos = cam->ScreenToWorldPos
			(
				CVector
				(
					WINDOW_WIDTH * 0.25f,
					WINDOW_HEIGHT * 0.1f,
					mGetCameraDist
				)
			);
		}

		// �A�C�e���擾����3D��Ԃł̍��W���X�N���[�����W���狁�߂�
		mGetStartPos.Z(mGetCameraDist);
		CVector startPos = cam->ScreenToWorldPos(mGetStartPos);

		// �ړ����Ԃ��o�߂��Ă��Ȃ�
		if (mElapsedTime < GET_MOVE_TIME)
		{
			float per = mElapsedTime / GET_MOVE_TIME;
			float per2 = Easing::QuintIn(mElapsedTime, GET_MOVE_TIME, 0.0f, 1.0f);
			CVector pos = CVector::Lerp(startPos, mGetTargetPos, per2);
			pos += CVector::up * sinf(M_PI * per) * GET_MOVE_UP;
			Position(pos);
			mElapsedTime += Time::DeltaTime();
		}
		// �ړ����Ԃ��o�߂���
		else
		{
			if (!mMeat3)
			{
				sScore += 1000;
			}
			mMeat3 = true;
			// �A�C�e���{�b�N�X�̈ʒu�܂ňړ�������A�폜
			Position(mGetTargetPos);
			SetShow(false);
			SetEnableCol(false);
		}

		// �J�����̕����֌�����
		Rotation
		(
			CQuaternion::LookRotation
			(
				(cam->Position() - Position()).Normalized(),
				CVector::up
			)
		);
		break;
	}
}

// �X�V����
void CMeat3::Update()
{
	switch (mState)
	{
	case EState::eIdle:
		UpdateIdle();
		break;
	case EState::eGet:
		UpdateGet();
		break;
	}
}

// �`�揈��
void CMeat3::Render()
{
	// �擾���̈ړ��������̂݁A�f�v�X�e�X�g���I�t�ɂ��āB
	// ���̃I�u�W�F�N�g����O�ɕ\��
	if (mState == EState::eGet)
	{
		glDisable(GL_DEPTH_TEST);
	}
	mpMeat->SetColor(mColor);
	mpMeat->Render(Matrix());

	glEnable(GL_DEPTH_TEST);
}