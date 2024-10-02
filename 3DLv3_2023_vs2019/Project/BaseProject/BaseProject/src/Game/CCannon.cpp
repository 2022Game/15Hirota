#include "CCannon.h"
#include "CPlayer.h"
#include "CCannonBall.h"
#include "Maths.h"

// ����̊p�x
#define FOV_ANGLE 100.0f
//// �d��
//#define GRAVITY 9.81f
// �d��
#define GRAVITY 0.0625f
// ���ˊp
#define LAUNCH_ANGLE 45.0f
// �e�̔��ˑҋ@����
#define WEIT_TIME 4.0f

// �R���X�g���N�^
CCannon::CCannon(const CVector& pos, const CVector& scale, const CVector& rot)
    : CObjectBase(ETag::eEnemy, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
    , mFireTime(0.0f)
    , mFire(false)
{
    // ��C���f�����擾
    mpCannon = CResourceManager::Get<CModel>("Cannon");

    Position(pos);
    Scale(scale);
    Rotate(rot);
}

// �f�X�g���N�^
CCannon::~CCannon()
{
    // �f�X�g���N�^����
}

// �Փˏ���
void CCannon::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
    // �Փˏ���
}

// �v���C���[�ǐՏ���
bool CCannon::IsFoundPlayer() const
{
    CPlayer* player = CPlayer::Instance();
    CVector playerPos = player->Position();
    CVector enemyPos = Position();

    CVector toPlayer = (playerPos - enemyPos).Normalized();
    CVector forward = Matrix().VectorZ().Normalized();

    float dot = forward.Dot(toPlayer);

    // ����p�̔������v�Z����
    float halfFOV = FOV_ANGLE * 0.5f;

    // ����p�̔�����菬�������v���C���[�Ƃ̋��������͈͈ȓ��ł���΁A�v���C���[��F������
    if (dot >= cosf(halfFOV * M_PI / 180.0f))
    {
        float distance = (playerPos - enemyPos).Length();
        const float chaseRange = 350.0f;

        if (distance <= chaseRange)
            return true;
    }

    return false;
}

// �X�V����
void CCannon::Update()
{
    //// ���������������
    //if (horizontalDistance > 0)
    //{
    //    if (horizontalDistance <= 0) {
    //        // ���������̋����������ł�
    //        printf("�G���[: ���������̋����������ł�\n");
    //        return; // �܂��͓K�؂ȏ���
    //    }

    //    if (horizontalDistance * tan(theta) <= verticalDistance) {
    //        // �v�Z�������ɂȂ�܂�
    //        printf("�G���[: ���������̋����������ł�\n");
    //        return;
    //    }

    //    if (verticalDistance < 0)
    //    {
    //        printf("�G���[: �v���C���[����C�����Ⴂ�ʒu�ɂ��܂�\n");
    //        return; // �܂��͓K�؂ȏ���
    //    }
    //}
    // �v���C���[�̃C���X�^���X
    CPlayer* player = CPlayer::Instance();
    // �v���C���[�̈ʒu
    CVector playerPos = player->Position();
    // �v���C���[�̈ړ����x
    CVector playerSpeed = player->Velocity();
    // ��C�̈ʒu
    CVector cannonPos = Position();
    // ��C�̐��ʕ����̃x�N�g��
    CVector cannonForward = VectorZ();
    // ���ʕ�����10.0f�ړ�
    cannonPos = cannonPos + (cannonForward * 10.0f);

    // ��C����v���C���[�܂ł̋���
    CVector directionToPlayer = playerPos - cannonPos;
    // ����������Y���͖���
    directionToPlayer.Y(0.0f);
    directionToPlayer.Normalize();

    // ���݂̑O�i�����ƖڕW�����̊Ԃ��Ԃ���
    // ��]���x�𒲐��ł���
    float rotationSpeed = 1.0f;
    // ������Slerp�ŕ��
    CVector forward = CVector::Slerp(cannonForward, directionToPlayer, rotationSpeed);

    // ��C���������ɉ�]������
    Rotation(CQuaternion::LookRotation(forward));

    // ��C���v���C���[�̕��Ɍ����Ă��邩�ǂ������m�F
    if (forward.Dot(directionToPlayer) > 0.99f)
    {
        // �d��
        const float g = GRAVITY;

        // �˒������̌v�Z
        // ����
        float initialSpeed = 5.0f;

        // ���ˊp�x�̌v�Z
        float theta = asin((directionToPlayer.X() * g) / (initialSpeed * initialSpeed)) / 2;

        // ��������
        float horizontalDistance = sin(theta * 2) * initialSpeed * initialSpeed / g;
        // ��������
        float verticalDistance = playerPos.Y() - cannonPos.Y();

        // �������v�Z (�d��, ��������, ��������, �p�x���l��)
        //float initialSpeed = sqrt((g * horizontalDistance * horizontalDistance) / (2 * (horizontalDistance * tan(theta) - verticalDistance)));

        // �ڕW���˒������ǂ������m�F
        if (IsFoundPlayer() && !mFire)
        {
            // �c�Ɖ��̑��x���v�Z
            // �c�̑��x
            //float verticalSpeed = initialSpeed * sin(theta);
            float verticalSpeed = initialSpeed / sqrt(2);
            // ���̑��x
            float horizontalSpeed = initialSpeed * cos(theta);

            // ���ˎ��Ԃ��v�Z
            //float timeToTarget = (2 * verticalSpeed) / g;
            float timeToTarget = sin(2 * theta * 2) * initialSpeed * initialSpeed / g;

            // �v���C���[�̖����̈ʒu��\��
            CVector futurePlayerPos = playerPos + playerSpeed * timeToTarget;

            // ���������̑��x��ݒ�
            float dx = futurePlayerPos.X() - cannonPos.X();
            float dz = futurePlayerPos.Z() - cannonPos.Z();

            // ���˕������v�Z
            CVector direction(dx, verticalSpeed, dz);
            direction.Normalize();

            // �v���C���[�������Ă��邩�łĂ���
            if (IsFoundPlayer() && !mFire)
            {
                // ��C�̒e�𐶐�
                CCannonBall* cannonBall = new CCannonBall
                (
                    cannonPos + CVector(0.0f, 4.0f, -10.0f),    // ���ˈʒu
                    direction,                                  // ���˕���
                    initialSpeed,                               // ���ˑ��x
                    2000.0f,                                    // �ő�򋗗�
                    verticalSpeed                               // Y���̏���
                );
                cannonBall->SetVerticalSpeed(verticalSpeed);
                // �łĂȂ�����
                mFire = true;
                printf("direction:%f %f %f\n", direction.X(), direction.Y(), direction.Z());
                printf("initialSpeed:%f\n", initialSpeed);
                printf("verticalSpeed:%f\n", verticalSpeed);
                printf("playerPosition:%f %f %f\n", playerPos.X(), playerPos.Y(), playerPos.Z());
                printf("Position:%f %f %f\n", Position().X(), Position().Y(), Position().Z());
            }
        }
    }

    // �ł�����̏���
    if (mFire)
    {
        mFireTime += Time::DeltaTime();
        if (mFireTime >= WEIT_TIME)
        {
            // ��莞�Ԃ��o�߂����
            // �łĂ�悤�ɂ���
            mFire = false;
            mFireTime = 0.0f;
        }
    }
    CDebugPrint::Print("mFireTime:%f\n",mFireTime);
}

// �`�揈��
void CCannon::Render()
{
    mpCannon->SetColor(mColor);
    mpCannon->Render(Matrix());
}


CCannonFoundations::CCannonFoundations(const CVector& pos, const CVector& scale, const CVector& rot)
    : CObjectBase(ETag::eEnemy, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
{
    // ��C�y�䃂�f�����擾
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