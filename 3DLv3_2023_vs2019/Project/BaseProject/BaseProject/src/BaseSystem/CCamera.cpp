#include "CCamera.h"
#include "glut.h"
#include "Maths.h"

CCamera* CCamera::spMainCamera = nullptr;

// �R���X�g���N�^
CCamera::CCamera(const CVector& eye, const CVector& center, bool isMainCamera)
	: CObjectBase(ETag::eCamera, ETaskPriority::eCamera)
	, mIsMainCamera(isMainCamera)
	, mFollowTargetTf(nullptr)
	, mFollowOffsetPos(CVector::zero)
{
	Set(eye, center);

	// ���C���J�����ł����
	if (mIsMainCamera)
	{
		spMainCamera = this;
	}
}

// �f�X�g���N�^
CCamera::~CCamera()
{
	// �폜���ꂽ�̂����C���J�����ł���΁A
	// �o�^���Ă��郁�C���J����������
	if (spMainCamera == this)
	{
		spMainCamera = nullptr;
	}
}

// ���C���J�������擾
CCamera* CCamera::MainCamera()
{
	return spMainCamera;
}

void CCamera::Set(const CVector& eye, const CVector& center)
{
	Position(eye);
	CVector forward = (center - eye).Normalized();
	CVector side = CVector::Cross(CVector::up, forward).Normalized();
	CVector up =  CVector::Cross(forward, side).Normalized();
	Rotation(CQuaternion::LookRotation(forward));

	if (mFollowTargetTf != nullptr)
	{
		mFollowOffsetPos = Position() - mFollowTargetTf->Position();
	}
}

// �Ǐ]����^�[�Q�b�g��ݒ�
void CCamera::SetFollowTargetTf(CTransform* target)
{
	mFollowTargetTf = target;
	if (mFollowTargetTf != nullptr)
	{
		mFollowOffsetPos = Position() - mFollowTargetTf->Position();
	}
}

// ��������ʒu��ݒ�
void CCamera::LookAt(const CVector& pos)
{
	CVector forward = (pos - Position()).Normalized();
	CVector side = CVector::Cross(CVector::up, forward).Normalized();
	CVector up = CVector::Cross(forward, side).Normalized();
	Rotation(CQuaternion::LookRotation(forward));
}

// �X�V
void CCamera::Update()
{
	// �Ǐ]����^�[�Q�b�g���ݒ肳��Ă���΁A
	// �J�����̈ʒu��Ǐ]�^�[�Q�b�g�̈ʒu�ɍ��킹��
	if (mFollowTargetTf != nullptr)
	{
		Position(mFollowTargetTf->Position() + mFollowOffsetPos);
	}
}

// �J�������f
void CCamera::Apply()
{
	CVector eye = CTransform::Position();
	CVector center = eye + VectorZ().Normalized();
	CVector up = CVector::up;
	gluLookAt
	(
		eye.X(), eye.Y(), eye.Z(),
		center.X(), center.Y(), center.Z(),
		up.X(), up.Y(), up.Z()
	);
}

// 2D�p�̃J�����s��𔽉f
void CCamera::Start2DCamera()
{
	// �v���W�F�N�V�����s��֐؂�ւ��āA
	// �s��̑ޔ��ƍs���������
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	// 2D�̕\���G���A��ݒ�
	gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);

	// ���f���r���[�s��֖߂��āA
	// �s��̑ޔ��ƍs���������
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// 2D�`��ɕK�v�Ȑݒ���s��
	glDisable(GL_DEPTH_TEST);	// �f�v�X�e�X�g���I�t
	glDisable(GL_LIGHTING);		// ���C�e�B���O���I�t
	glDisable(GL_CULL_FACE);	// �J�����O����
}

// 3D�p�̃J�����s��֖߂�
void CCamera::End2DCamera()
{
	// 3D�`��ɕK�v�ȏ������I���ɂ���
	glEnable(GL_DEPTH_TEST);	// �f�v�X�e�X�g���I��
	glEnable(GL_LIGHTING);		// ���C�e�B���O���I��
	glEnable(GL_CULL_FACE);

	// �v���W�F�N�V�����s��֐؂�ւ��āA
	// 2D�`��J�n���ɑޔ������s��֖߂�
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	// ���f���r���[�s��֖߂��āA
	// ��������ޔ������s��֖߂�
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
