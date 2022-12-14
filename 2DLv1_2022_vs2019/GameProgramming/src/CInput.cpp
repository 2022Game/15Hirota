#include <Windows.h>
#include "CInput.h"
#include <stdio.h>


GLFWwindow* CInput::spWindow = nullptr;	//ウィンドウのポインタ

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
	printf("入力インスタンスが生まれました\n");
}


bool CInput::Key(char key)
{
	if (GetAsyncKeyState(key) & 0x8000) {
		if (!keyflg) {
			//キーを押した瞬間の処理
			keyflg = true;
		}
		//キーを押している間の処理
		false;
	}
	else {
		//キーを離している間の処理
		keyflg = false;
	}
	return GetAsyncKeyState(key) < 0;
}


//if (GetAsyncKeyState(key)) {
//	cout << "押されてます" << endl;
//}
//else {
//	cout << "押されていません" << endl;
//}
