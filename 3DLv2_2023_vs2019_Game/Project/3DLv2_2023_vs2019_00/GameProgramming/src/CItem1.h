#ifndef CITEM1_H
#define CITEM1_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CEnemy.h"
#include "CInput.h"
#include "CColliderLine.h"

class CEnemy;

/*
�A�C�e���N���X
CEnemy�N���X���p��
*/
class CItem1 : public CEnemy {
public:
	//�Փˏ���
	void Collision();
	//�Փˏ���
	//Collision(�R���C�_1, �R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	CItem1();
	//CItem1(���f��, �ʒu, ��], �g�k)
	CItem1(const CVector& pos, const CVector& rot, const CVector& scale);
	//�X�V����
	void Update();
private:
	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2; //�����R���C�_
	CColliderLine mLine3; //�����R���C�_
	CInput mInput;
};
#endif

//#ifndef CITEM1_H
//#define CITEM1_H
////�L�����N�^�N���X�̃C���N���[�h
//#include "CCharacter3.h"
//#include "CCollider.h"
//
///*
//�G�l�~�[�N���X
//�L�����N�^�N���X���p��
//*/
//class CItem1 : public CCharacter3 {
//public:
//	//�Փˏ���
//	void Collision();
//	//�Փˏ���
//	//Collision(�R���C�_1, �R���C�_2)
//	void Collision(CCollider* m, CCollider* o);
//	////�m�F�p���\�b�h�@�폜�\��
//	//void CEnemy::Render() {
//	//	CCharacter3::Render();
//	//	mCollider1.Render();
//	//	mCollider2.Render();
//	//	mCollider3.Render();
//	//}
//
//	//�R���X�g���N�^
//	//CEnemy(���f��, �ʒu, ��], �g�k)
//	CItem1(CModel* model, const CVector& position,
//		const CVector& rotation, const CVector& scale);
//	//�X�V����
//	void Update();
//private:
//	//�R���C�_
//	CCollider mCollider1;
//	CCollider mCollider2;
//	CCollider mCollider3;
//
//};
//
//#endif