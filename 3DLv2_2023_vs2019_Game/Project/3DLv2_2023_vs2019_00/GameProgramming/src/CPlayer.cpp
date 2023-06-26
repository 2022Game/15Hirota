//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"
#include "CApplication.h"
#include "CCollisionManager.h"
#include "CRectangle.h"

//�G�l�~�[�N���X�ɃC���N���[�h����
#include <math.h>
#define M_PI        3.14159265358979323846264338327950288

const CVector GRAVITY(0.0f, -0.007f, 0.0f);

#define HP 100	//hp

#define JUMP_START CVector(0.0f,0.3f,0.0f)	//�W�����v����
#define JUMP_FORCE CVector(0.0f,0.35f,0.0f)

#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //��]���x
#define VELOCITY CVector(0.0f, 0.0f, 0.3f) //�ړ����x
#define ROTATION_XV	CVector(2.0f, 0.0f, 0.0f) //��]���x

CPlayer* CPlayer::spInstance = nullptr;

int CPlayer::sHp = 0;	//Hp

CPlayer::CPlayer()
	: mLine(this, &mMatrix, CVector(0.0f, 3.5f, 5.0f), CVector(0.0f, 3.5f, -5.0f))		//�O��
	, mLine2(this, &mMatrix, CVector(0.0f, 6.0f, 0.0f), CVector(0.0f, -0.5f, 0.0f))		//�㉺
	, mLine3(this, &mMatrix, CVector(3.5f, 3.5f, 0.0f), CVector(-3.5f, 3.5f, 0.0f))	//���E
	, mJumpcount(0)
	,isOnObstacle(false)
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
			Position(Position() + CVector(0.0f, 0.0f, 0.20f) * MatrixRotate());
			
		}
		else
		{
			//�������Ȃ��ł����Ă�H
		}
	}
	bool isGrounded = Position().Y() <= 0.0f;
	//�ڒn���Ă��邩
	bool isJumpKeyPressed = mInput.PushKey(VK_SPACE);	//�����Ă��邩
	bool isJumping = false;	//�W�����v����
	bool wasOnObstacle = false; // �O�t���[���ŏ�Q���ɏ���Ă������������t���O

	//�W�����v����
	if (isJumpKeyPressed) {
		if ((mJumpcount == 0 && isGrounded) || (Velocity().Y() <= 0.0f && isGrounded) || Velocity().Y() == 0.0f) {
				// �W�����v����
				Velocity(Velocity() + JUMP_START * MatrixRotate());
				mJumpcount = 1;
				isJumping = true;
			}
		if (isOnObstacle && isGrounded) {
			// �W�����v����
			Velocity(Velocity() + JUMP_FORCE * MatrixRotate());
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

	if (!isOnObstacle && !isGrounded) {
		Velocity(Velocity() + GRAVITY);
	}

	// �d�͂���ɉ��Z����
	Velocity(Velocity() + GRAVITY);
	/*if (!isOnObstacle && !isGrounded) {
		Velocity(Velocity() + GRAVITY);
	}*/

	//�ړ�����
	Position(Position() + Velocity());

	// �㏸���܂��͒��n�����ꍇ�̏���
	if (mJumpcount > 0 && Velocity().Y() > 0.0f && !isJumpKeyPressed) {
		mJumpcount = 0; // �󒆂ł̃W�����v�𖳌���
	}

	if (isGrounded && Velocity().Y() <= 0.0f) {
		Position(CVector(Position().X(), 0.0f, Position().Z()));
		Velocity(CVector(Velocity().X(), 0.0f, Velocity().Z()));
		if (isGrounded) {
			mJumpcount = 0; //�n�ʂɒ��n������W�����v�J�E���g�����Z�b�g
		}
	}
	if (isOnObstacle) {
		mJumpcount = 1;
	}

	/*if (Position().Y() > 0.0f && Velocity().Y() < 0.0f) {
		Position(CVector(Position().X(), 0.0f, Position().Z()));
		Velocity(CVector(Velocity().X(), 0.0f, Velocity().Z()));
		isGrounded = true;
		mJumpcount = 0;
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
			if (CCollider::CollisionTriangleLine(o, m, &adjust)) {

				bool isGrounded = Position().Y() <= 0.0f;

				// �ʒu�̍X�V
				Position(Position() + adjust);

				if (!isOnObstacle) {
					// �ړ��x�N�g���𒲐�
					CVector velocity = Velocity();
					velocity.SetY(0.0f);
					Velocity(velocity);

					// �ړ�����
					Position(Position() - Velocity());

					isOnObstacle = true;
				}
				else {
					isOnObstacle = false;
				}
			}
		}
		break;
	}
}
//	//�ʒu�̍X�V(mPosition + adjust)
			//	Position(Position() + adjust);

			//	/*Velocity(Velocity() + adjust);*/

			//	// �s��̍X�V
			//	CTransform::Update();

			//	//�ʒu�̍X�V(mPosition + adjust)
			//	Position(Position() + adjust);

			//	if (!isOnObstacle) {
			//		//�ړ�����
			//		Position(Position() + Velocity());
			//	}
			//}