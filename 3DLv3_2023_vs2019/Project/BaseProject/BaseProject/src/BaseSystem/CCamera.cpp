#include "CCamera.h"
#include "glut.h"
#include "Maths.h"
#include "CDebugCamera.h"

CCamera* CCamera::spMainCamera = nullptr;

// �R���X�g���N�^
CCamera::CCamera(const CVector& eye, const CVector& center, bool isMainCamera)
	: CObjectBase(ETag::eCamera, ETaskPriority::eCamera)
	, mIsMainCamera(isMainCamera)
	, mFollowTargetTf(nullptr)
	, mFollowOffsetPos(CVector::zero)
	, mFovy(CAMERA_FOVY)
	, mZNear(CAMERA_ZNEAR)
	, mZFar(CAMERA_ZFAR)
{
	LookAt(eye, center, CVector::up);
	Reshape(WINDOW_WIDTH, WINDOW_HEIGHT);

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

// ���݂̃J�������擾
CCamera* CCamera::CurrentCamera()
{
	// �f�o�b�O�J�������L���ł���΁A
	if (CDebugCamera::IsOn())
	{
		// �f�o�b�O�J������Ԃ�
		return CDebugCamera::DebugCamera();
	}
	// �f�o�b�O�J�����������ł���΁A
	else
	{
		// ���C���J������Ԃ�
		return spMainCamera;
	}
}

// �J�����̏�Ԃ��R�s�[
void CCamera::CopyCamera(CCamera * copy)
{
	if (copy == nullptr) return;
	
	Position(copy->Position());
	Rotation(copy->Rotation());
	mViewMatrix = copy->mViewMatrix;
	mProjectionMatrix = copy->mProjectionMatrix;
	mViewportMatrix = copy->mViewportMatrix;
	mFovy = copy->mFovy;
	mZNear = copy->mZNear;
	mZFar = copy->mZFar;
	mEye = copy->mEye;
	mAt = copy->mAt;
	mUp = copy->mUp;
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

// �Ǐ]���̃I�t�Z�b�g���W��ݒ�
void CCamera::SetFollowTargetOffset(const CVector& offset)
{
	if (mFollowTargetTf != nullptr)
	{
		mFollowOffsetPos = offset;
	}
}

// ��������ʒu��ݒ�i�����_�̂݁j
void CCamera::LookAt(const CVector& pos)
{
	LookAt(mEye, pos, mUp);
}

// ��������ʒu��ݒ�i�����_ + ��x�N�g���j
void CCamera::LookAt(const CVector& pos, const CVector& up)
{
	LookAt(mEye, pos, up);
}

// ��������ʒu��ݒ�i���_ + �����_ + ��x�N�g���j
void CCamera::LookAt(const CVector& eye, const CVector& at, const CVector& up)
{
	mEye = eye; mAt = at; mUp = up;
	mViewMatrix.Identity();
	CVector f = (mEye - mAt).Normalized();
	CVector r = CVector::Cross(mUp, f).Normalized();
	CVector u = CVector::Cross(f, r).Normalized();
	mViewMatrix.M(0, 0, r.X()); mViewMatrix.M(1, 0, r.Y()); mViewMatrix.M(2, 0, r.Z());
	mViewMatrix.M(0, 1, u.X()); mViewMatrix.M(1, 1, u.Y()); mViewMatrix.M(2, 1, u.Z());
	mViewMatrix.M(0, 2, f.X()); mViewMatrix.M(1, 2, f.Y()); mViewMatrix.M(2, 2, f.Z());
	mViewMatrix.M(3, 0, -CVector::Dot(mEye, r));
	mViewMatrix.M(3, 1, -CVector::Dot(mEye, u));
	mViewMatrix.M(3, 2, -CVector::Dot(mEye, f));

	Position(mEye);
	Rotation(CQuaternion::LookRotation(f));

	if (mFollowTargetTf != nullptr)
	{
		mFollowOffsetPos = Position() - mFollowTargetTf->Position();
	}
}

// ��ʃT�C�Y�ύX����
void CCamera::Reshape(int width, int height)
{
	//��ʂ̕`��G���A�̎w��
	Viewport(0.0f, 0.0f, width, height);

	Perspective
	(
		CAMERA_FOVY,
		(float)width / height,
		CAMERA_ZNEAR,
		CAMERA_ZFAR
	);
}

// ��ʂ̕`��G���A���w��
void CCamera::Viewport(float x, float y, float w, float h)
{
	glViewport(x, y, w, h);
	mViewportMatrix.Identity();
	mViewportMatrix.M(0, 0, w * 0.5f);
	mViewportMatrix.M(3, 0, x + w * 0.5f);
	mViewportMatrix.M(1, 1, -h * 0.5f);
	mViewportMatrix.M(3, 1, y + h * 0.5f);
}

// �������e�s���ݒ�
void CCamera::Perspective(float fovy, float aspect, float zNear, float zFar)
{
	//�e�l��ݒ�
	mFovy = fovy;
	mZNear = zNear;
	mZFar = zFar;

	//�v���W�F�N�V�����s��֐؂�ւ�
	glMatrixMode(GL_PROJECTION);
	//�s������������āA�V�����v���W�F�N�V�����s���ݒ�
	glLoadIdentity();
	gluPerspective(mFovy, aspect, mZNear, mZFar);
	//�v���W�F�N�V�����s����L�����Ă���
	glGetFloatv(GL_PROJECTION_MATRIX, mProjectionMatrix.M());

	//���f���r���[�s��֖߂�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// �X�N���[�����W���烏�[���h���W�֕ϊ�
CVector CCamera::ScreenToWorldPos(const CVector& screenPos)
{
	float z = screenPos.Z();
	float d = ((z * (mZFar + mZNear) - 2.0f * mZFar * mZNear) / (mZFar - mZNear) / z);
	CVector4 v =
		mViewportMatrix.Inverse() *
		mProjectionMatrix.Inverse() *
		mViewMatrix.Inverse() *
		CVector4(screenPos.X(), screenPos.Y(), d, 1.0f);
	return CVector(v.X() / v.W(), v.Y() / v.W(), v.Z() / v.W());
}

// ���[���h���W����X�N���[�����W�֕ϊ�
CVector CCamera::WorldToScreenPos(const CVector& worldPos)
{
	CVector4 v =
		mViewMatrix *
		mProjectionMatrix *
		mViewportMatrix *
		CVector4(worldPos, 1.0f);
	return CVector(v.X() / v.W(), v.Y() / v.W(), v.Z() / fabsf(v.W()));
}

// �X�V
void CCamera::Update()
{
	// �Ǐ]����^�[�Q�b�g���ݒ肳��Ă���΁A
	// �J�����̈ʒu��Ǐ]�^�[�Q�b�g�̈ʒu�ɍ��킹��
	if (mFollowTargetTf != nullptr)
	{
		Position(mFollowTargetTf->Position() + mFollowOffsetPos);
		mEye = Position();
		mAt = mEye + -VectorZ().Normalized();
	}
	LookAt(mEye, mAt, mUp);
}

// �J�������f
void CCamera::Apply()
{
	glMultMatrixf(mViewMatrix.M());
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
