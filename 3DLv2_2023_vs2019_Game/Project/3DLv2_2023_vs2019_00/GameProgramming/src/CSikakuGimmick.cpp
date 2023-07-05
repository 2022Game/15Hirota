#include "CSikakuGimmick.h"
#include "CTaskManager.h"
#include "CPlayer.h"
#include "CTransform.h"
#include "CVector.h"

#define MODEL_SIKAKU "res\\aoiro sikaku1.obj","res\\aoiro sikaku.mtl"

#define MOVE CVector(0.1f,0.0f,0.0f)

const CVector& CSikakuGimmick::Position() const
{
	return mPosition;
}
void CSikakuGimmick::Position(const CVector& v)
{
	mPosition = v;
}

void CSikakuGimmick::Velocity(const CVector& v)
{
	mVelocity = v;
}

void CSikakuGimmick::Init()
{
	//���f���ǂݍ���
	mpSikakuModel = new CModel();
	mpSikakuModel->Load(MODEL_SIKAKU);

	//CreateSikaku(CVector(-100.0f, 4.0f, 20.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	CreateSikaku(CVector(-100.0f, 4.0f, 20.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	mMovingSikakus.push_back(mSikakus.back());
	CreateSikaku(CVector(-120.0f, 8.0f, 20.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	mMovingSikakus.push_back(mSikakus.back());
	CreateSikaku(CVector(-150.0f, 12.0f, 40.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	mMovingSikakus.push_back(mSikakus.back());
	CreateSikaku(CVector(-190.0f, 17.0f, 60.0f), CVector(), CVector(5.0f, 3.0f, 3.0f));
	mMovingSikakus.push_back(mSikakus.back());
	CreateSikaku(CVector(-150.0f, 20.0f, 40.0f), CVector(), CVector(5.0f, 3.0f, 3.0f));
	mMovingSikakus.push_back(mSikakus.back());
	CreateSikaku(CVector(-60.0f, 2.0f, 20.0f), CVector(0.0f,0.0f,-15.0f), CVector(6.0f, 4.0f, 6.0f));
	mMovingSikakus.push_back(mSikakus.back());

	// ����̎l�p�݂̂��ړ��Ώۂɐݒ�
	mMovingSikakus.clear();
	mMovingSikakus.push_back(mSikakus[0]);
	mMovingSikakus.push_back(mSikakus[3]);

	CreateSikaku(CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(6.0f, 3.0f, 6.0f));
	CreateSikaku(CVector(0.0f, 0.0f, 52.75f), CVector(), CVector(6.0f, 3.0f, 6.0f));
	CreateSikaku(CVector(0.0f, 0.0f, 52.75f*2), CVector(), CVector(6.0f, 3.0f, 6.0f));

	// �ړ����������l�p��mMovingSikaku�ɐݒ�
	//mMovingSikaku = mSikakus[0];
	 // ���ׂĂ̎l�p���ړ��Ώۂɐݒ�
	for (int i = 0; i < mSikakus.size(); i++) {
		mMovingSikakus.push_back(mSikakus[i]);
	}

	// ����̎l�p�̈ړ������𔽓]������
	for (int i = 0; i < mMovingSikakus.size(); i++) {
		if (i == 0 || i == 3) {  // ���Ε����Ɉړ����������l�p�̃C���f�b�N�X���w��
			CVector velocity = mMovingSikakus[i]->Velocity();
			mMovingSikakus[i]->Position(mMovingSikakus[i]->Position() - (velocity * 100));  // �����ʒu�𔽑Ε����Ɉړ�
			mMovingSikakus[i]->Velocity(CVector(-velocity.X(), -velocity.Y(), -velocity.Z()));  // �ړ������𔽓]������
		}
	}

}

void CSikakuGimmick::CreateSikaku(CVector& pos, CVector& rot, CVector& scale)
{
	if (mpSikakuModel == nullptr) return;

	// �l�p�𐶐����ă��X�g�ɒǉ�
	CSikaku* sikaku = new CSikaku(mpSikakuModel, pos, rot, scale);
	mSikakus.push_back(sikaku);
}

CSikakuGimmick::CSikakuGimmick()
	:mMoveCounter(0)
	, mMoveDirection(1)
	,mReverseMove(false)
{
	// ��������
	Init();

	// �^�X�N�}�l�[�W���[�Ɏ��g��ǉ�
	CTaskManager::Instance()->Add(this);
}

CSikakuGimmick::~CSikakuGimmick()
{
	// �l�p�̃��f���f�[�^��j��
	if (mpSikakuModel != nullptr)
	{
		delete mpSikakuModel;
	}

	// �l�p��j��
	for (int i = 0; i < mSikakus.size(); i++)
	{
		delete mSikakus[i];
	}
	// �ꉞ���X�g���N���A���Ă���
	mSikakus.clear();

	// �^�X�N�}�l�[�W���[���玩�g����菜��
	CTaskManager::Instance()->Remove(this);
}

void CSikakuGimmick::Update()
{
	// �ǉ�: �J�E���^�[�̃`�F�b�N
	if (mMoveCounter < 100) {
		for (int i = 0; i < mMovingSikakus.size(); i++) {
			CSikaku* sikaku = mMovingSikakus[i];
			if (sikaku != nullptr) {
				sikaku->Position(sikaku->Position() + (MOVE * mMoveDirection)); // �ʒu�𒼐ڕύX����
			}
		}
		mMoveCounter++;
	}
	else {
		mMoveDirection *= -1; // �ړ������𔽓]������
		mMoveCounter = 0; // �J�E���^�[�����Z�b�g
	}

	//// �ǉ�: �J�E���^�[�̃`�F�b�N
	//if (mMoveCounter < 100) {
	//	Position(Position() + (MOVE * mMoveDirection)); // �ʏ�̈ړ�
	//	mMoveCounter++;
	//}
	//else {
	//	mMoveDirection *= -1; // �ړ������𔽓]������
	//	mMoveCounter = 0; // �J�E���^�[�����Z�b�g
	//}

	// �v���C���[���l�p�ɐڒn�������ǂ����̔���
	for (int i = 0; i < mSikakus.size(); i++) {
		CSikaku* sikaku = mSikakus[i];
		if (sikaku != nullptr) {
			break;
		}
	}
}

	//// �v���C���[���l�p�ɐڒn���Ă���ꍇ�̏���
	//if (playerGrounded) {
	//	// �v���C���[���l�p�ɐڒn���Ă���ꍇ�̏��������s
	//	CSikaku* sikaku;
	//	if (mPosition.Y() <= sikaku->EPLAYER) {
	//		mPosition = CVector(mPosition.X(), sikaku->EPLAYER, mPosition.Z());
	//		mVelocity = CVector(mVelocity.X(), 0.0f, mVelocity.Z());
	//	}
	//}
	//else {
	//	// �v���C���[���l�p�ɐڒn���Ă��Ȃ��ꍇ�̏��������s
	//	false;
	//}