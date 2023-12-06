#include "CResource.h"

CResource::CResource()
	: mReferenceCount(0)
{
}

CResource::~CResource()
{
}

//bool CResource::Load(std::string path)
//{
//	return false;
//}

void CResource::Referenced()
{
	mReferenceCount++;
}

void CResource::Release()
{
	mReferenceCount--;
}