#include "System.h"
#include "CColor.h"
#include <glut.h>

// ��ʂ̃N���A�J���[��ݒ�irgba�j
void System::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

// ��ʂ̃N���A�J���[��ݒ�iCColor�j
void System::SetClearColor(const CColor& color)
{
	SetClearColor(color.R(), color.G(), color.B(), color.A());
}