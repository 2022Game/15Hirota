#pragma once
#include <Windows.h>
#include "GLFW/glfw3.h"
#include <map>
#include "CVector.h"

// ���͔���N���X
class CInput
{
public:
	/// <summary>
	/// �E�B���h�E��ݒ�
	/// </summary>
	/// <param name="pwindow"></param>
	static void Window(GLFWwindow* pwindow);
	// �}�E�X���W���擾
	static CVector2 GetMousePos();

	/// <summary>
	/// �L�[�����͂���Ă��邩
	/// </summary>
	/// <param name="key">���肷��L�[</param>
	/// <returns>true�Ȃ�΁A������Ă���</returns>
	static bool Key(int key);

	/// <summary>
	/// �L�[���������u�Ԃ��ǂ���
	/// �O��̃t���[���͉����Ă��Ȃ���Ԃ�
	/// ����̃t���[���ŉ�������ԂɂȂ�������
	/// 1�t���[���̂�true��Ԃ�
	/// </summary>
	/// <param name="key">���肷��L�[</param>
	/// <returns>true�Ȃ�΁A�������u�Ԃł���</returns>
	static bool PushKey(int key);

	/// <summary>
	/// �L�[�𗣂����u�Ԃ��ǂ���
	/// �O��̃t���[���͉����Ă����Ԃ�
	/// ����̃t���[���ŗ�������ԂɂȂ�������
	/// 1�t���[���̂�true��Ԃ�
	/// </summary>
	/// <param name="key">���肷��L�[</param>
	/// <returns>true�Ȃ�΁A�������u�Ԃł���</returns>
	static bool PullKey(int key);

	/// <summary>
	/// �L�[�̓��͏�Ԃ��X�V
	/// �i�Ăяo����1�t���[����1��܂Łj
	/// </summary>
	static void Update();

private:
	// �R���X�g���N�^
	// �i�C���X�^���X�𐶐��ł��Ȃ��悤��private�j
	CInput();

	static GLFWwindow* spWindow;	// �E�B���h�E�̃|�C���^

	// �L�[�̓��͏�ԃr�b�g
	enum InputBit
	{
		eInputBit_On,	//�����Ă��邩�ǂ���
		eInputBit_Push,	//�������u�Ԃ��ǂ���
		eInputBit_Pull,	//�������u�Ԃ��ǂ���
		Num,
	};
	// �L�[�̓��͏�Ԃ��Ǘ����郊�X�g
	static std::map<int, int> msInputBits;
};