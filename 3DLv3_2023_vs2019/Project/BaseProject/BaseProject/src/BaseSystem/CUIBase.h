#pragma once
#include "CTask.h"

class CImage;

class CUIBase : public CTask
{
public:
	CUIBase();
	virtual ~CUIBase();	
private:
	CImage* image;
};