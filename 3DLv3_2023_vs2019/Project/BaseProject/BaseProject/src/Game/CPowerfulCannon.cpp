#include "CPowerfulCannon.h"
#include "CStageManager.h"
#include "CCannonBall.h"
#include "CPlayer.h"

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
#define MAX_SPEED 5.5f
// �ŏ����x
#define MIN_SPEED 6.0f
// ���W�A���p�x
#define RAD_TO_DEG (180.0f / 3.14159265358979323846f)

// �R���X�g���N�^
CPowerfulCannon::CPowerfulCannon(const CVector& pos, const CVector& scale, const CVector& rot,
	std::string modelPath)
	: CCannonBase(pos, scale, rot)
    , mFireTime(0.0f)
    , mFire(false)
{
	// ��C�̃��f���擾
	mpCannon = CResourceManager::Get<CModel>(modelPath);

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CPowerfulCannon::~CPowerfulCannon()
{
	CStageManager::RemoveTask(this);
}

// �X�V����
void CPowerfulCannon::Update()
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

        // ��C����v���C���[�܂ł̋���
        CVector DirectionToPlayer = PlayerPos - CannonPos;
        // ����������Y���͖���
        DirectionToPlayer.Y(0.0f);
        // ��������
        float HorizontalDistance = DirectionToPlayer.Length();
        DirectionToPlayer.Normalize();

        //// ��C�̌�����ς��鏈�� ////
        // ��C�̑O�����ƃv���C���[�����̊p�x���v�Z
        float AngleToPlayer = acos(CVector::Dot(CannonForward, DirectionToPlayer)) * RAD_TO_DEG;

        // ��]�p�x��80�x�ɐ���
        float MaxRotationAngle = 80.0f;
        float RotationAngle = fmin(AngleToPlayer, MaxRotationAngle);

        // ��]�p�x�����e�͈͓��ł���Ή�]
        if (AngleToPlayer <= MaxRotationAngle) 
        {
            // ������Slerp�ŕ��
            float RotationSpeed = 1.0f;
            CVector Forward = CVector::Slerp(CannonForward, DirectionToPlayer, RotationSpeed);
            // ��C���������ɉ�]������
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

            // ���e�n�_�܂ł̋������v�Z
            // ��������
            float ImpactPointToPlayer = HorizontalDistance;

            // �v���C���[�܂ł�3�����������v�Z
            // Y�������܂߂������v�Z
            ImpactPointToPlayer = sqrt(dx * dx + dy * dy + dz * dz);

            // �p�x�W�����v�Z
            float AngleFactor = (ImpactPointToPlayer - MIN_DISTANCE * 0.5f) / (MAX_DISTANCE - MIN_DISTANCE * 0.5f);
            // 0����1�͈̔�
            AngleFactor = std::max(0.0f, std::min(1.0f, AngleFactor));

            // ���ˑ��x�̌v�Z
            // �p�x�Ɋ�Â��đ��x�𒲐�
            float v = MIN_SPEED + (AngleFactor * (MAX_SPEED - MIN_SPEED));

            // ���B���Ԃ��v�Z
            // ���������𑬓x�Ŋ���
            float TimeToPlayer = horizontalDistance / v;

            // �v���C���[�̖����̈ʒu���v�Z
            float PredictedPlayerX = PlayerPos.X() + PlayerSpeed.X() * TimeToPlayer;
            float PredictedPlayerY = PlayerPos.Y() + PlayerSpeed.Y() * TimeToPlayer;
            float PredictedPlayerZ = PlayerPos.Z() + PlayerSpeed.Z() * TimeToPlayer;

            // ��C�̔��ˈʒu��Y���W
            float InitialY = CannonPos.Y();
            float VerticalDrop = 0.5f * g * TimeToPlayer * TimeToPlayer;

            // �ŏI�I�ȖڕWY��ݒ�
            // ������Y�ʒu���g�p
            float TargetY = PredictedPlayerY;

            // �K�v�ȏ���Y�����x���v�Z
            float initialVerticalSpeed = (TargetY - InitialY + VerticalDrop) / TimeToPlayer;

            // �e�̔��˕������v�Z
            // ��{�I��0.3f�̕�������
            CVector DirectionToTarget(PredictedPlayerX - CannonPos.X(), TargetY * 0.01f - InitialY * 0.01f, PredictedPlayerZ - CannonPos.Z());
            // �P�ʃx�N�g���ɐ��K��
            DirectionToTarget.Normalize();

            if (!mFire)
            {
                // �e�ۂ𔭎�
                CCannonBall* cannonBall = new CCannonBall
                (
                    CannonPos + CVector(0.0f, 4.2f, 0.0f),  // �ʒu
                    DirectionToTarget,                      // ����
                    v,                                      // �����ړ����x
                    1500.0f,                                // �ő�򋗗�
                    initialVerticalSpeed                    // Y���������x
                );
                mFire = true; // ���˃t���O�𗧂Ă�
            }

            //// ��C���v���C���[�̕��Ɍ����Ă��邩�ǂ������m�F
            //if (Forward.Dot(DirectionToPlayer) > 0.5f)
            //{
            //    
            //}
        }
    }
    else
    {
        
    }

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