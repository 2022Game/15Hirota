#include "CDebugTimer.h"

// �R���X�g���N�^
CDebugTimer::CDebugTimer()
	: freq({ 0 })
	, startCount({ 0 })
	, endCount({ 0 })
	, isEnd(false)
{
}

// ���Ԍv���J�n
void CDebugTimer::Start()
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startCount);
	isEnd = false;
}

// ���Ԍv���I��
void CDebugTimer::End()
{
	QueryPerformanceCounter(&endCount);
	isEnd = true;
}

// �v���������Ԃ��擾
float CDebugTimer::Get() const
{
	if (isEnd)
	{
		return (float)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	}
	else
	{
		LARGE_INTEGER tempCount;
		QueryPerformanceCounter(&tempCount);
		return (float)(tempCount.QuadPart - startCount.QuadPart) / freq.QuadPart;
	}
}

// ���Ԍv�����I�����Ă��邩
bool CDebugTimer::IsEnd() const
{
	return isEnd;
}