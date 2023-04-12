#include "CEnemy3.h"

#define OBJ "res\\f16.obj"	//���f���̃t�@�C��
#define MTL "res\\f16.mtl"	//���f���̃}�e���A���t�@�C��

//�ړ����x
#define VELOCITY 0.11f	//���x

#define HP 3	//�ϋv�l


CModel CEnemy3::sModel;	//���f���̃f�[�^�쐬

//�R���X�g���N�^
CEnemy3::CEnemy3()
	:CCharacter3(1)
	, mHp(HP)
	, mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4)
{
	//���f�����Ȃ��Ƃ��͓ǂݍ���
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &sModel;

	//�ڕW�n�_�̐ݒ�
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
}

//CEnemy3(�ʒu�A��]�A�g�k)
CEnemy3::CEnemy3(const CVector& position, const CVector& rotation,
	const CVector& scale)
	:CEnemy3()	//�f�t�H���g�R���X�g���N�^�����s����
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�
	CTransform::Update();	//�s��̍X�V
}

//�Փˏ���
//COllision(�R���C�_�P�A�R���C�_�Q)
void CEnemy3::Collision(CCollider* m, CCollider* o)
{
	//����̃R���C�_�^�C�v�̔���
	switch (o->Type())
	{
	case CCollider::ESPHERE:	//���R���C�_�̎�
		//�R���C�_��m��y���Փ˂��Ă��邩����
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă���Ƃ��͖����ɂ���
			//mEnagled = false;
			mHp--;
		}
		break;
	case CCollider::ETRIANGLE:	//���R���C�_�̎�
		CVector abjust;	//�����l
		//���R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &abjust))
		{
			//���j�Œn�ʂɏՓ˂���Ɩ���
			if (mHp <= 0)
			{
				mEnabled = false;
			}
		}
		break;
	}
}

void CEnemy3::Collision()
{
	mCollider.ChangePriority();

	CCollisionManager::Instance()->Collision(&mCollider, COLLISIONRANGE);
}

//�X�V����
void CEnemy3::Update()
{
	//�v���C���[�̃|�C���^��0�̈ȊO�̎�
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		//�v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = player->Position() - mPosition;
		//���x�N�g���Ƃ̓��ς����߂�
		float dx = vp.Dot(mMatrixRotate.VectorX());
		//��x�N�g���Ƃ̓��ς����߂�
		float dy = vp.Dot(mMatrixRotate.VectorY());
		//�O��̃x�N�g���Ƃ̓��ς����߂�
		float dz = vp.Dot(mMatrixRotate.VectorZ());

		//X���̂��ꂪ2.0�ȉ�
		if (-2.0f < dx && dx < 2.0f)
		{
			//Y���̂��ꂪ2.0�ȉ�
			if (-2.0f < dy && dy < 2.0f)
			{
				//Z���̂��ꂪ2.0�ȉ�
				if (0.0f < dz && dz < 30.0f)
				{
						//�e�𔭎˂��܂�
						CBullet* bullet = new CBullet();
						bullet->Set(0.1f, 1.5f);
						bullet->Position(
							CVector(0.0f, 0.0f, 10.0f) * mMatrix);
						bullet->Rotation(mRotation);
						bullet->Update();
				}
			}
		}
		//HP��0�ȉ��̎��@���j
		if (mHp <= 0)
		{
			mHp--;
			//15�t���[�����ɃG�t�F�N�g
			if (mHp % 15 == 0)
			{
				//�G�t�F�N�g����
				new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			}
			//���~������
			mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
			CTransform::Update();
			return;
		}
	}
	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	//�ۑ�
	//���x�N�g���Ƃ̓��ς����߂�
	float dx = vp.Dot(mMatrixRotate.VectorX());
		//��x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(mMatrixRotate.VectorY());
	const float margin = 0.1f;
	//���E�����։�]
	if (dx > margin)
	{
		mRotation = mRotation + CVector(0.0f, 1.0f, 0.0f);	//���։�]
	}
	else if (dx < -margin)
	{
		//�ۑ�
		mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f);
	}
	//������։�]
	if (dy > margin)
	{
		mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f);	//��։�]
	}
	else if (dy < -margin)
	{
		//�ۑ�
		mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f);
	}

	//�@�̑O���ֈړ�����
	mPosition = mPosition + mMatrixRotate.VectorZ() * VELOCITY;
	CTransform::Update();	//�s��X�V

	//���悻3�b���ɖڕW�n�_���X�V
	int r = rand() % 180;	//rand()�͐����̗�����Ԃ�
							//% 180�@��180�Ŋ������]������߂�
	if (r == 0)
	{
		if (player != nullptr)
		{
			mPoint = player->Position();
		}
		else
		{
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}
}