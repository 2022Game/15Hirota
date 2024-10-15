#include "CCannonBase.h"
#include "CPlayer.h"
#include "CCannonBall.h"
#include "Maths.h"

// ����̊p�x
#define FOV_ANGLE 100.0f

// �R���X�g���N�^
CCannonBase::CCannonBase(const CVector& pos, const CVector& scale, const CVector& rot)
    : CObjectBase(ETag::eEnemy, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
    , mpCannon(nullptr)
    , InitialVectorZ(CVector::zero)
{
    InitialVectorZ = Matrix().VectorZ().Normalized();
    // ��C���f�����擾
    //mpCannon = CResourceManager::Get<CModel>("Cannon");

    Position(pos);
    Scale(scale);
    Rotate(rot);
}

// �f�X�g���N�^
CCannonBase::~CCannonBase()
{
    
}

// �Փˏ���
void CCannonBase::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
    // �Փˏ���
}

// �v���C���[�ǐՏ���
bool CCannonBase::IsFoundPlayer() const
{
    CPlayer* player = CPlayer::Instance();
    CVector playerPos = player->Position();
    CVector enemyPos = Position();

    // �v���C���[�ւ̃x�N�g��
    CVector toPlayer = (playerPos - enemyPos).Normalized();
    // �G�̑O�����x�N�g��
    CVector forward = Matrix().VectorZ().Normalized();

    // �h�b�g�όv�Z (�O�������ǂ����̔���)
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
void CCannonBase::Update()
{
   
}

// �`�揈��
void CCannonBase::Render()
{
    if (mpCannon != nullptr)
    {
        mpCannon->SetColor(mColor);
        mpCannon->Render(Matrix());
    }
}


CCannonFoundationsBase::CCannonFoundationsBase(const CVector& pos, const CVector& scale, const CVector& rot,
    std::string modelPath)
    : CObjectBase(ETag::eEnemy, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
    , mpFoundations(nullptr)
{
    // ��C�y�䃂�f�����擾
    mpFoundations = CResourceManager::Get<CModel>(modelPath);

    Position(pos);
    Scale(scale);
    Rotate(rot);
}

CCannonFoundationsBase::~CCannonFoundationsBase()
{
}

void CCannonFoundationsBase::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}

void CCannonFoundationsBase::Update()
{
}

void CCannonFoundationsBase::Render()
{
    if (mpFoundations != nullptr)
    {
        mpFoundations->SetColor(mColor);
        mpFoundations->Render(Matrix());
    }
}