#include <Windows.h>
#include "CInput.h"
#include <stdio.h>


GLFWwindow* CInput::spWindow = nullptr;	//�E�B���h�E�̃|�C���^

using namespace std;

void CInput::Window(GLFWwindow* pwindow)
{
	spWindow = pwindow;
}

void CInput::GetMousePos(float* px, float* py)
{
	double xpos, ypos;
	glfwGetCursorPos(spWindow, &xpos, &ypos);
	*px = (float)xpos;
	*py = (float)ypos;
	return;
}

CInput::CInput()
{
	printf("���̓C���X�^���X�����܂�܂���\n");
}


bool CInput::Key(char key)
{
	if (GetAsyncKeyState(key) & 0x8000) {
		if (!keyflg) {
			//�L�[���������u�Ԃ̏���
			keyflg = true;
		}
		//�L�[�������Ă���Ԃ̏���
		false;
	}
	else {
		//�L�[�𗣂��Ă���Ԃ̏���
		keyflg = false;
	}
	return GetAsyncKeyState(key) < 0;
}


//if (GetAsyncKeyState(key)) {
//	cout << "������Ă܂�" << endl;
//}
//else {
//	cout << "������Ă��܂���" << endl;
//}
