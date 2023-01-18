#include "CBullet.h"
#define BULLET_VELOCITY CVector(0.0f,0.0f,1.0f)//�e�̑��x

CBullet::CBullet()
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.1f)
	,mLife(50)
{}

//���Ɖ��s���̐ݒ�
//Set(���A���s��)
void CBullet::Set(float w, float d) {
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ�
	mT.Vertex(CVector(w,0.0f,0.0f), CVector(0.0f,0.0f,-d), CVector(-w,0.0f,0.0f));
	//�O�p�`�̖@���ݒ�
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

//�Փˏ���
//Collidsion(�R���C�_�P�A�R���C�_�Q)
void CBullet::Collision(CCollider* m, CCollider* o) {
	//�R���C�_��m��o���Փ˂��Ă��邩����
	if (CCollider::Collision(m, o)) {
		//�Փ˂��Ă���Ƃ��͖����ɂ���
		mEnabled = false;
	}
}

//�X�V
void CBullet::Update() {
	//�������Ԃ̔���
	if (mLife-- > 0) {
		CTransform::Update();
		//�ʒu�X�V
		mPosition = mPosition + BULLET_VELOCITY * mMatrixRotate;
	}
	else {
		//�����ɂ���
		mEnabled = false;
	}
}

//�`��
void CBullet::Render() {
	//DIFFUSE���F�ݒ�
	float c[] = { 1.0f,1.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	mT.Render(mMatrix);
	//mCollider.Render();
}