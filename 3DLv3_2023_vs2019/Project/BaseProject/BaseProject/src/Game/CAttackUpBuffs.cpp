#include "CAttackUpBuffs.h"
#include "CPlayer.h"

// �R���X�g���N�^
CAttackUpBuffs::CAttackUpBuffs(CObjectBase* owner, const CVector& pos, const CVector& dir,
	float speed, float dist)
	: CObjectBase(ETag::eEffect, ETaskPriority::eEffect, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mKillMoveDist(dist)
	, mMovedDist(0.0f)
{
	Position(pos);
	mMoveSpeed = dir.Normalized() * speed;
	Rotation(CQuaternion::LookRotation(mMoveSpeed, CVector::up));

	mpModel = CResourceManager::Get<CModel>("LineEffect");
	mpModel->SetupEffectSettings();
}

// �f�X�g���N�^
CAttackUpBuffs::~CAttackUpBuffs()
{

}

// �X�V����
void CAttackUpBuffs::Update()
{
	// ��]
	float rot = 10.0f;
	Rotate(0.0f, rot, 0.0f);

	// �ړ����x���v�Z
	CVector move = mMoveSpeed * Time::DeltaTime();
	// move�̃x�N�g���̒������i�[
	float dist = move.Length();
	// mMoveDist���AmKillMoveDist�ȏ�ɂȂ������ǂ���
	if (mMovedDist + dist >= mKillMoveDist)
	{
		// �I�u�W�F�N�g���ő勗���ɒB����܂ł̎c��̋������v�Z
		dist = mKillMoveDist - mMovedDist;
		// �ړ��x�N�g�������̎c�苗���Ɋ�Â��Ē���
		move = move.Normalized() * dist;
	}
	// �I�u�W�F�N�g�̈ʒu���X�V���āA���m�ɂ��̎c�苗�������ړ�
	Position(Position() + move);

	// ���݂̃t���[���ňړ���������dist��ݐψړ�����mMovedDist�ɉ��Z
	mMovedDist += dist;
	// �ݐψړ�������mKillMoveDist�ȏ�ɂȂ������ǂ���
	if (mMovedDist >= mKillMoveDist)
	{
		// �폜
		Kill();
	}

	CPlayer* player = CPlayer::Instance();
	bool clear = player->IsStageClear();
	if (clear)
	{
		Kill();
	}
}

// �`�揈��
void CAttackUpBuffs::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}