#include "CPicoSword.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPicoChan.h"
#include "CEnemy.h"

CPicoSword::CPicoSword()
	: mpPicoChan(nullptr)
{
	mpSword = CResourceManager::Get<CModel>("MajicSwordPico");

	// �U������p�̃R���C�_�[���쐬
	mpAttackCol = new CColliderLine
	(
		this, ELayer::eAttackCol,
		CVector(0.0f, 0.0f, -0.2f),
		CVector(0.0f, 1.7f, -0.4f)
	);
	// �U������p�̃R���C�_�[�ƏՓ˔�����s��
	// ���C���[�ƃ^�O��ݒ�
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::ePlayer });

	// �ŏ��͍U������p�̃R���C�_�[���I�t�ɂ��Ă���
	mpAttackCol->SetEnable(false);
}

CPicoSword::~CPicoSword()
{
	// �R���C�_�[��j��
	SAFE_DELETE(mpAttackCol);
}

// �Փˏ���
void CPicoSword::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�R���C�_�[�ł����
	if (self == mpAttackCol)
	{
		// �L�����̃|�C���^�ɕϊ�
		CCharaBase* chara = dynamic_cast<CCharaBase*>(other->Owner());
		// ����̃R���C�_�[�̎����傪�L�����ł����
		if (chara != nullptr)
		{
			// ���łɍU���ς݂̃L�����łȂ����
			if (!IsAttackHitObj(chara))
			{
				//�@�_���[�W��^����
				chara->TakeDamage(2);

				// �U���ς݃��X�g�ɒǉ�
				AddAttackHitObj(chara);
			}
		}
	}
}

// �U���J�n
void CPicoSword::AttackStart()
{
	// ���łɍU�����ł���΁A�T�C�h�J�n�����͎��s���Ȃ�
	if (mIsAttack) return;

	CWeaponEnemy::AttackStart();
	// �U�����n�܂�����A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(true);
}

// �U���I��
void CPicoSword::AttackEnd()
{
	CWeaponEnemy::AttackEnd();
	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(false);
}

void CPicoSword::SetPicoChanInstance(CPicoChan* pPicoChan)
{
	mpPicoChan = pPicoChan;
}

// ����̍s����擾
CMatrix CPicoSword::Matrix() const
{
	const CMatrix* attachMtx = GetAttachMtx();
	// ��Ɏ����Ă��Ȃ��Ƃ��́A�������g�̍s���Ԃ�
	if (attachMtx == nullptr)
	{
		return CTransform::Matrix();
	}
	// ��Ɏ����Ă���Ƃ��́A�A�^�b�`���Ă���s���Ԃ�
	else
	{
		CMatrix sm;
		sm.Scale(47.0f, 47.0f, 47.0f);

		if (mpPicoChan && mpPicoChan->IsAttack())
		{
			CMatrix translate;
			// X��(������)
			// Y��(�c����)
			// Z��(�O����)
			translate.Translate(4.0f, 0.0f, -44.0f);

			// 90�x��]��\���s����쐬
			CMatrix rotateY;
			CMatrix rotateZ;
			CMatrix rotateX;

			rotateY.RotateY(90.0f);		// Y��
			rotateX.RotateX(-92.0f);		// X��
			rotateZ.RotateZ(0.0f);		// Z��

			return sm * rotateY * rotateX * rotateZ * translate * (*attachMtx);
		}
		else
		{
			CMatrix translate;
			translate.Translate(0.0f, -8.0f, 17.0f);

			// 90�x��]��\���s����쐬
			CMatrix rotateY;
			CMatrix rotateZ;
			CMatrix rotateX;

			rotateY.RotateY(0.0f);		// Y��
			rotateX.RotateX(0.0f);		// X��(�O��)
			rotateZ.RotateZ(-30.0f);		// Z��(���E)

			return sm * rotateY * rotateX * rotateZ * translate * (*attachMtx);
		}
	}
}

// �X�V����
void CPicoSword::Update()
{

}

// �`�揈��
void CPicoSword::Render()
{
	mpSword->SetColor(mColor);
	mpSword->Render(Matrix());
}