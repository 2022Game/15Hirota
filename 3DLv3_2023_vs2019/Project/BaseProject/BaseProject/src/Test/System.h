#pragma once
class CColor;

namespace System
{
	/// <summary>
	/// ��ʂ̃N���A����\��ݒ�irgba�j
	/// </summary>
	/// <param name="r">�ݒ肷��F�̐ԗv�f</param>
	/// <param name="g">�ݒ肷��F�̗Ηv�f</param>
	/// <param name="b">�ݒ肷��F�̐v�f</param>
	/// <param name="a">�ݒ肷��F�̃A���t�@�l</param>
	void SetClearColor(float r, float g, float b, float a);
	/// <summary>
	/// ��ʂ̃N���A�J���[��ݒ�iCColor�j
	/// </summary>
	/// <param name="color">�ݒ肷��F</param>
	void SetClearColor(const CColor& color);
}