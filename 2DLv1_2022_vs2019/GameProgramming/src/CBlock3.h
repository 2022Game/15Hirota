#pragma once
#include "CCharacter.h"
/*
* CBlock
* �u���b�N�N���X
* �}�b�v�̃u���b�N�Ɏg�p����
*/
class CBlock3 : public CCharacter
{
public:
	//CBlock(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CBlock3(float x, float y, float w, float h, CTexture* pt);

public:
	bool flag_B;

	//Update�ł͉������Ȃ�
	void Update() {}
};
