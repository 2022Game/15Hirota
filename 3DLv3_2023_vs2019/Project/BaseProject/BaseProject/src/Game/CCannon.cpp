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
        const float g = GRAVITY;

        float horizontalDistance = (playerPos - cannonPos).Length();
        float verticalDistance = playerPos.Y() - cannonPos.Y();

        float launchSpeed = 15.0f; // ����

        // ���������Ɛ��������Ɋ�Â��Ĕ��ˊp�x���v�Z
        float theta = atan2(verticalDistance, horizontalDistance);

        CVector fireDirection = directionToPlayer;
        fireDirection.Y(0.0f);
        fireDirection.Normalize();

        // �������x���v�Z
        float verticalSpeed = launchSpeed * sinf(theta);

        // ���������̑��x���v�Z
        fireDirection = fireDirection * (launchSpeed * cosf(theta));

        // Y���̑��x�����ł���΁A���ɏC��
        if (verticalSpeed < 0)
        {
            verticalSpeed = fabs(verticalSpeed);
        }

        // ���ˎ���Y�������̑��x��ݒ�
        fireDirection.Y(verticalSpeed);

        if (IsFoundPlayer() && !mFire)
        {
            CCannonBall* cannonBall = new CCannonBall
            (
                cannonPos + CVector(0.0f, 4.0f, -10.0f),
                fireDirection,
                launchSpeed,
                2000.0f,
                verticalSpeed
            );
            cannonBall->SetVerticalSpeed(verticalSpeed);
            mFire = true;
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
    CDebugPrint::Print("mFireTime:%f\n", mFireTime);
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