#include "CSikakuGimmick.h"
#include "CTaskManager.h"
#include "CPlayer.h"
#include "CTransform.h"
#include "CVector.h"

#define MODEL_SIKAKU "res\\aoiro sikaku1.obj","res\\aoiro sikaku.mtl"

const CVector& CSikakuGimmick::Position()
{
	return mPosition;
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

	CreateSikaku(CVector(-100.0f, 4.0f, 20.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	CreateSikaku(CVector(-120.0f, 8.0f, 20.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	CreateSikaku(CVector(-150.0f, 12.0f, 40.0f), CVector(), CVector(6.0f, 4.0f, 6.0f));
	CreateSikaku(CVector(-190.0f, 17.0f, 60.0f), CVector(), CVector(5.0f, 3.0f, 3.0f));
	CreateSikaku(CVector(-150.0f, 20.0f, 40.0f), CVector(), CVector(5.0f, 3.0f, 3.0f));

}

void CSikakuGimmick::CreateSikaku(CVector& pos, CVector& rot, CVector& scale)
{
	if (mpSikakuModel == nullptr) return;

	// �l�p�𐶐����ă��X�g�ɒǉ�
	CSikaku* sikaku = new CSikaku(mpSikakuModel, pos, rot, scale);
	mSikakus.push_back(sikaku);
}

CSikakuGimmick::CSikakuGimmick()
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