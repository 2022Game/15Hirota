#include "CHorizontalCannon.h"
#include "CPlayer.h"
#include "CHorizontalCannonBall.h"
#include "Maths.h"

// �v���C���[�̃C���X�^���X�ݒ�
#define PLAYER_INSTANCE CPlayer::Instance()
// ����̊p�x
#define FOV_ANGLE 100.0f
// �e�̔��ˑҋ@����
#define WEIT_TIME 2.0f
// �v���C���[�������鋗��
#define CASERANGE 200.0f

// �R���X�g���N�^
CHorizontalCannon::CHorizontalCannon(const CVector& pos, const CVector& scale, const CVector& rot)
    : CObjectBase(ETag::eEnemy, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
    , mFireTime(0.0f)
    , mFire(false)
{
    // ��C���f�����擾
    mpCannon = CResourceManager::Get<CModel>("HorizontalCannon");

    Position(pos);
    Scale(scale);
    Rotate(rot);
}

// �f�X�g���N�^
CHorizontalCannon::~CHorizontalCannon()
{
    // �f�X�g���N�^����
}

// �Փˏ���
void CHorizontalCannon::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
    // �Փˏ���
}

// �v���C���[�ǐՏ���
bool CHorizontalCannon::IsFoundPlayer() const
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
        const float chaseRange = CASERANGE;

        if (distance <= chaseRange)
            return true;
    }

    return false;
}

// �X�V����
void CHorizontalCannon::Update()
{
    if (IsFoundPlayer())
    {
        if (!mFire)
        {
            // �e�ۂ𐶐�
            new CHorizontalCannonBall
            (
                // ���ˈʒu
                Position() + CVector(0.0f, -2.0f, 0.0f) + VectorZ(),
                VectorZ(),	// ���˕���
                80.0f,	    // �ړ�����
                200.0f		// �򋗗�
            );
            mFire = true;
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
    }
    else
    {
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
    }
    
    //CDebugPrint::Print("mFireTime:%f\n", mFireTime);
}

// �`�揈��
void CHorizontalCannon::Render()
{
    mpCannon->SetColor(mColor);
    mpCannon->Render(Matrix());
}


CCannonFoundationsHorizontal::CCannonFoundationsHorizontal(const CVector& pos, const CVector& scale, const CVector& rot)
    : CObjectBase(ETag::eEnemy, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
{
    // ��C�y�䃂�f�����擾
    mpCannonFoundations = CResourceManager::Get<CModel>("HorizontalCannonFound");

    Position(pos);
    Scale(scale);
    Rotate(rot);
}

CCannonFoundationsHorizontal::~CCannonFoundationsHorizontal()
{
}

void CCannonFoundationsHorizontal::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}

void CCannonFoundationsHorizontal::Update()
{
}

void CCannonFoundationsHorizontal::Render()
{
    mpCannonFoundations->SetColor(mColor);
    mpCannonFoundations->Render(Matrix());
}