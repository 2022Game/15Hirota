#include "CCanLockOn.h"
#include "Maths.h"
#include "CCamera.h"
#include "CGameCamera.h"

CCanLockOn::CCanLockOn(ETag tag, ETaskPriority, const CVector& pos)
	: CBillBoardImage("UI\\GimmickUI\\CanLock-onImage.png", tag, ETaskPauseType::eGame)
	, mMoveSpeed(CVector::zero)
	, mDefaultPos(pos)
	, mElapsedTime(0.0f)
	, mIsDeath(false)
{
	SetPriority(ETaskPriority::eEffect);
	SetSize(CVector2(50.0f, 50.0f));
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

bool CCanLockOn::IsDeath() const
{
	return mIsDeath;
}

// �摜����]���邽�߂̃p�����[�^
CVector rotationAxis(0, 0, 1);  // Z����]
float rotationSpeed = 1.0f;      // ��]���x�i�x/�b�j
float currentRotationAngle = 0.0f; // ���݂̉�]�p�x

// �X�V
void CCanLockOn::Update()
{
	// ���N���X�̍X�V
	CBillBoardImage::Update();

	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// ���Ԍo�߂ɉ����ĉ�]�p�x���X�V
	// �t���[���Ԃ̌o�ߎ���
	float deltaTime = Time::DeltaTime();
	// ��]�p�x���X�V
	currentRotationAngle += rotationSpeed * deltaTime;

	// ��]�p�x��360�x�𒴂����烊�Z�b�g
	if (currentRotationAngle >= 360.0f) {
		currentRotationAngle -= 360.0f;
	}

	// �J�����̑O����
	CVector camForward = cam->VectorZ();  
	// �J�����̏����
	CVector camUp = cam->VectorY();
	
	// �J�����̏��������]���Ƃ��Ďg�p
	CVector localRotationAxis = camForward;

	// �N�H�[�^�j�I���ŉ�]���쐬�i�J�����̌����Ɋ�Â�����]�j
	CQuaternion rotation = CQuaternion::AngleAxis(currentRotationAngle, localRotationAxis);

	// �摜�ɉ�]��K�p
	Rotation(rotation);
}