#pragma once
#include "CCharacter.h"
/*
* CGoal
* �S�[��
* �}�b�v�̃S�[���Ɏg�p����
*/
class CGoal : public CCharacter
{
public:
	//CGOAL(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CGoal(float x, float y, float w, float h, CTexture* pt);
	//Update�ł͉������Ȃ�
	void Update() {}
};
