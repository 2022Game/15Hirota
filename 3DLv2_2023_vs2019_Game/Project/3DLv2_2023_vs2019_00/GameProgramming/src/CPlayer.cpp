//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
#include "CApplication.h"
#include "CCollisionManager.h"
#include "CRectangle.h"

#define HP 100	//hp

#define GRAVITY CVector(0.0f,-0.05f,0.0f)	//�d�͉����x

#define JUMP_HGIT CVector(0.0f,5.0f,0.0f)	//�W�����v�̍���
#define JUMP_SHOKI CVector(0.0f,1.0f,0.0f)	//�W�����v�̏���
#define JUMP_OWARI CVector(0.0f,-0.5f,0.0f)	//�W�����v�̏I���̑��x
#define AIR_RESISTANCE CVector(0.0f,-0.5f,0.0f)	//��C��R

#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //��]���x
#define VELOCITY CVector(0.0f, 0.0f, 0.3f) //�ړ����x
#define ROTATION_XV	CVector(2.0f, 0.0f, 0.0f) //��]���x

CPlayer* CPlayer::spInstance = nullptr;

int CPlayer::sHp = 0;	//Hp


CPlayer::CPlayer()
	: mLine(this, &mMatrix, CVector(0.0f, 3.5f, 4.5f), CVector(0.0f, 3.5f, -4.5f))		//�O��
	, mLine2(this, &mMatrix, CVector(0.0f, 6.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f))		//�㉺
	, mLine3(this, &mMatrix, CVector(2.5f, 3.5f, 0.0f), CVector(-2.5f, 3.5f, 0.0f))	//���E
	,mJumpcount(0)
{
	//�C���X�^���X�̐ݒ�
	spInstance = this;
	sHp = HP;
}

//CPlayer(�ʒu, ��], �X�P�[��)
CPlayer::CPlayer(const CVector& pos, const CVector& rot, const CVector& scale)
{
	CTransform::Update(pos, rot, scale); //�s��̍X�V
}

int CPlayer::Hp()
{
	return sHp;
}

//�X�V����
void CPlayer::Update() {
	
	//D�L�[���͂ŉ�]
	if (mInput.Key('D')) {
		//Y���̉�]�l������
		mRotation = mRotation - ROTATION_YV;
	}
	//A�L�[���͂ŉ�]
	if (mInput.Key('A')) {
		//Y���̉�]�l������
		mRotation = mRotation + ROTATION_YV;
	}
	//S�L�[���͂Ō��
	if (mInput.Key('S')) {
		//���ɉ�����
		mPosition = mPosition - VELOCITY * mMatrixRotate;
	}
	//W�L�[���͂őO�i
	if (mInput.Key('W')) {
		//�O�����ɐi��
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	if (mInput.Key(VK_SHIFT))
	{
		if (mInput.Key('W') || mInput.Key('A') || mInput.Key('D'))
		{
			mPosition = mPosition + CVector(0.0f, 0.0f, 0.20f) * mMatrixRotate;
		}
		else
		{
			//�������Ȃ��ł����Ă邩�H
		}
	}
	//�X�y�[�X�L�[���͂ŃW�����v
	if (mInput.PushKey(VK_SPACE)) {

		if (mJumpcount == 0 && mPosition.Y() <= 0.0f)
		{
			//// �W�����v����
			mPosition = mPosition + JUMP_SHOKI + JUMP_HGIT * mMatrixRotate;
			mJumpcount++;
		}
		else if (mJumpcount > 0 && mInput.PushKey(VK_SPACE) && mPosition.Y() > 4.0f) {
			//�W�����v���̏���
			mVelocity = mVelocity + GRAVITY + AIR_RESISTANCE;
			mJumpcount++;
			/*mPosition = mPosition + JUMP_HGIT + JUMP_OWARI * mMatrixRotate;
			mVelocity = mVelocity - AIR_RESISTANCE;*/
			mJumpcount++;
		}
		if (mInput.Key(VK_SPACE) && mPosition.Y() < 2.0f)
		{
			mVelocity = mVelocity - AIR_RESISTANCE * mMatrixRotate;
		}
	}
	else if (!mInput.Key(VK_SPACE) && !(mPosition.Y() <= 0.0f))
	{
		mJumpcount = 0;
	}
	if (GetKeyState(VK_LBUTTON) & 0x80) {
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet->Rotation(mRotation);
		bullet->Update();
		/*CApplication::TaskManager()->Add(bullet);
		bullet.Set(0.1f, 1.5f);
		bullet.Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet.Rotation(mRotation);*/
	}
	if (GetKeyState(VK_RBUTTON) & 0x80) {

	}
	if (GetKeyState(VK_MBUTTON) & 0x80) {

	}

	//�ϊ��s��̍X�V
	CTransform::Update();
	//UI�ݒ�
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());


	//�d�͏���
	mVelocity = mVelocity + GRAVITY;
	//�ړ��ʂ𔽉f
	mPosition = mPosition + mVelocity;	

	//�ړ�����
	if (mPosition.Y() > 0.0f) {	//�n�ʂɐڐG���Ă��Ȃ�
		mPosition = mPosition + mVelocity;
		mVelocity = mVelocity + GRAVITY;
	}
	//�n�ʂɐڐG���Ă���ꍇ�́A�ʒu��n�ʂ̏�ɌŒ肷��
	if (mPosition.Y() <= 0.0f) {
		mPosition = CVector(mPosition.X(), 0.0f, mPosition.Z());
		mVelocity = CVector(mVelocity.X(), 0.0f, mVelocity.Z());
	}

	//���������Ɏg����
	
	////�ʒu����ʊO�ɏo���ꍇ�͏����ʒu�ɖ߂�
	//if (mPosition.Y() < -10.0f)
	//{
	//	mPosition = CVector(0.0f, 0.0f, 0.0f);
	//	mVelocity = CVector(0.0f, 0.0f, 0.0f);
	//}
}

CPlayer* CPlayer::Instance()
{
	return spInstance;
}

void CPlayer::Collision()
{
	//�R���C�_�̗D��x�ύX
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Instance()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mLine3, COLLISIONRANGE);
}

void CPlayer::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::ELINE://�����R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->Type() == CCollider::ETRIANGLE) {2;
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				mVelocity = CVector(0.0f, 0.0f, 0.0f);

				//�s��̍X�V
				CTransform::Update();
			}
			else
			{
				//�d�͏���
				mVelocity =  GRAVITY;
			}
		}
		break;
	}
}