#pragma once
#define WINDOW_WIDTH 1280	//�E�B���h�E�̕�
#define WINDOW_HEIGHT 720	//�E�B���h�E�̍���
//#define FULL_SCREEN	//�t���X�N���[���ɂ���ꍇ�͒�`����
#define GAME3D	//3D�Q�[���̏ꍇ�͒�`����

//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

//���\�[�X�t�@�C���t�H���_
#define RES_DIR "res\\"
//�̈������}�N����
#define SAFE_DELETE(del) {if(del != nullptr) delete del; del = nullptr;}
//���I�z��̗̈������}�N����
#define SAFE_DELETE_ARRAY(ary) {if(ary != nullptr) delete[] ary; ary = nullptr;}



#include "CDebugPrint.h"