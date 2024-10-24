#include "CCannon.h"
#include "CPlayer.h"
#include "CCannonBall.h"
#include "CStageManager.h"
#include "Maths.h"

// �d��
#define GRAVITY 0.0625f
// �e�̔��ˑҋ@����
#define WEIT_TIME 2.0f

// �v���C���[�̍ŏ�����
#define MIN_DISTANCE 10.0f
// �v���C���[�̍ő勗��
#define MAX_DISTANCE 350.0f
// �ő�p�x
#define MAX_ANGLE 90.0f
// �ŏ��p�x
#define MIN_ANGLE -10.0f
// �ő呬�x
#define MAX_SPEED 4.5f
// �ŏ����x
#define MIN_SPEED 5.0f

// �R���X�g���N�^
CCannon::CCannon(const CVector& pos, const CVector& scale, const CVector& rot,
    std::string modelPath)
    : CCannonBase(pos, scale, rot)
    , mFireTime(0.0f)
    , mFire(false)
{
    // ��C���f�����擾
    mpCannon = CResourceManager::Get<CModel>(modelPath);

    Position(pos);
    Scale(scale);
    Rotate(rot);
}

// �f�X�g���N�^
CCannon::~CCannon()
{
    CStageManager::RemoveTask(this);
}

// �X�V����
void CCannon::Update()
{
    if (IsFoundPlayer())
    {
        //// �����ݒ� ////
        // �v���C���[�̃C���X�^���X
        CPlayer* player = CPlayer::Instance();
        // �v���C���[�̈ʒu
        CVector PlayerPos = player->Position();
        // �v���C���[�̈ړ����x
        CVector PlayerSpeed = player->Velocity();
        // ��C�̈ʒu
        CVector CannonPos = Position();
        // ��C�̐��ʕ����̃x�N�g��
        CVector CannonForward = VectorZ();
        // ���ʕ�����10.0f�ړ�
        // �C���̈ʒu���΂ߑO�̂��ߏ���Z�ʒu��ύX
        CannonPos = CannonPos + (CannonForward * 11.0f);

        //// ��C�̌�����ς��鏈�� ////
        // ��C����v���C���[�܂ł̋���
        CVector DirectionToPlayer = PlayerPos - CannonPos;
        // ����������Y���͖���
        DirectionToPlayer.Y(0.0f);
        // ��������
        float HorizontalDistance = DirectionToPlayer.Length();
        DirectionToPlayer.Normalize();
        // ��]���x�𒲐��ł���
        float RotationSpeed = 1.0f;
        // ������Slerp�ŕ��
        CVector Forward = CVector::Slerp(CannonForward, DirectionToPlayer, RotationSpeed);

        // ��C���������ɉ�]������
        Rotation(CQuaternion::LookRotation(Forward));
        // ���݂̑�C�̌����ƃv���C���[�����Ƃ̊p�x���v�Z
        float AngleToPlayer = acos(CVector::Dot(VectorZ(), DirectionToPlayer));

        // �p�x�̐���
        // ���W�A���ɕϊ�
        float MaxRotationAngle = 45.0f * (M_PI / 180.0f);

        // �p�x�������͈͓��ɂ��邩�`�F�b�N
        if (AngleToPlayer <= MaxRotationAngle)
        {
            // ��]���x�𒲐��ł���
            float RotationSpeed = 1.0f;
            // ������Slerp�ŕ��
            CVector Forward = CVector::Slerp(CannonForward, DirectionToPlayer, RotationSpeed);

            // ��C����]������
            Rotation(CQuaternion::LookRotation(Forward));

            // �d�͉����x
            const float g = GRAVITY;

            // �v���C���[�̈ʒu�Ƃ̑��ΓI�ȍ����v�Z
            float dx = PlayerPos.X() - CannonPos.X();
            float dy = PlayerPos.Y() - CannonPos.Y();
            float dz = PlayerPos.Z() - CannonPos.Z();

            // �����������v�Z
            // Y�����������������v�Z
            float horizontalDistance = sqrt(dx * dx + dz * dz);

            // �v���C���[�܂ł�3�����������v�Z
            float ImpactPointToPlayer = sqrt(dx * dx + dy * dy + dz * dz);

            // �p�x�W�����v�Z
            float AngleFactor = (ImpactPointToPlayer - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE);
            AngleFactor = std::max(0.0f, std::min(1.0f, AngleFactor));

            // ���ˑ��x�̌v�Z
            float v = MIN_SPEED + (AngleFactor * (MAX_SPEED - MIN_SPEED));

            // ���B���Ԃ��v�Z
            // ���������𑬓x�Ŋ���
            float TimeToPlayer = horizontalDistance / v;

            // �K�v��Y���̈ړ��ʂ��v�Z
            float InitialY = CannonPos.Y();
            float VerticalDrop = 0.5f * g * TimeToPlayer * TimeToPlayer;

            // �ŏI�I�ȖڕWY��ݒ�
            float TargetY = PlayerPos.Y();

            // �K�v�ȏ���Y�����x���v�Z
            float initialVerticalSpeed = (TargetY - InitialY + VerticalDrop) / TimeToPlayer;

            // �e�̔��˕������v�Z
            CVector DirectionToTarget(dx, TargetY * 0.3f - InitialY * 0.3f, dz);
            DirectionToTarget.Normalize();

            if (!mFire)
            {
                // �e�ۂ𔭎�
                CCannonBall* cannonBall = new CCannonBall
                (
                    CannonPos + CVector(0.0f, 4.0f, 0.0f),  // �ʒu
                    DirectionToTarget,                      // ����
                    v,                                      // �����ړ����x
                    1500.0f,                                // �ő�򋗗�
                    initialVerticalSpeed                    // Y���������x
                );
                mFire = true; // ���˃t���O�𗧂Ă�
            }
            //// ��C���v���C���[�̕��Ɍ����Ă��邩�ǂ������m�F
            //if (Forward.Dot(DirectionToPlayer) > 0.99f)
            //{
            //    
            //}
        }
        else
        {
            // �����͈͂𒴂����ꍇ�A��]���Ȃ��i�܂��͐����p�x�܂ŉ�]�j
            // �K�v�ɉ����ĕʂ̏�����ǉ�
        }
    }

    //CDebugPrint::Print("isFound:%s\n", IsFoundPlayer() ? "true" : "false");
    // �ł�����̏���
    if (mFire)
    {
        // ���Ԃ𑝕�
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