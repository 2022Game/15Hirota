#ifndef CJUMPINGKINOKO_H
#define CJUMPINGKINOKO_H

#include "CJumpingObject.h"

// プレイヤーを跳ねさせるキノコ
class CJumpingKinoko : public CJumpingObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="scale">大きさ</param>
	/// <param name="rot">回転</param>
	CJumpingKinoko(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "JumpingKinoko");

	// デストラクタ
	virtual ~CJumpingKinoko();
};
#endif