#include "CCannon.h"
#include "CPlayer.h"
#include "CCannonBall.h"
#include "Maths.h"

// 視野の角度
#define FOV_ANGLE 100.0f
//// 重力
//#define GRAVITY 9.81f
// 重力
#define GRAVITY 0.0625f
// 発射角
#define LAUNCH_ANGLE 45.0f
// 弾の発射待機時間
#define WEIT_TIME 4.0f

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
    CPlayer* player = CPlayer::Instance();
    CVector playerPos = player->Position();
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
    //// 水平距離があれば
    //if (horizontalDistance > 0)
    //{
    //    if (horizontalDistance <= 0) {
    //        // 水平方向の距離が無効です
    //        printf("エラー: 水平方向の距離が無効です\n");
    //        return; // または適切な処理
    //    }

    //    if (horizontalDistance * tan(theta) <= verticalDistance) {
    //        // 計算が無効になります
    //        printf("エラー: 水平方向の距離が無効です\n");
    //        return;
    //    }

    //    if (verticalDistance < 0)
    //    {
    //        printf("エラー: プレイヤーが大砲よりも低い位置にいます\n");
    //        return; // または適切な処理
    //    }
    //}
    // プレイヤーのインスタンス
    CPlayer* player = CPlayer::Instance();
    // プレイヤーの位置
    CVector playerPos = player->Position();
    // プレイヤーの移動速度
    CVector playerSpeed = player->Velocity();
    // 大砲の位置
    CVector cannonPos = Position();
    // 大砲の正面方向のベクトル
    CVector cannonForward = VectorZ();
    // 正面方向に10.0f移動
    cannonPos = cannonPos + (cannonForward * 10.0f);

    // 大砲からプレイヤーまでの距離
    CVector directionToPlayer = playerPos - cannonPos;
    // 垂直方向のY軸は無視
    directionToPlayer.Y(0.0f);
    directionToPlayer.Normalize();

    // 現在の前進方向と目標方向の間を補間する
    // 回転速度を調整できる
    float rotationSpeed = 1.0f;
    // 向きをSlerpで補間
    CVector forward = CVector::Slerp(cannonForward, directionToPlayer, rotationSpeed);

    // 大砲を横方向に回転させる
    Rotation(CQuaternion::LookRotation(forward));

    // 大砲がプレイヤーの方に向いているかどうかを確認
    if (forward.Dot(directionToPlayer) > 0.99f)
    {
        // 重力
        const float g = GRAVITY;

        // 射程距離の計算
        // 初速
        float initialSpeed = 5.0f;

        // 発射角度の計算
        float theta = asin((directionToPlayer.X() * g) / (initialSpeed * initialSpeed)) / 2;

        // 水平距離
        float horizontalDistance = sin(theta * 2) * initialSpeed * initialSpeed / g;
        // 垂直距離
        float verticalDistance = playerPos.Y() - cannonPos.Y();

        // 初速を計算 (重力, 水平距離, 垂直距離, 角度を考慮)
        //float initialSpeed = sqrt((g * horizontalDistance * horizontalDistance) / (2 * (horizontalDistance * tan(theta) - verticalDistance)));

        // 目標が射程内かどうかを確認
        if (IsFoundPlayer() && !mFire)
        {
            // 縦と横の速度を計算
            // 縦の速度
            //float verticalSpeed = initialSpeed * sin(theta);
            float verticalSpeed = initialSpeed / sqrt(2);
            // 横の速度
            float horizontalSpeed = initialSpeed * cos(theta);

            // 発射時間を計算
            //float timeToTarget = (2 * verticalSpeed) / g;
            float timeToTarget = sin(2 * theta * 2) * initialSpeed * initialSpeed / g;

            // プレイヤーの未来の位置を予測
            CVector futurePlayerPos = playerPos + playerSpeed * timeToTarget;

            // 水平方向の速度を設定
            float dx = futurePlayerPos.X() - cannonPos.X();
            float dz = futurePlayerPos.Z() - cannonPos.Z();

            // 発射方向を計算
            CVector direction(dx, verticalSpeed, dz);
            direction.Normalize();

            // プレイヤーを見つけているかつ打てる状態
            if (IsFoundPlayer() && !mFire)
            {
                // 大砲の弾を生成
                CCannonBall* cannonBall = new CCannonBall
                (
                    cannonPos + CVector(0.0f, 4.0f, -10.0f),    // 発射位置
                    direction,                                  // 発射方向
                    initialSpeed,                               // 発射速度
                    2000.0f,                                    // 最大飛距離
                    verticalSpeed                               // Y軸の初速
                );
                cannonBall->SetVerticalSpeed(verticalSpeed);
                // 打てなくする
                mFire = true;
                printf("direction:%f %f %f\n", direction.X(), direction.Y(), direction.Z());
                printf("initialSpeed:%f\n", initialSpeed);
                printf("verticalSpeed:%f\n", verticalSpeed);
                printf("playerPosition:%f %f %f\n", playerPos.X(), playerPos.Y(), playerPos.Z());
                printf("Position:%f %f %f\n", Position().X(), Position().Y(), Position().Z());
            }
        }
    }

    // 打った後の処理
    if (mFire)
    {
        mFireTime += Time::DeltaTime();
        if (mFireTime >= WEIT_TIME)
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