#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include <stdio.h>

#define VELOCITY 2.0f	//�ړ����x

class CCharacter : public CRectangle
{
public:
	enum class ETag
	{
		EZERO,		//�����l
		EBULLET,	//�e
		EENEMY,		//�G
		EITEM,		//�A�C�e��
		EPLAYER,	//�v���C���[
		ETURN,		//�܂�Ԃ�
		EBLOCK,		//�u���b�N
		EBLOCK2,	//����u���b�N
		EBLOCK3,	//���u���b�N
		EBLOCK4,	//�n�e�i�u���b�N
		EBLOCK5,	//�K�i�u���b�N
		EDOKAN,     //�y��
		EBACK,	    //�w�i
		EGOAL,		//�S�[���u���b�N
		EMOVEBLOCK,	//�ړ��u���b�N��
		EMOVEBLOCK2,//�ړ��u���b�N�c
		EFALLING,	//������
	};
	enum class EState	//���
	{
		EMOVE,		//�ړ�
		EFALL,		//�������
		ESTOP,		//��~
		EJUMP,		//�W�����v
		ECRY,		//����
	};
protected:
	float mVx;	//X�����x
	float mVy;	//Y�����x
	bool mEnabled;
	ETag mTag;
	EState mState;
private:
	CTexture *mpTexture;
	int mLeft, mRight, mBottom, mTop;
public:
	EState State();	//��Ԃ��擾����
	bool Enabled();
	ETag Tag();
	float Vx();	//	�u���b�N�ɏ�������̃L�����N�^�[�̃X�s�[�h�𑫂�(x��)
	float Vy(); //	�u���b�N�ɏ�������̃L�����N�^�[�̃X�s�[�h�𑫂�(y��)
	//�Փˏ����Q
	virtual void Collision() {};
	//�Փˏ����S
	//Collision(�����̃|�C���^, �Փˑ���̃|�C���^)
	virtual void Collision(CCharacter* m, CCharacter* o) {};
	virtual void Update() = 0;
	CCharacter();
	CTexture* Texture();
	void Texture(CTexture *pTexture, int left, int right, int bottom, int top);
	virtual void Render();
	void Move();
};