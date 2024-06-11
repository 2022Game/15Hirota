#include "CHealingPotion.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"
#include "CSound.h"
#include "CStageManager.h"

// �d��
#define GRAVITY 0.0625f

CHealingPotion::CHealingPotion()
	: mHealingUsed(false)
	, mIsGround(false)
	, mIsHeld(false)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
{
	// �񕜖�A�C�e�����f���擾
	mpHealingPotion = CResourceManager::Get<CModel>("Healing");

	// �񕜂����Ƃ���SE�擾
	mpHealingSE = CResourceManager::Get<CSound>("8bitKaifuku");

	// �񕜔���p�̃R���C�_�[�쐬
	mpHealingCol = new CColliderSphere
	(
		this, ELayer::eRecoverCol,
		1.5f
	);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	// �^�O�t��
	// ���C���[�t��
	// �R���C�_�[�̈ʒu�𒲐�
	mpHealingCol->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField });
	mpHealingCol->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });
	mpHealingCol->Position(0.0f, 1.0f, 0.0f);

	// �ŏ��̓R���C�_�[���I���ɂ��Ă���
	mpHealingCol->SetEnable(true);
}

CHealingPotion::~CHealingPotion()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpHealingCol);
}


// �Փˏ���
void CHealingPotion::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�̃R���C�_�[�ł����
	if (self == mpHealingCol)
	{
		// �v���C���[��h���N���X�̃|�C���^�ɕϊ�
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// ���łɉ񕜍ς݂̃L�����łȂ����
			if (!IsAttachHitHealingObj(player) && !mHealingUsed)
			{
				//mpHealingSE->Play(1.0f, false, 0.0f);
				mHealingUsed = true;

				// �񕜍ς݃��X�g�ɒǉ�
				AddAttachHitHealingObj(player);

				if (mHealingUsed)
				{
					Kill();
				}
			}
		}
		// �t�B�[���h�֘A�̓����蔻��
		else if (other->Layer() == ELayer::eField)
		{
			// ���ɂ��Ă���
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust * hit.weight);
		}
		// �u���b�N�֘A�̓����蔻��
		else if (other->Layer() == ELayer::eBlockCol)
		{
			// ���ɂ��Ă���
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		// �ǃR���C�_�[�֘A�̓����蔻��
		else if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust * hit.weight);
		}
	}
}
//
//void CHealingPotion::HealingStart()
//{
//	CItemObjectBase::HealingStart();
//	// �񕜂��n�܂�����A�񕜃R���C�_�[���I���ɂ���
//	mpHealingCol->SetEnable(true);
//}
//
//// �񕜏I��
//void CHealingPotion::HealingEnd()
//{
//	CItemObjectBase::HealingEnd();
//	// �񕜂��I���΁A�񕜃R���C�_�[���I�t�ɂ����
//	mpHealingCol->SetEnable(false);
//}

void CHealingPotion::OnTouch(CPlayer* player)
{
	if (mIsHeld)
	{
		player->AddItem(CPlayer::ItemType::HEALING);
		mIsHeld = true;
	}
}

// �X�V����
void CHealingPotion::Update()
{
	// �d��
	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// ��]
	const float rot = 1.0f;
	Rotate(0.0f, rot, 0.0f);

	// �ړ�
	Position(Position() + mMoveSpeed * 60.0f * Time::DeltaTime());
}

// �`��
void CHealingPotion::Render()
{
	mpHealingPotion->SetColor(mColor);
	mpHealingPotion->Render(Matrix());
}