#pragma once
#include "CCharacter.h"
/*
* CDokan
*�w�i�N���X
*�w�i�Ɏg��
*/
class CBackground : public CCharacter
{
public:
	//CBackground(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CBackground(float x, float y, float w, float h, CTexture* pt);
	//Update�ł͉������Ȃ�
	void Update() {}
};