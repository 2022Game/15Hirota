#include "CCanLockOn.h"
#include "Maths.h"
#include "CCamera.h"
#include "CGameCamera.h"

CCanLockOn::CCanLockOn(ETag tag, ETaskPriority, const CVector& pos)
	: CBillBoardImage("UI\\GimmickUI\\CanLock-onImage.png", tag, ETaskPauseType::eGame)
	, mDefaultPos(pos)
	, mSpeed(1.0f)
	, mElapsedTime(0.0f)
	, mRotationAngle(0.0f)
{
	SetPriority(ETaskPriority::eLockOn);
	SetSize(CVector2(10.0f, 10.0f));
}

CCanLockOn::~CCanLockOn()
{
}

void CCanLockOn::SetColor(const CColor& color)
{
	mMaterial.Diffuse()[0] = color.R();
	mMaterial.Diffuse()[1] = color.G();
	mMaterial.Diffuse()[2] = color.B();
	mMaterial.Diffuse()[3] = color.A();
	CObjectBase::SetColor(color);
}

void CCanLockOn::SetBlendType(EBlend type)
{
	mMaterial.SetBlendType(type);
}

// �X�V
void CCanLockOn::Update()
{
	// ���N���X�̍X�V
	CBillBoardImage::Update();

	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// ���Ԍo�߂ɉ����ĉ�]�p�x���X�V
	mRotationAngle += mSpeed * Time::DeltaTime();

	// ��]�p�x��360�x�𒴂����烊�Z�b�g
	if (mRotationAngle >= 360.0f) {
		mRotationAngle -= 360.0f;
	}

	// �J�����̑O����
	CVector camForward = cam->VectorZ();  
	
	// �J�����̑O��������]���Ƃ��Ďg�p
	CVector localRotationAxis = camForward;

	// �N�H�[�^�j�I���ŉ�]���쐬�i�J�����̌����Ɋ�Â�����]�j
	CQuaternion rotation = CQuaternion::AngleAxis(mRotationAngle, localRotationAxis);

	// �摜�ɉ�]��K�p
	Rotation(rotation);

	SetShow(IsShow());
}