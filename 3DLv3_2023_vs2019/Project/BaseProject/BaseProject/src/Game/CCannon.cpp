#include "CCannon.h"
#include "CPlayer.h"
#include "CCannonBall.h"
#include "Maths.h"

// プレイヤーのインスタンス設定
#define PLAYER_INSTANCE CPlayer::Instance()
// 視野の角度
#define FOV_ANGLE 100.0f

// コンストラクタ
CCannon::CCannon(const CVector& pos, const CVector& scale, const CVector& rot)
    : CObjectBase(ETag::eEnemy, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
    , mFireTime(0.0f)
    , mFire(false)
{
    // 大砲モデルを取得
    mpCannon = CResourceManager::Get<CModel>("Cannon");

    Position(pos);
    Scale(scale);
    Rotate(rot);
}

// デストラクタ
CCannon::~CCannon()
{
    // デストラクタ処理
}

// 衝突処理
void CCannon::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
    // 衝突処理
}

// プレイヤー追跡処理
bool CCannon::IsFoundPlayer() const
{
    CVector playerPos = PLAYER_INSTANCE->Position();
    CVector enemyPos = Position();

    CVector toPlayer = (playerPos - enemyPos).Normalized();
    CVector forward = Matrix().VectorZ().Normalized();

    float dot = forward.Dot(toPlayer);

    // 視野角の半分を計算する
    float halfFOV = FOV_ANGLE * 0.5f;

    // 視野角の半分より小さいかつプレイヤーとの距離が一定範囲以内であれば、プレイヤーを認識する
    if (dot >= cosf(halfFOV * M_PI / 180.0f))
    {
        float distance = (playerPos - enemyPos).Length();
        const float chaseRange = 550.0f;

        if (distance <= chaseRange)
            return true;
    }

    return false;
}

// 更新処理
void CCannon::Update()
{
    CPlayer* player = CPlayer::Instance();
    CVector playerPos = player->Position();
    CVector cannonPos = Position();

    // プレイヤーと大砲の間の水平距離
    float horizontalDistance = sqrt(pow(playerPos.X() - cannonPos.X(), 2) + pow(playerPos.Z() - cannonPos.Z(), 2));
    // プレイヤーと大砲の間の垂直距離
    float verticalDistance = playerPos.Y() - cannonPos.Y();
    // 重力加速度
    const float g = 0.0625f;

    // プレイヤーを見つけているかつ
    // 打てる状態
    if (IsFoundPlayer() && !mFire)
    {
        if (horizontalDistance > 0)
        {
            // 発射角を45度に設定し、ラジアンに変換
            float theta = 45.0f * (3.1415f / 180.0f);
            // 角度のタンジェントを計算
            float tanTheta = tan(theta);

            // 初速の計算
            // 目標となるプレイヤーの位置に基づいて初速を計算
            float initialSpeed = sqrt((g * horizontalDistance * horizontalDistance) / (2 * (horizontalDistance * tan(theta) - verticalDistance)));

            if (initialSpeed > 0)
            {
                // verticalSpeedの計算を調整
                float verticalSpeed = initialSpeed * sin(theta);
                float horizontalSpeed = initialSpeed * cos(theta);

                // 水平方向の速度をX軸とZ軸に設定
                float dx = playerPos.X() - cannonPos.X();
                float dz = playerPos.Z() - cannonPos.Z();
                float horizontalSpeedX = horizontalSpeed * (dx / horizontalDistance);
                float horizontalSpeedZ = horizontalSpeed * (dz / horizontalDistance);

                // 発射方向を計算
                CVector direction(horizontalSpeedX, verticalSpeed, horizontalSpeedZ);
                direction.Normalize();

                // 生成
                CCannonBall* cannonBall = new CCannonBall
                (
                    cannonPos + CVector(0.0f, 15.5f, 0.0f), // 発射位置
                    direction,                              // 発射方向
                    initialSpeed,                           // 発射速度
                    5000.0f,                                // 最大飛距離
                    verticalSpeed                           // Y軸の初速
                );
                cannonBall->SetVerticalSpeed(verticalSpeed);
                // 打てなくする
                mFire = true;
            }
        }
    }

    // 打った後の処理
    if (mFire)
    {
        mFireTime += Time::DeltaTime();
        if (mFireTime >= 2.0f)
        {
            // 一定時間が経過すると
            // 打てるようにする
            mFire = false;
            mFireTime = 0.0f;
        }
    }
}

// 描画処理
void CCannon::Render()
{
    mpCannon->SetColor(mColor);
    mpCannon->Render(Matrix());
}