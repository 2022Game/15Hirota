#include "CInput.h"
#include <stdio.h>

GLFWwindow* CInput::spWindow = nullptr;	// �E�B���h�E�̃|�C���^
std::map<int, int> CInput::msInputBits;	// �L�[�̓��͏�Ԃ��Ǘ����郊�X�g

// �E�B���h�E��ݒ�
void CInput::Window(GLFWwindow* pwindow)
{
	spWindow = pwindow;
}

// �}�E�X���W���擾
CVector2 CInput::GetMousePos()
{
	double xpos, ypos;
	glfwGetCursorPos(spWindow, &xpos, &ypos);
	return CVector2((float)xpos, (float)ypos);
}

// �R���X�g���N�^
CInput::CInput()
{
	printf("���̓C���X�^���X�����܂�܂���\n");
}

// �L�[�����͂���Ă��邩
bool CInput::Key(int key)
{
	return (msInputBits[key] & (1 << eInputBit_On)) != 0;
}

// �L�[���������u�Ԃ��ǂ���
bool CInput::PushKey(int key)
{
	return (msInputBits[key] & (1 << eInputBit_Push)) != 0;
}

// �L�[�𗣂����u�Ԃ��ǂ���
bool CInput::PullKey(int key)
{
	return (msInputBits[key] & (1 << eInputBit_Pull)) != 0;
}

// �L�[�̓��͏�Ԃ��X�V
void CInput::Update()
{
	auto itBegin = msInputBits.begin();
	auto itEnd = msInputBits.end();
	for (auto it = itBegin; it != itEnd; ++it)
	{
		int key = it->first;
		int bit = it->second;

		// ���݉����Ă����Ԃ��擾
		bool isOn = (GetAsyncKeyState(key) & 0x8000) != 0;
		// �O�񉟂��Ă����Ԃ��擾
		bool isLastOn = bit & (1 << eInputBit_On);

		// �r�b�g�t���O������
		bit = 0;

		// ���݉����Ă����Ԃł���΁A
		// eInputBit_On�̃r�b�g�𗧂Ă�
		if (isOn) bit |= (1 << eInputBit_On);
		// �O��͗����Ă��āA���݂͉����Ă����Ԃł���΁A
		// eInputBit_Push�̃r�b�g�𗧂Ă�
		if (!isLastOn && isOn) bit |= (1 << eInputBit_Push);
		// �O��͉����Ă��āA���݂͗����Ă����Ԃł���΁A
		// eInputBit_Pull�̃r�b�g�𗧂Ă�
		if (isLastOn && !isOn) bit |= (1 << eInputBit_Pull);

		// ���X�g���̃r�b�g�t���O���㏑��
		it->second = bit;
	}
}
