#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
#include "CCollisionManager.h"

class CCollisionManager;

/*
�R���C�_�N���X
�Փ˔���f�[�^
*/

class CCollider : public CTransform, public CTask {
	friend CCollisionManager;
public:
	//�R���X�g���N�^
	//CCollider(�e�A�e�s��A�ʒu�A���a)
	CCollider(CCharacter3* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//�e�|�C���^�̎擾
	CCharacter3* Parent();
	//�f�X�g���N�^
	~CCollider();
	//�Փ˔���
	//Collision(�R���C�_1�A�R���C�_2)
	//return:true(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
	static bool Collision(CCollider* m, CCollider* o);
	//�R���C�_�^�C�v
	enum EType {
		ESPHERE,	//�e�R���C�_
		ETRIANGLE,	//���R���C�_
		ELINE,		//�����R���C�_
	};
	//�f�t�H���g�R���X�g���N�^
	CCollider();

	//CollisionTriangleLine(���R���C�_�A�����R���C�_�A�����l)
	//return:true(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
	//�����l�F�Փ˂��Ă��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleLine(CCollider* triangle, CCollider* line, CVector* abjust);

	EType Type();

	//�`��
	void Render();
protected:
	CCharacter3* mpParent;	//�e
	CMatrix* mpMatrix;		//�e�s��
	float mRadius;			//���a
	EType mType;	//�R���C�_�^�C�v
	CVector mV[3];
};
#endif