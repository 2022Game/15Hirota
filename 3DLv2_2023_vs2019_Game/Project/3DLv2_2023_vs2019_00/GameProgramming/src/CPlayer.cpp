//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
#include "CApplication.h"
#include "CCollisionManager.h"
#include "CRectangle.h"

#define HP 100	//hp

#define GRAVITY CVector(0.0f,-0.05f,0.0f)	//�d�͉����x

#define JUMP_START CVector(0.0f,0.75f,0.0f)	//�W�����v����

#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //��]���x
#define VELOCITY CVector(0.0f, 0.0f, 0.3f) //�ړ����x
#define ROTATION_XV	CVector(2.0f, 0.0f, 0.0f) //��]���x

CPlayer* CPlayer::spInstance = nullptr;

int CPlayer::sHp = 0;	//Hp

CPlayer::CPlayer()
	: mLine(this, &mMatrix, CVector(0.0f, 3.5f, 5.0f), CVector(0.0f, 3.5f, -5.0f))		//�O��
	, mLine2(this, &mMatrix, CVector(0.0f, 6.0f, 0.0f), CVector(0.0f, -0.5f, 0.0f))		//�㉺
	, mLine3(this, &mMatrix, CVector(3.5f, 3.5f, 0.0f), CVector(-3.5f, 3.5f, 0.0f))	//���E
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

int CPlayer::Hp()	//HP
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
		Position(Position() - VELOCITY * MatrixRotate());
	}
	//W�L�[���͂őO�i
	if (mInput.Key('W')) {
		//�O�����ɐi��
		Position(Position() + VELOCITY * MatrixRotate());
	}
	if (mInput.Key(VK_SHIFT))	//�_�b�V������
	{
		if (mInput.Key('W') || mInput.Key('A') || mInput.Key('D'))
		{
			Position(Position() + CVector(0.0f, 0.0f, 0.20f) * mMatrixRotate);
		}
		else
		{
			//�������Ȃ��ł����Ă�H
		}
	}
	bool isGrounded = mPosition.Y() <= 0.0f || mVelocity.Y() == 0.0f;	//�ڒn���Ă��邩
	bool isJumpKeyPressed = mInput.PushKey(VK_SPACE);	//�����Ă��邩

	if (isJumpKeyPressed) {
		if ((mJumpcount == 0 && isGrounded) || (mVelocity.Y() <= 0.0f && isGrounded)) {
			// �W�����v����
			mVelocity = JUMP_START * MatrixRotate();
			mJumpcount = 1;
		}
	}
	if (GetKeyState(VK_LBUTTON) & 0x80) {	//�}�E�X���@�U��
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * Matrix());
		bullet->Rotation(mRotation);
		bullet->Update();
		/*CApplication::TaskManager()->Add(bullet);
		bullet.Set(0.1f, 1.5f);
		bullet.Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet.Rotation(mRotation);*/
	}
	if (GetKeyState(VK_RBUTTON) & 0x80) {
		//����
	}
	if (GetKeyState(VK_MBUTTON) & 0x80) {
		//����
	}

	//�ϊ��s��̍X�V
	CTransform::Update();
	//UI�ݒ�
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());

	// �d�͏���
	if (!isGrounded) {
		mVelocity = mVelocity + GRAVITY;
		Position(Position() + GRAVITY);
	}

	//�ړ�����
	Position(Position() + mVelocity);

	////�㏸���܂��͒��n�����ꍇ�̏���
	//	if (mJumpcount > 0 && mVelocity.Y() > 0.0f) {
	//		mJumpcount = 0; //�󒆂ł̃W�����v�𖳌���
	//	}

	// �㏸���܂��͒��n�����ꍇ�̏���
	if (mJumpcount > 0 && mVelocity.Y() > 0.0f && !isJumpKeyPressed) {
		mJumpcount = 0; // �󒆂ł̃W�����v�𖳌���
	}

	if (isGrounded && mVelocity.Y() <= 0.0f) {
		Position(CVector(mPosition.X(), 0.0f, mPosition.Z()));
		mVelocity = CVector(mVelocity.X(), 0.0f, mVelocity.Z());
		if (isGrounded) {
			mJumpcount = 0; //�n�ʂɒ��n������W�����v�J�E���g�����Z�b�g
		}
	}

	//���������Ɏg���邩���H
	//�ʒu����ʊO�ɏo���ꍇ�͏����ʒu�ɖ߂�
	/*if (mPosition.Y() < -10.0f)
	{
		mPosition = CVector(0.0f, 0.0f, 0.0f);
		mVelocity = CVector(0.0f, 0.0f, 0.0f);
	}*/
}

//�v���C���[�̃C���X�^���X
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
	//mLine4.ChangePriority();
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
			if (CCollider::CollisionTriangleLine(o, m, &adjust)){
				//�ʒu�̍X�V(mPosition + adjust)
				Position(Position() + adjust);

				//�s��̍X�V
				CTransform::Update();
			}
		}
		break;
	}
}