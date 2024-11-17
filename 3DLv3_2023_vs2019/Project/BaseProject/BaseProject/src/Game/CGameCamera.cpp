#include "CGameCamera.h"
#include "CInput.h"
#include "CPlayer.h"

// カメラの回転速度
#define ROTATE_SPEED 0.1f

// コンストラクタ
CGameCamera::CGameCamera(const CVector& eye, const CVector& center, bool isMainCamera)
	: CCamera(eye, center, isMainCamera)
{
}

// デストラクタ
CGameCamera::~CGameCamera()
{
}

// 更新
void CGameCamera::Update()
{
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr) return;

    if (player->IsCameraReset() == false)
    {
        // マウスの横方向の移動量に合わせて、回転値（クォータニオン）を求める
        CVector2 delta = CInput::GetDeltaMousePos();
        CQuaternion rot = CQuaternion(0.0f, delta.X() * ROTATE_SPEED, 0.0f);

        // カメラの向きを回転
        CVector vec = -mEyeVec.Normalized(); // 視線ベクトル
        CVector forward = rot * vec; // 回転後の向き

        // 回転した向きに基づいてカメラの向きを更新
        Rotation(CQuaternion::LookRotation(forward));

        // 追従位置を回転
        mFollowOffsetPos = rot * mFollowOffsetPos;

        // ベースのカメラ更新処理
        CCamera::Update();

		//if (player->IsCameraReset() == false)
		//{
		//	// マウスの横方向の移動量に合わせて、回転値（クォータニオン）を求める
		//	CVector2 delta = CInput::GetDeltaMousePos();
		//	CQuaternion rot = CQuaternion(0.0f, delta.X() * ROTATE_SPEED, 0.0f);

		//	// 追従時のオフセット位置を回転
		//	mFollowOffsetPos = rot * mFollowOffsetPos;

		//	// カメラの向きを回転
		//	CVector vec = -mEyeVec.Normalized();
		//	CVector forward = rot * vec;
		//	Rotation(CQuaternion::LookRotation(forward));

		//	// カメラのベースの更新処理
		//	CCamera::Update();
		//}
    }
}