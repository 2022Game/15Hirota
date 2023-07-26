#ifndef CALIEN_H
#define CALIEN_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CEnemy.h"
#include "CInput.h"
#include "CColliderLine.h"

//class CEnemy;

/*
�G�C���A���N���X
CEnemy�N���X���p��
*/
class CAlien : public CEnemy {
public:
	//�Փˏ���
	void Collision();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	CAlien();
	//CEnemy(���f��, �ʒu, ��], �g�k)
	CAlien(const CVector& pos, const CVector& rot, const CVector& scale);
	//�X�V����
	void Update();
private:
	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2; //�����R���C�_
	CColliderLine mLine3; //�����R���C�_
	CInput mInput;

	CVector mPoint;	//�ڕW�n�_
	int mHp;	//�q�b�g�|�C���g
	CCollider mCollider;	//�R���C�_
	bool IsFoundPlayer() const;	//�v���C���[����������
	std::vector<CAlien*> mCAlien;	//���X�g

	//�G�̏��
	enum class EState
	{
		EIDLE,	//�ҋ@
		ECHASE,	//�ǐ�
		EATTACK,//�U��
	};
	//���݂̏��
	EState mState;
	//�ҋ@
	void UpdateIdle();
	//�ǐ�
	void UpdateChase();
	//�U��
	void UpdateAttack();
};
#endif

//#ifndef CENEMY3_H
//#define CENEMY3_H
////�L�����N�^�N���X�̃C���N���[�h
//#include "CCharacter3.h"
////�R���C�_�N���X�̃C���N���[�h
//#include "CCollider.h"
//
//class CCharacter3;
//
///*
//�G�l�~�[�N���X
//�L�����N�^�N���X���p��
//*/
//class CEnemy3 : public CCharacter3 {
//public:
//	//�R���X�g���N�^
//	CEnemy3();
//	//CEnemy3(�ʒu, ��], �g�k)
//	CEnemy3(CModel* model, const CVector& position, const CVector& rotation,
//		const CVector& scale);
//	//�X�V����
//	void Update();
//	//�Փˏ���
//	//Collision(�R���C�_1, �R���C�_2)
//	void Collision(CCollider* m, CCollider* o);
//	void Collision();
//private:
//	CVector mPoint;	//�ڕW�n�_
//	int mHp;	//�q�b�g�|�C���g
//	//���f���f�[�^
//	static CModel sModel;
//	//�R���C�_
//	CCollider mCollider;
//
//	//�v���C���[�����������ǂ���
//	bool IsFoundPlayer() const;
//
//	std::vector<CEnemy3*> mEnemy3;	//���X�g
//	CModel* mpEnemy3Model;	//���f���f�[�^
//
//	//�G�̏��
//	enum class EState
//	{
//		EIDLE,	//�ҋ@
//		ECHASE,	//�ǐ�
//		EATTACK,//�U��
//	};
//	//���݂̏��
//	EState mState;
//	//�ҋ@
//	void UpdateIdle();
//	//�ǐ�
//	void UpdateChase();
//	//�U��
//	void UpdateAttack();
//};
//
//#endif