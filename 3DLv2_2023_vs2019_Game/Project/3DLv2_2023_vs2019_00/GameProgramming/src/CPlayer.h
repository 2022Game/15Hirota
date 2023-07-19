#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter3.h"
#include "CInput.h"
#include "CBullet.h"
#include "CColliderLine.h"
#include"CWeapon.h"

/*
�v���C���[�N���X
�L�����N�^�N���X���p��
*/
class CPlayer : public CCharacter3 {
public:
	//�C���X�^���X�̃|�C���^�̎擾
	static CPlayer* Instance();
	//�Փˏ���
	void Collision();

	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);

	//CBullet bullet;
	CPlayer();
	//CPlayer(�ʒu, ��], �X�P�[��)
	CPlayer(const CVector& pos, const CVector& rot, const CVector& scale);

	static int Hp();
	//�X�V����
	void Update();

private:
	//�v���C���[�̃C���X�^���X
	static CPlayer* spInstance;

	static int sHp;

	CColliderLine mLine; //�����R���C�_
	CColliderLine mLine2; //�����R���C�_
	CColliderLine mLine3; //�����R���C�_
	CInput mInput;
	//�v���C���[�̎����Ă��镐��
	CWeapon* mpWeapon;
	
	int mJumpcount;	//�W�����v�̉񐔏���
	bool isOnObstacle;	//��Q���ɏ���Ă��邩�ǂ����̃t���O
	bool disableGravity; // ��Q����ŏd�͂𖳌������邽�߂̃t���O
	bool isOnObstacleJump;	//��Q���ɏ���Ă��邩
	bool isJumping;	//�W�����v����
	bool isDodging;	//��𒆂��ǂ����̃t���O
};

#endif
