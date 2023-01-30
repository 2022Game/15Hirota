#pragma once
#include "CUi.h"
#include "CPlayer2.h"
#include <Windows.h>

//�萔�̒�`

#define TEXTURE "image.png" //�e�N�X�`���̃t�@�C����
#define TIPSIZE 40.0f //�}�b�v�v�f�̃T�C�Y

#define TEXTURE_E1 "pngaaa.com-3726776.png"
#define TIPSIZE_E1 35.0f

#define TEXTURE_D "Dokan.png"
#define TIPSIZE_D 130.0f

#define TEXTURE_B1 "kindpng_2063012.png"
#define TIPSIZE_B1 40.0f

#define TEXTURE_B2 "kindpng_2063012.png"
#define TIPSIZE_B2 35.0f

#define TEXTURE_B3 "kindpng_2063012.png"
#define TIPSIZE_B3 35.0f

#define TEXTURE_B4 "pngaaa.com-3726776.png"
#define TIPSIZE_B4 40.0f

//#define TEXCOORD_NO_ITEM "pngaaa.com-3726776.png"
//#define TIPSIZE_B4 35.0f

#define TEXTURE_BACK "pixel-background-png-4.png"
#define TIPSIZE_BACK 40.0f

#define TEXTURE_GOAL "pngaaa.com-3726776.png"
#define TIPSIZE_GOAL 500.0f

#define TEXTURE_KINOKO "pngaaa.com-3726776.png"
#define TIPSIZE_KINOKO 40.0f

#define TEXTURE_MoveBlock "pngaaa.com-3726776.png"
#define TIPSIZE_MoveBlock 20.0f

#define TEXTURE_MoveBlock2 "pngaaa.com-3726776.png"
#define TIPSIZE_MoveBlock2 20.0f

/*
* CGame�N���X
* �Q�[���N���X
* �Q�[���̃}�b�v���쐬���A
* �L�����N�^��z�u����
*/
class CGame
{
public:
	//�f�X�g���N�^
	~CGame();
	//�Q�[���N���A����
	bool IsClear();
	//�Q�[���N���A����
	void Clear();
	//�Q�[���I�[�o�[����
	bool IsOver();
	//�Q�[���I�[�o�[����
	void Over();
	//�X�^�[�g����
	void Start();
	CGame(); //�f�t�H���g�R���X�g���N�^�i���������j
	void Update(); //�X�V����
private:
	int mCdx, mCdy; //�J�����ƃv���C���[�̍��W�̍���
	void CameraSet(); //�J�����ݒ�
	CPlayer2* mpPlayer; //�v���C���[�̃|�C���^
	int mTime; //�o�ߎ���
	int mScore;	//�X�R�A
	CUi* mpUi; //UI�N���X�̃|�C���^
};
