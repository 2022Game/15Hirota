#pragma once
#include <Windows.h>
#include "GLFW/glfw3.h"
#include <map>

class CInput
{
public:
	static void Window(GLFWwindow* pwindow);
	void GetMousePos(float* px, float* py);

	CInput();
	//bool Key(����)
	//�߂�l
	//true:�����̃L�[��������Ă���
	//false:�����̃L�[��������Ă��Ȃ�
	bool Key(int key);

	//�L�[���������u�Ԃ��ǂ���
	//�O��̃t���[���͗�������Ԃ�
	//����̃t���[���͉����Ă����Ԃ̎�����true��Ԃ�
	bool PushKey(int key);

	//�L�[�𗣂����u�Ԃ��ǂ���
	//�O��̃t���[���͉����Ă����Ԃ�
	//����̃t���[���͗�������Ԃ̎�����true��Ԃ�
	bool PullKey(int key);

	//�L�[�̓��͏�Ԃ��X�V
	//(�Ăяo����1�t���[����1��܂�)
	static void Update();
private:
	static GLFWwindow* spWindow;	//�E�B���h�E�̃|�C���^

	//�L�[�̓��͏�ԃr�b�g
	enum InputBit
	{
		eInputBit_On,	//�����Ă��邩�ǂ���
		eInputBit_Push,	//�������u�Ԃ��ǂ���
		eInputBit_Pull,	//�������u�Ԃ��ǂ���
		Num,
	};
	//�L�[�̓��͏�Ԃ��Ǘ����郊�X�g
	static std::map<int, int> msInputBits;
};