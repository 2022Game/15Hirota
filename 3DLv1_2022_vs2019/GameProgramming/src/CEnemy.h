#ifndef CENEMY_H
#define CENEMY_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
//�G�t�F�N�g�N���X�̃C���N���[�h
#include "CEffect.h"

/*
�G�l�~�[�N���X
�L�����N�^�N���X���p��
*/
class CEnemy : public CCharacter3 {
public:
	//�R���X�g���N�^
	//CEnemy(���f���A�ʒu�A��]�A�g�k)
	CEnemy(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
public:
	//�m�F�p���\�b�h�@�폜�\��
	/*void CEnemy::Render() {
		CCharacter3::Render();
		mCollider1.Render();
		mCollider2.Render();
		mCollider3.Render();
	}*/
public:
	//�Փˏ���
	//Collision(�R���C�_�P�A�R���C�_�Q)
	void Collision(CCollider* m, CCollider* o);

	//�X�V����
	void Update();
private:
	//�R���C�_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};
#endif