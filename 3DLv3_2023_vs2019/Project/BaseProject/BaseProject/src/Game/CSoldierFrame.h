#ifndef CSOLDIERFRAME_H
#define CSOLDIERFRAME_H
class CImage;

#include "CUIBase.h"

class CSoldierFrame :public CUIBase
{
private:
	CImage* mpFrameImage;		// �g�摜

public:
	// �R���X�g���N�^
	CSoldierFrame();
	// �f�X�g���N�^
	~CSoldierFrame();

	// �X�V����
	void Update();

};

#endif