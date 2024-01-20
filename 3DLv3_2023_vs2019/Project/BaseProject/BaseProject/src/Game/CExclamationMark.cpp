#include "CExclamationMark.h"
#include "Maths.h"
#include "CImage.h"
#include "CPlayer.h"
#include "CSoldier.h"

// �X�P�[���l�v�Z���̃J�����Ƃ̋����̍ŏ��l
#define SCALE_DIST_MIN 50.0f
// �X�P�[���l�v�Z���̃J�����Ƃ̋����̍ő�l
#define SCALE_DIST_MAX 100.0f
// �X�P�[���l�̍ŏ��l
#define SCALE_MIN 0.8f
// �X�P�[���l�̍ő�l
#define SCALE_MAX 1.0f

// �R���X�g���N�^
CExclamationMark::CExclamationMark()
	: mScale(0.0f)
	, mCenterRatio(0.0f, 0.0f)
{
	// �r�b�N���}�[�N�摜�擾
	mpExclamationMark = new CImage("ExclamationMark");
	mpExclamationMark->SetSize(50.0f, 50.0f);
	mpExclamationMark->SetUV(0, 0, 1, 1);
}

// �f�X�g���N�^
CExclamationMark::~CExclamationMark()
{

}

// �폜
void CExclamationMark::Kill()
{
	CTask::Kill();
	mpExclamationMark->Kill();
}

// ���S�ʒu��ݒ�
void CExclamationMark::SetCeneterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

// ���[���h���W��ݒ�
void CExclamationMark::SetWorldPos(const CVector& worldPos)
{
	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	CVector playerPos = CPlayer::Instance()->Position();

	// �ݒ肳�ꂽ���[���h���W���X�N���[�����W�ɕϊ�
	CVector screenPos = cam->WorldToScreenPos(worldPos);

	// �ݒ肳�ꂽ���[���h���W���J�����̔w��ł���΁A
	// �Q�[�W��\�����Ȃ�
	if (screenPos.Z() < 0.0f)
	{
		SetShow(false);
		return;
	}

	float distanceToPlayer = (worldPos - playerPos).Length();
	if (distanceToPlayer < 100.0f)
	{
		SetShow(true);
	}
	else
	{
		SetShow(false);
	}

	// ���߂��X�N���[�����W�����g�̍��W�ɐݒ�
	mPosition = screenPos;

	//// �ݒ肳�ꂽ���[���h���W�ƃJ�����̋��������߂�
	//float dist = (worldPos - cam->Position()).Length();

	//// �J�������痣��邲�ƂɃX�P�[���l������������
	//float ratio = Math::Clamp01((dist - SCALE_DIST_MIN) / (SCALE_DIST_MAX - SCALE_DIST_MIN));
	//mScale = Math::Lerp(SCALE_MIN, SCALE_MAX, ratio);

}

// �X�V����
void CExclamationMark::Update()
{
	// �t���[���ʒu��ݒ�
	//CVector2 pos = mPosition - CVector2(FRAME_SIZE_X, 0.0f) * 0.5f;
	mpExclamationMark->SetPos(mPosition);
	mpExclamationMark->SetSize(CVector2(50.0f, 50.0f));


	// �t���[���̒��S�ʒu
	mpExclamationMark->SetCenter
	(
		50.0f * mCenterRatio.X(),
		50.0f * mCenterRatio.Y()
	);

	mpExclamationMark->SetShow(IsShow());
}