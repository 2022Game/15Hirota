#include "CCannon.h"
#include "CPlayer.h"
#include "CCannonBall.h"
#include "Maths.h"

// プレイヤーのインスタンス設定
#define PLAYER_INSTANCE CPlayer::Instance()
// 視野の角度
#define FOV_ANGLE 100.0f
// 重力
#define GRAVITY 0.0625f
// 発射角
#define LAUNCH_ANGLE 45.0f

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
        const float chaseRange = 350.0f;

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
    // 現在の位置を取得
    CVector cannonPos = Position();
    // 大砲の正面方向のベクトル
    CVector cannonForward = VectorZ();
    // 正面方向に10.0f移動
    cannonPos = cannonPos + (cannonForward * 10.0f);

    // 大砲からプレイヤーまでの距離
    CVector directionToPlayer = playerPos - cannonPos;
    // 垂直方向のY軸は虫
    directionToPlayer.Y(0.0f);
    directionToPlayer.Normalize();

    // 現在の前進方向と目標方向の間を補間する
    // 回転速度を調整できる
    float rotationSpeed = 0.05f;
    // 向きをSlerpで補間
    CVector forward = CVector::Slerp(cannonForward, directionToPlayer, rotationSpeed);

    // 大砲を横方向に回転させる
    Rotation(CQuaternion::LookRotation(forward));

    // 大砲がプレイヤーの方に向いているかどうかを確認
    if (forward.Dot(directionToPlayer) > 0.99999999f);
    {
        // プレイヤーと大砲の間の水平距離
        float horizontalDistance = sqrt(pow(playerPos.X() - cannonPos.X(), 2) + pow(playerPos.Z() - cannonPos.Z(), 2));
        // プレイヤーと大砲の間の垂直距離
        float verticalDistance = playerPos.Y() - cannonPos.Y();
        // 重力加速度
        const float g = GRAVITY;

        // プレイヤーを見つけているかつ
        // 打てる状態
        if (IsFoundPlayer() && !mFire)
        {
            // 水平距離があれば
            if (horizontalDistance > 0)
            {
                // 発射角を45度に設定し、ラジアンに変換
                float theta = LAUNCH_ANGLE * (M_PI / 180.0f);
                // 角度のタンジェントを計算
                float tanTheta = tan(theta);

                // 初速の計算
                // 目標となるプレイヤーの位置に基づいて初速を計算
                float initialSpeed = sqrt((g * horizontalDistance * horizontalDistance) / (2 * (horizontalDistance * tan(theta) - verticalDistance)));

                // 初速が加算されていれば
                if (initialSpeed > 0)
                {
                    // verticalSpeedの計算を調整
                    float verticalSpeed = initialSpeed * sin(theta);
                    float horizontalSpeed = initialSpeed * cos(theta);

                    // 水平方向の速度をX軸とZ軸に設定
                    // プレイヤーと大砲のX軸の差分
                    float dx = playerPos.X() - cannonPos.X();
                    // プレイヤーと大砲のY軸の差分
                    float dz = playerPos.Z() - cannonPos.Z();
                    // 発射された物体がどれだけの速さでX軸方向に進むかを計算
                    // X軸の速さ
                    float horizontalSpeedX = horizontalSpeed * (dx / horizontalDistance);
                    // Z軸の速さ
                    float horizontalSpeedZ = horizontalSpeed * (dz / horizontalDistance);

                    // 発射方向を計算
                    CVector direction(horizontalSpeedX, verticalSpeed, horizontalSpeedZ);
                    direction.Normalize();

                    // 生成
                    CCannonBall* cannonBall = new CCannonBall
                    (
                        cannonPos + CVector(0.0f, 3.0f, -10.0f),    // 発射位置
                        direction,                                  // 発射方向
                        initialSpeed,                               // 発射速度
                        1000.0f,                                    // 最大飛距離
                        verticalSpeed                               // Y軸の初速
                    );
                    cannonBall->SetVerticalSpeed(verticalSpeed);
                    // 打てなくする
                    mFire = true;
                }
            }
        }
    }

    // 打った後の処理
    if (mFire)
    {
        mFireTime += Time::DeltaTime();
        if (mFireTime >= 4.0f)
        {
            // 一定時間が経過すると
            // 打てるようにする
            mFire = false;
            mFireTime = 0.0f;
        }
    }
    CDebugPrint::Print("mFireTime:%f\n",mFireTime);
}

// 描画処理
void CCannon::Render()
{
    mpCannon->SetColor(mColor);
    mpCannon->Render(Matrix());
}


CCannonFoundations::CCannonFoundations(const CVector& pos, const CVector& scale, const CVector& rot)
    : CObjectBase(ETag::eEnemy, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
{
    // 大砲土台モデルを取得
    mpCannonFoundations = CResourceManager::Get<CModel>("CannonFound");

    Position(pos);
    Scale(scale);
    Rotate(rot);
}

CCannonFoundations::~CCannonFoundations()
{
}

void CCannonFoundations::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}

void CCannonFoundations::Update()
{
}

void CCannonFoundations::Render()
{
    mpCannonFoundations->SetColor(mColor);
    mpCannonFoundations->Render(Matrix());
}