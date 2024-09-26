#include "CCannon.h"
#include "CPlayer.h"
#include "CCannonBall.h"
#include "Maths.h"

// �v���C���[�̃C���X�^���X�ݒ�
#define PLAYER_INSTANCE CPlayer::Instance()
// ����̊p�x
#define FOV_ANGLE 100.0f
// �d��
#define GRAVITY 0.0625f
// ���ˊp
#define LAUNCH_ANGLE 45.0f

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
    CVector playerPos = PLAYER_INSTANCE->Position();
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
    CPlayer* player = CPlayer::Instance();
    CVector playerPos = player->Position();
    // ���݂̈ʒu���擾
    CVector cannonPos = Position();
    // ��C�̐��ʕ����̃x�N�g��
    CVector cannonForward = VectorZ();
    // ���ʕ�����10.0f�ړ�
    cannonPos = cannonPos + (cannonForward * 10.0f);

    // ��C����v���C���[�܂ł̋���
    CVector directionToPlayer = playerPos - cannonPos;
    // ����������Y���͒�
    directionToPlayer.Y(0.0f);
    directionToPlayer.Normalize();

    // ���݂̑O�i�����ƖڕW�����̊Ԃ��Ԃ���
    // ��]���x�𒲐��ł���
    float rotationSpeed = 0.05f;
    // ������Slerp�ŕ��
    CVector forward = CVector::Slerp(cannonForward, directionToPlayer, rotationSpeed);

    // ��C���������ɉ�]������
    Rotation(CQuaternion::LookRotation(forward));

    // ��C���v���C���[�̕��Ɍ����Ă��邩�ǂ������m�F
    if (forward.Dot(directionToPlayer) > 0.99999999f);
    {
        // �v���C���[�Ƒ�C�̊Ԃ̐�������
        float horizontalDistance = sqrt(pow(playerPos.X() - cannonPos.X(), 2) + pow(playerPos.Z() - cannonPos.Z(), 2));
        // �v���C���[�Ƒ�C�̊Ԃ̐�������
        float verticalDistance = playerPos.Y() - cannonPos.Y();
        // �d�͉����x
        const float g = GRAVITY;

        // �v���C���[�������Ă��邩��
        // �łĂ���
        if (IsFoundPlayer() && !mFire)
        {
            // ���������������
            if (horizontalDistance > 0)
            {
                // ���ˊp��45�x�ɐݒ肵�A���W�A���ɕϊ�
                float theta = LAUNCH_ANGLE * (M_PI / 180.0f);
                // �p�x�̃^���W�F���g���v�Z
                float tanTheta = tan(theta);

                // �����̌v�Z
                // �ڕW�ƂȂ�v���C���[�̈ʒu�Ɋ�Â��ď������v�Z
                float initialSpeed = sqrt((g * horizontalDistance * horizontalDistance) / (2 * (horizontalDistance * tan(theta) - verticalDistance)));

                // ���������Z����Ă����
                if (initialSpeed > 0)
                {
                    // verticalSpeed�̌v�Z�𒲐�
                    float verticalSpeed = initialSpeed * sin(theta);
                    float horizontalSpeed = initialSpeed * cos(theta);

                    // ���������̑��x��X����Z���ɐݒ�
                    // �v���C���[�Ƒ�C��X���̍���
                    float dx = playerPos.X() - cannonPos.X();
                    // �v���C���[�Ƒ�C��Y���̍���
                    float dz = playerPos.Z() - cannonPos.Z();
                    // ���˂��ꂽ���̂��ǂꂾ���̑�����X�������ɐi�ނ����v�Z
                    // X���̑���
                    float horizontalSpeedX = horizontalSpeed * (dx / horizontalDistance);
                    // Z���̑���
                    float horizontalSpeedZ = horizontalSpeed * (dz / horizontalDistance);

                    // ���˕������v�Z
                    CVector direction(horizontalSpeedX, verticalSpeed, horizontalSpeedZ);
                    direction.Normalize();

                    // ����
                    CCannonBall* cannonBall = new CCannonBall
                    (
                        cannonPos + CVector(0.0f, 3.0f, -10.0f),    // ���ˈʒu
                        direction,                                  // ���˕���
                        initialSpeed,                               // ���ˑ��x
                        1000.0f,                                    // �ő�򋗗�
                        verticalSpeed                               // Y���̏���
                    );
                    cannonBall->SetVerticalSpeed(verticalSpeed);
                    // �łĂȂ�����
                    mFire = true;
                }
            }
        }
    }

    // �ł�����̏���
    if (mFire)
    {
        mFireTime += Time::DeltaTime();
        if (mFireTime >= 4.0f)
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