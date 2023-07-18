//����N���X�̃C���N���[�h
#include "CWeapon.h"
#include "CApplication.h"
#include "CCollisionManager.h"

#define ROTATION_YV	CVector(0.0f, 1.0f, 0.0f) //��]���x
#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //�ړ����x
#define ROTATION_XV	CVector(1.0f, 0.0f, 0.0f) //��]���x

CWeapon::CWeapon()
	: mAttackCollider
	(
		this,		//�e�̃|�C���^
		&mMatrix,	//�e�̍s��
		CVector(0.0f, 3.0f, 0.3f),	//�����̎n�_
		CVector(0.0f, 3.0f, -0.3f)	//�����̏I�_
	)
{
	mpModel = new CModel();
	mpModel->Load("res\\����.obj", "res\\����.mtl");
}

//CWeapon(�ʒu, ��], �X�P�[��)
CWeapon::CWeapon(const CVector& pos, const CVector& rot, const CVector& scale, const CVector& vel)
	: CWeapon()
{
	CTransform::Update(pos, rot, scale,vel); //�s��̍X�V
}

//�Փ˔���̍X�V����
void CWeapon::Collision()
{
	//�R���C�_�̗D��x�ύX
	mAttackCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Instance()->Collision
	(
		&mAttackCollider,
		COLLISIONRANGE
	);
}

//�Փ˔���
void CWeapon::Collision(CCollider* m, CCollider* o)
{
}

//�X�V����
void CWeapon::Update()
{
	//�ϊ��s��̍X�V
	CTransform::Update();
}