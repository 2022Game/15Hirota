#include "CBlueMedal.h"
#include "CMedalObjectBase.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"
#include "CSound.h"
#include "CBlueMedalEvent.h"
#include "CStageManager.h"

// �d��
#define GRAVITY 0.0625

int CBlueMedal::sScore = 0;

CBlueMedal::CBlueMedal(const CVector& pos, const CVector& scale)
	: CMedalObjectBase(ETaskPriority::eMedal)
	, mIsGround(false)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mpEvent(nullptr)
{
	sScore;

	// �u���[���_�����f���擾
	mpBlueMedel = CResourceManager::Get<CModel>("BlueMedal");

	mpBlueMedalCol = new CColliderSphere
	(
		this, ELayer::eMedalCol,
		1.3f
	);
	mpBlueMedalCol->SetCollisionTags({ ETag::ePlayer,ETag::eField });
	mpBlueMedalCol->SetCollisionLayers({ ELayer::ePlayer,ELayer::eField,ELayer::eFieldWall });
	mpBlueMedalCol->Position(0.0f, 1.0f, 0.0f);

	Position(pos);
	Scale(scale);

	mpBlueMedalCol->SetEnable(true);

	SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
}

CBlueMedal::~CBlueMedal()
{
	// �쐬�����^�X�N����菜��
	CStageManager::RemoveTask(this);

	SAFE_DELETE(mpBlueMedalCol);


	if (mpEvent != nullptr)
	{
		mpEvent->KilledBlueMedal(this);
	}
}

void CBlueMedal::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�̃R���C�_�[�ł����
	if (self == mpBlueMedalCol)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// ���łɖ��G�̃L�����łȂ����
			if (!IsAttachHitMedalObj(player))
			{
				// ���G���X�g�ɒǉ�
				AddAttachHitMedalObj(player);
				sScore += 50;
				Kill();
			}
		}
		else if (other->Layer() == ELayer::eField)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eBlockCol)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust);
		}
	}
}

void CBlueMedal::SetScore(int score)
{
	sScore = score;
}

int CBlueMedal::GetScore()
{
	return sScore;
}

// �Ǘ�����Ă���C�x���g��ݒ�
void CBlueMedal::SetEvent(CBlueMedalEvent* ev)
{
	mpEvent = ev;
}

void CBlueMedal::Update()
{
	// �d��
	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);

	// ��]
	float rot = 1.0f;
	Rotate(0.0f, rot, 0.0f);

	mIsGround = false;
}

// �`��
void CBlueMedal::Render()
{
	mpBlueMedel->SetColor(mColor);
	mpBlueMedel->Render(Matrix());
}