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

// 画像が回転するためのパラメータ
CVector rotationAxis(0, 0, 1);  // Z軸回転
float rotationSpeed = 1.0f;      // 回転速度（度/秒）
float currentRotationAngle = 0.0f; // 現在の回転角度

// 更新
void CCanLockOn::Update()
{
	// 基底クラスの更新
	CBillBoardImage::Update();

	// 現在のカメラを取得
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// 時間経過に応じて回転角度を更新
	// フレーム間の経過時間
	float deltaTime = Time::DeltaTime();
	// 回転角度を更新
	currentRotationAngle += rotationSpeed * deltaTime;

	// 回転角度が360度を超えたらリセット
	if (currentRotationAngle >= 360.0f) {
		currentRotationAngle -= 360.0f;
	}

	// カメラの前方向
	CVector camForward = cam->VectorZ();  
	// カメラの上方向
	CVector camUp = cam->VectorY();
	
	// カメラの上方向を回転軸として使用
	CVector localRotationAxis = camForward;

	// クォータニオンで回転を作成（カメラの向きに基づいた回転）
	CQuaternion rotation = CQuaternion::AngleAxis(currentRotationAngle, localRotationAxis);

	// 画像に回転を適用
	Rotation(rotation);
}