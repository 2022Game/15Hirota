#pragma once
#include "CCharacter.h"
/*
* CDokan
*�y�ǂ̃N���X
*�}�b�v�̃u���b�N�Ɏg��
*/
class CDokan : public CCharacter
{
public:
	//CDokan(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CDokan(float x, float y, float w, float h, CTexture* pt);
	//Update�ł͉������Ȃ�
	void Update() {}
};
